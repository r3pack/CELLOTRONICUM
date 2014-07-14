#include "effects.h"
#include "osc.h"


const int MAX_EFFECTS_COUNT=1000;

struct cmpCStr
{
   bool operator()(char const *a, char const *b)
   {
      return std::strcmp(a, b) < 0;
   }
};

std::map<const char*, bool, cmpCStr> effectsList;

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
			while (pr.isOk() && (incomingMsg = pr.popMessage()) != 0) 
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
						(*it).second=true;
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
		if(!((*it).second)) 
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
	msg->pushStr(std::string("\\")+std::string(name));
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

std::map <int, Effect*> effectInstanceList;

std::map <int, Effect*>* getEffectInstanceList() {return &effectInstanceList;}

Effect::Effect() 
{
	printf("konstruktor bazowy\n");
	id=lastId++; 
	effectInstanceList.insert(std::pair<int, Effect*>(id, this));
}

Effect::~Effect() 
{
	effectInstanceList.erase(id);
}

void Effect::setArgument(int argId, int value)
{
	EffectArgument* args=getAgrs();
	args[argId].set(value);
}

void Effect::setArgument(int argId, float value)
{
	EffectArgument* args=getAgrs();
	args[argId].set(value);
}

void Effect::setArgument(int argId, std::string value)
{
	EffectArgument* args=getAgrs();
	args[argId].set(value);
}

void Effect::sendArgument(int argId)
{
	EffectArgument* args=getAgrs();
	args[argId].sendArgument(id);
}

void Effect::setAndSendArgument(int argId, int value)
{
	EffectArgument* args=getAgrs();
	args[argId].set(value);
	args[argId].sendArgument(id);
}

void Effect::setAndSendArgument(int argId, float value)
{
	EffectArgument* args=getAgrs();
	args[argId].set(value);
	args[argId].sendArgument(id);
}

void Effect::setAndSendArgument(int argId, std::string value)
{
	EffectArgument* args=getAgrs();
	args[argId].set(value);
	args[argId].sendArgument(id);
}

void Effect::sendInstance()
{
	printf("ssend\n");
	Message msg("/new_effect_instance"); 
	printf("ssend\n");
	const char* name=getName();
	printf("ssend %s\n", name);
	msg.pushInt32(id).pushStr(name);
	printf("ssend\n");
	int argsCount=getAgrsCount();
	printf("ssend\n");
	EffectArgument* args=getAgrs();
	printf("ssend\n");
	for(int i=0;i<argsCount;++i)
	{
		args[i].addArgumentToMessage(&msg);
	}
	
	fprintf(stderr, "Sending new instance of effect '%s', id: %d\n", name, id);
	printf("ssend\n");
	
	PacketWriter pw;
	
	pw.init();
	pw.startBundle().addMessage(msg).endBundle();
	
	if(!OSCConn::getSock().sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending instance..\n");
	}
	
}

void registerEffect(const char* name) 
{
	effectsList.insert(std::pair<const char*, bool>(name, false));
}
