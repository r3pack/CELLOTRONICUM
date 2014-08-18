#include "effects.h"
#include "osc.h"
#include "effectsdef.h"
#include "controllers.h"
#include "controllersdef.h"

const int MAX_EFFECTS_COUNT=1000;


struct EffectEntry{
	bool checked;
	const char* group;
	const char* subgroup;
	EffectEntry(bool c, const char* g, const char* s) {checked=c; group=g; subgroup=s;}
};

std::map<const char*, EffectEntry, cmpCStr> effectsList;


bool checkEffectsList()
{
	if(!OSCConn::sendSimpleMessage("/app_list_effects")) return false;

	int effectCount=MAX_EFFECTS_COUNT;
	int effectReceived=0;

	UdpSocket& sock=OSCConn::getSock();
	
	while (OSCConn::isOk() && effectReceived < effectCount)
	{
		if (sock.receiveNextPacket(30)) 
		{
			PacketReader pr(sock.packetData(), sock.packetSize());
			Message *incomingMsg;
			while (pr.isOk() && (incomingMsg = pr.popMessage()) != NULL) 
			{
				const char* addressPatern=incomingMsg->addressPattern().c_str();
			
				if(strcmp(addressPatern, "/effect")==0)
				{
					std::string name;
					incomingMsg->arg().popStr(name);
					
					fprintf(stderr, "Got effect '%s'", name.c_str());
					
					auto it = effectsList.find(name.c_str());
					
					if(it != effectsList.end())
					{
						fprintf(stderr, ", which exist on client side (OK)\n");
						(*it).second.checked=true;
					}
					else
					{
						fprintf(stderr, ", which NOT exist on client side (X)\n");
					}
					
					++effectReceived;
				}
				else
				if(strcmp(addressPatern, "/effects_count")==0)
				{
					incomingMsg->arg().popInt32(effectCount);
					fprintf(stderr, "Effects count: %d\n", effectCount);
				}
			}
		}
		
	}
	
	bool gotAllEffects=true;
	
	for(auto it=effectsList.begin();it!=effectsList.end();++it)
	{
		if(!((*it).second.checked)) 
		{
			gotAllEffects=false;
			fprintf(stderr, "Effect '%s' not found on server side!!! Program will be closed!\n", (*it).first);
		}
	}
	
	return gotAllEffects;
}

void EffectArgument::set(int var)
{
	type=TYPE_INT;
	value=new int(var);
}

void EffectArgument::set(float var)
{
	type=TYPE_FLOAT;
	value=new float(var);
}

void EffectArgument::set(std::string var)
{
	type=TYPE_STRING;
	value=new std::string(var);
}

void EffectArgument::addArgumentToMessage(Message* msg)
{
	msg->pushStr(name);
	switch(type)
	{
		case TYPE_INT:
			msg->pushInt32(*(int*)value);
		break;
		case TYPE_FLOAT:
			msg->pushFloat(*(float*)value);
		break;
		case TYPE_STRING:
			msg->pushStr(*(std::string*)value);
		break;
	}
}

void EffectArgument::sendArgument(int id)
{
	Message msg("/set_param"); 
	msg.pushInt32(id);
	msg.pushStr(name);
	switch(type)
	{
		case TYPE_INT:
			msg.pushInt32(*(int*)value);
		break;
		case TYPE_FLOAT:
			msg.pushFloat(*(float*)value);
		break;
		case TYPE_STRING:
			msg.pushStr(*(std::string*)value);
		break;
	}
	
	PacketWriter pw;
	
	pw.init();
	pw.startBundle().addMessage(msg).endBundle();
	
	//fprintf(stderr, "Sending an argument '%s' of instance %d\n", name, id);
	
	if(!OSCConn::getSock().sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending an argument '%s' of instance %d\n", name, id);
	}
}

EffectArgument::~EffectArgument()
{
	switch(type)
	{
		case TYPE_INT:
			delete (int*)value;
		break;
		case TYPE_FLOAT:
			delete (float*)value;
		break;
		case TYPE_STRING:
			delete (std::string*)value;
		break;
	}
}


int Effect::lastId=0;

std::set <std::pair<int, int> > Effect::effectTree;

std::map <int, Effect*> effectInstanceList;

std::map <int, Effect*>* getEffectInstanceList() {return &effectInstanceList;}

Effect::Effect() 
{
	id=lastId++; 
	effectInstanceList.insert(std::pair<int, Effect*>(id, this));
}

Effect::~Effect() 
{
	effectInstanceList.erase(id);
}

void Effect::setArgument(int argId, int value)
{
	EffectArgument* args=getArgs();
	args[argId].set(value);
}

void Effect::setArgument(int argId, float value)
{
	EffectArgument* args=getArgs();
	args[argId].set(value);
}

void Effect::setArgument(int argId, std::string value)
{
	EffectArgument* args=getArgs();
	args[argId].set(value);
}

void Effect::sendArgument(int argId)
{
	EffectArgument* args=getArgs();
	args[argId].sendArgument(id);
}

void Effect::setAndSendArgument(int argId, int value)
{
	EffectArgument* args=getArgs();
	args[argId].set(value);
	args[argId].sendArgument(id);
}

void Effect::setAndSendArgument(int argId, float value)
{
	EffectArgument* args=getArgs();
	args[argId].set(value);
	args[argId].sendArgument(id);
}

void Effect::setAndSendArgument(int argId, std::string value)
{
	EffectArgument* args=getArgs();
	args[argId].set(value);
	args[argId].sendArgument(id);
}

void Effect::pauseInstance()
{
	paused=true;
	Message msg("/pause_effect_instance");
	msg.pushInt32(id);
	
	PacketWriter pw;
	
	pw.init();
	pw.startBundle().addMessage(msg).endBundle();
	
	if(!OSCConn::getSock().sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending message..\n");
	}
}

void Effect::unpauseInstance()
{
	paused=false;
	Message msg("/unpause_effect_instance");
	msg.pushInt32(id);
	
	PacketWriter pw;
	
	pw.init();
	pw.startBundle().addMessage(msg).endBundle();
	
	if(!OSCConn::getSock().sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending message..\n");
	}
}

void Effect::sendInstance(bool paused)
{
	this->paused=paused;
	Message msg;
	if(paused)
	msg.init("/new_effect_instance_paused");
	else
	msg.init("/new_effect_instance");
	const char* name=getName();
	msg.pushInt32(id).pushStr(name);
	int argsCount=getArgsCount();
	EffectArgument* args=getArgs();
	for(int i=0;i<argsCount;++i)
	{
		args[i].addArgumentToMessage(&msg);
	}
	
	fprintf(stderr, "Sending new instance of effect '%s', id: %d\n", name, id);
	
	PacketWriter pw;
	
	pw.init();
	pw.startBundle().addMessage(msg).endBundle();
	
	if(!OSCConn::getSock().sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending message..\n");
	}
	
}

void Effect::deleteInstance()
{
	Message msg("/delete_effect_instance"); 
	const char* name=getName();
	msg.pushInt32(id);
	
	fprintf(stderr, "Deleting instance of effect '%s', id: %d\n", name, id);
	
	PacketWriter pw;
	
	pw.init();
	pw.startBundle().addMessage(msg).endBundle();
	
	if(!OSCConn::getSock().sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending message..\n");
	}
	
}

void Effect::updateTopologicalSequence()
{
	std::queue <int> Q;
	std::set <std::pair<int, int> > tmp;
	std::vector <int> sequence;
	
	effectTree.clear();
	
	for(auto it=getConnections()->begin();it!=getConnections()->end();++it)
	effectTree.insert(std::pair<int, int>((*it).first->getEffect()->getId(), (*it).second->getEffect()->getId()));
	
	
	for(auto it=effectTree.begin();it!=effectTree.end();++it)
	{
		int id=(*it).second;
		auto itlow=tmp.lower_bound(std::pair<int, int>(id, -1)); 
		if(itlow==tmp.end() || (*itlow).first!=id)
		{
			tmp.insert(std::pair<int,int>(id,1));
		}
		else
		{
			std::pair<int,int> buf=(*itlow);
			buf.second+=1;
			tmp.erase(itlow);
			tmp.insert(buf);
		}
	}
	
	for(auto it=effectTree.begin();it!=effectTree.end();++it)
	{
		int id=(*it).first;
		auto itlow=tmp.lower_bound(std::pair<int, int>(id, -1)); 
		if(itlow==tmp.end() || (*itlow).first!=id)
		{
			tmp.insert(std::pair<int,int>(id,0));
			Q.push(id);
		}
	}
	
	while(!Q.empty())
	{
		int u=Q.front();
		Q.pop();
		
		sequence.push_back(u);
		
		auto itlow=effectTree.lower_bound(std::pair<int, int>(u, -1)); 
		auto itup=effectTree.upper_bound(std::pair<int, int>(u+1, -1));
		
		for(auto it=itlow;it!=itup;++it)
		{
			auto ittmp=tmp.lower_bound(std::pair<int, int>((*it).second, -1));
			
			
			std::pair<int,int> buf=(*ittmp);
			buf.second-=1;
			tmp.erase(ittmp);
			
			if(buf.second==0)
			{
				Q.push(buf.first);
			}
			else
			{
				tmp.insert(buf);
			}
		}
		
	}
	
	//effectInstanceList[sequence[0]]->moveToHead();
	
	for(int i=1;i<sequence.size();++i)
	{
		effectInstanceList[sequence[i]]->moveAfter(effectInstanceList[sequence[i-1]]);
	}
	
}

void Effect::moveBefore(Effect* effect)
{	
	int secondId=effect->id;

	Message msg("/move_before_effect_instance"); 
	const char* name=getName();
	msg.pushInt32(id);
	msg.pushInt32(secondId);
	
	fprintf(stderr, "Moving instance of effect '%s', id: %d, before instance of effect '%s', id: %d\n", name, id, effect->getName(), secondId);
	
	PacketWriter pw;
	
	pw.init();
	pw.startBundle().addMessage(msg).endBundle();
	
	if(!OSCConn::getSock().sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending message..\n");
	}
	
}

void Effect::moveAfter(Effect* effect)
{	
	int secondId=effect->id;

	Message msg("/move_after_effect_instance"); 
	const char* name=getName();
	msg.pushInt32(id);
	msg.pushInt32(secondId);
	
	fprintf(stderr, "Moving instance of effect '%s', id: %d, after instance of effect '%s', id: %d\n", name, id, effect->getName(), secondId);
	
	PacketWriter pw;
	
	pw.init();
	pw.startBundle().addMessage(msg).endBundle();
	
	if(!OSCConn::getSock().sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending message..\n");
	}
	
}

void Effect::moveToHead()
{	
	Message msg("/move_to_head"); 
	const char* name=getName();
	msg.pushInt32(id);
	
	fprintf(stderr, "Moving instance of effect '%s', id: %d to head\n", name, id);
	
	PacketWriter pw;
	
	pw.init();
	pw.startBundle().addMessage(msg).endBundle();
	
	if(!OSCConn::getSock().sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending message..\n");
	}
	
}

void Effect::saveToFile(const char* filename)
{
	printf("Saving session to file '%s'\n", filename);
	FILE* file=fopen(filename, "wb");
	
	if(file==NULL)
	{
		fprintf(stderr, "Cannot open file to save data\n");
		return;
	}
	
	for(auto it=effectInstanceList.begin();it!=effectInstanceList.end();++it)
	{
		Effect* effect=(*it).second;
		fprintf(file, "effect %s %d \"", effect->getName(), effect->getId());
		effect->saveData(file);
		fprintf(file, "\"\n");
	}
	
	for(auto it=getControllerInstanceList()->begin();it!=getControllerInstanceList()->end();++it)
	{
		Controller* controller=(*it).second;
		fprintf(file, "controller %s %d \"", controller->getName(), controller->getId());
		controller->saveData(file);
		fprintf(file, "\"\n");
	}
	
	for(auto it=getConnections()->begin();it!=getConnections()->end();++it)
	{
		fprintf(file, "connection %d %d %d %d\n", (*it).first->getEffect()->getId(), (*it).first->getArg(), (*it).second->getEffect()->getId(), (*it).second->getArg());
	}
	
	fclose(file);
}

void Effect::loadFromFile(const char* filename)
{
	printf("Loading session from file '%s'\n", filename);
	FILE* file=fopen(filename, "rb");
	
	if(file==NULL)
	{
		fprintf(stderr, "Cannot open file to load data\n");
		return;
	}
	int maxId=lastId-1;
	
	char buf[2048];
	
	
	while(fscanf(file, "%s", buf)!=-1)
	{
		if(strcmp(buf, "effect")==0)
		{
			int id;
			fscanf(file, "%s %d", buf, &id);
			
			lastId=id;
			if(id>maxId) maxId=id;
			
			Effect* eff;
			
			bool playbuf=false;
			
			if(strcmp(buf, "eff_playbuf")==0) playbuf=true;
			else
			eff=getEffect(buf);
			
			fgets(buf, 2048, file);
			
			int begin;
			int i=0;
			for(;buf[i]!='\"';++i) {} i+=1;
			
			begin=i;
			
			for(;buf[i]!='\"';++i)
			{
				if(buf[i]=='\0') 
				fgets(buf+i, 2048-i, file);
			}
			
			
			buf[i]='\0';
			
			if(playbuf) eff=new Playbuf(buf+begin);
			else
			eff->loadData(buf+begin);
		}
		else if(strcmp(buf, "controller")==0)
		{
			int id;
			fscanf(file, "%s %d", buf, &id);
			
			Controller::lastId=id;
			if(id>maxId) maxId=id;
			
			Controller* ctr=getController(buf);
			
			fgets(buf, 2048, file);
			
			int begin;
			int i=0;
			for(;buf[i]!='\"';++i) {} i+=1;
			
			begin=i;
			
			for(;buf[i]!='\"';++i)
			{
				if(buf[i]=='\0') 
				fgets(buf+i, 2048-i, file);
			}
			
			buf[i]='\0';
			
			ctr->loadData(buf+begin);
		}
		else if(strcmp(buf, "connection")==0)
		{
			int effId1, effId2, arg1, arg2;
			fscanf(file, "%d %d %d %d", &effId1, &arg1, &effId2, &arg2);
			
			Effect* eff1=effectInstanceList[effId1];
			Effect* eff2=effectInstanceList[effId2];
			
			Bus* bus1, *bus2;
			
			for(auto it=busList.begin();it!=busList.end();++it)
			{
				Bus* bus=(*it).second;
				if(bus->getEffect()==eff1 && bus->getArg()==arg1) bus1=bus;
				if(bus->getEffect()==eff2 && bus->getArg()==arg2) bus2=bus;
			}
			
			bus1->setClicked();
			bus2->setClicked();
		}
	}
	lastId=maxId+1;
	updateTopologicalSequence();
}

void Effect::clearAll()
{

	while(!effectInstanceList.empty())
	{
		Effect* ptr=effectInstanceList.begin()->second;
		ptr->deleteInstance();
		delete ptr;
	}
	
	for(auto it=getControllerInstanceList()->begin();it!=getControllerInstanceList()->end();++it)
	{
		delete it->second;
	}

	getConnections()->clear();
	busList.clear();
	controllBusList.clear();
	valueGifterList.clear();
	effectInstanceList.clear();
	getControllerInstanceList()->clear();
	
	Bus::lastClicked=-1;
	Bus::lastId=0;
	ControllBus::lastClicked=-1;
	ControllBus::lastId=0;
	Slider::lastClicked=-1;
	Slider::lastId=0;

	lastId=0;
	Controller::lastId=0;
}

void EffectCreator::moveUp() 
{
	EffectCreatorMenuEntry* parent=chosenEffect->parent;
	if(parent==NULL) return;
	
	auto it=parent->submenuEntries->begin();
	for(;it!=parent->submenuEntries->end();++it)
	{
		if((*it).second==chosenEffect) break;
	}
	
	if(it==parent->submenuEntries->begin())
	{
		it=--parent->submenuEntries->end();
	}
	else --it;
	
	chosenEffect=(*it).second;
}

void EffectCreator::moveDown()
{
	EffectCreatorMenuEntry* parent=chosenEffect->parent;
	if(parent==NULL) return;
	
	auto it=parent->submenuEntries->begin();
	for(;it!=parent->submenuEntries->end();++it)
	{
		if((*it).second==chosenEffect) break;
	}
	
	++it;
	
	if(it==parent->submenuEntries->end())
	{
		it=parent->submenuEntries->begin();
	}
	
	chosenEffect=(*it).second;
}

void EffectCreator::enter()
{
	if(chosenEffect->submenuEntries==NULL)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		
		if(strncmp(chosenEffect->name, "ctr_", 4)==0)
		getController(chosenEffect->name, x, y);
		else
		if(strncmp(chosenEffect->name, "eff_", 4)==0)
		getEffect(chosenEffect->name, x, y);
	}
	else
	{
		chosenEffect=chosenEffect->submenuEntries->begin()->second;
	}
}

void EffectCreator::back()
{
	if(chosenEffect->parent->parent!=NULL)
	chosenEffect=chosenEffect->parent;
}

void EffectCreator::init()
{
	chosenEffect=new EffectCreatorMenuEntry("", NULL, false);
	for(auto it=effectsList.begin();it!=effectsList.end();++it)
	{
		const char* name=(*it).first;
		const char* group=(*it).second.group;
		const char* subgroup=(*it).second.subgroup;
		
		auto mapIt=chosenEffect->submenuEntries->find(group);
		if(mapIt==chosenEffect->submenuEntries->end())
		{
			mapIt=chosenEffect->submenuEntries->insert(std::pair<const char*, EffectCreatorMenuEntry*>(group, new EffectCreatorMenuEntry(group, chosenEffect, false))).first;
		}
		
		if(subgroup!=NULL)
		{
			auto mapIt2=mapIt->second->submenuEntries->find(subgroup);
			if(mapIt2==mapIt->second->submenuEntries->end())
			{
				mapIt2=mapIt->second->submenuEntries->insert(std::pair<const char*, EffectCreatorMenuEntry*>(subgroup, new EffectCreatorMenuEntry(subgroup, mapIt->second, false))).first;
			}
			mapIt=mapIt2;
		}

		mapIt->second->submenuEntries->insert(std::pair<const char*, EffectCreatorMenuEntry*>(name, new EffectCreatorMenuEntry(name, (*mapIt).second, true)));
	}
	
	auto mapIt=chosenEffect->submenuEntries->insert(std::pair<const char*, EffectCreatorMenuEntry*>("Controllers", new EffectCreatorMenuEntry("Controllers", chosenEffect, false))).first;
	
	for(auto it=getControllerList()->begin();it!=getControllerList()->end();++it)
	{
		const char* name=(*it);
		(*mapIt).second->submenuEntries->insert(std::pair<const char*, EffectCreatorMenuEntry*>(name, new EffectCreatorMenuEntry(name, (*mapIt).second, true)));
	}
	
	chosenEffect->calculateWidth();
	
	chosenEffect=chosenEffect->submenuEntries->begin()->second;
}

void EffectCreator::draw(int X, int Y)
{
	EffectCreatorMenuEntry* actualEntry=chosenEffect;
	EffectCreatorMenuEntry* oldEntry=NULL;
	
	while(1)
	{	
		int newY=Y;
		
		oldEntry=actualEntry;
		actualEntry=actualEntry->parent;
		
		if(actualEntry==NULL) break;
	
		X-=actualEntry->width+menu_period;
		for(auto it=actualEntry->submenuEntries->begin();it!=actualEntry->submenuEntries->end();++it)
		{
			SDL_Texture* nameTex=(((*it).second==oldEntry)?(*it).second->nameTexRed:(*it).second->nameTex);
			int w, h;
			SDL_QueryTexture(nameTex, NULL, NULL, &w, &h);
			SDL_Rect nameRect;
			nameRect.x=X;
			nameRect.y=newY;
			nameRect.w=w;
			nameRect.h=h;
			SDL_RenderCopy(render, nameTex, NULL, &nameRect);
			newY+=h;
		}
	}
}

#include "effectsdef.h"

void EffectCreator::receiveKeyboardEvent(SDL_Scancode scancode)
{
	switch(scancode)
	{
		case SDL_SCANCODE_UP:
			moveUp();
		break;
		case SDL_SCANCODE_DOWN:
			moveDown();
		break;
		case SDL_SCANCODE_RETURN:
			enter();
		break;
		case SDL_SCANCODE_BACKSPACE:
		case SDL_SCANCODE_LEFT:
			back();
		break;
	}
}

void registerEffect(const char* name, const char* group, const char* subgroup) 
{
	effectsList.insert(std::pair<const char*, EffectEntry>(name, EffectEntry(false, group, subgroup)));
}
