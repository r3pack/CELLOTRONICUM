#include "effects.h"
#include "osc.h"
#include <map>

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
	if(!conn.sendSimpleMessage("/app_list_effects")) return false;

	int effectCount=MAX_EFFECTS_COUNT;
	int effectReceived=0;

	UdpSocket& sock=conn.getSock();
	
	while (conn.isOk() && effectReceived < effectCount)
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

void EffectArgument::getArgumentStr(std::ostringstream& ss)
{
	ss << "\\" << name << " ";
	switch(type)
	{
		case TYPE_INT:
			ss << *(int*)value;
		break;
		case TYPE_FLOAT:
			ss << *(float*)value;
		break;
		case TYPE_STRING:
			ss << *(std::string*)value;
		break;
	}
	ss << " ";
}

void EffectArgument::sendArgument(const char* effect)
{
	std::string str="/" +  std::string(effect) + "/" + std::string(name);
	Message msg(str); 
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
	
	if(!conn.getSock().sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending an argument '%s'\n", str.c_str());
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

template <class T>
void Effect::setArgument(int id, T value)
{
	EffectArgument* args=getAgrs();
	args[id].set(value);
}

void Effect::sendArgument(int id)
{
	EffectArgument* args=getAgrs();
	args[id].sendArgument(getName());
}

template <class T>
void Effect::setAndSendArgument(int id, T value)
{
	EffectArgument* args=getAgrs();
	args[id].set(value);
	args[id].sendArgument(getName());
}

void Effect::sendInstance()
{
	Message msg("/new_effect_instance"); 
	
	const char* name=getName();
	
	msg.pushInt32(id).pushStr(name);
	
	std::ostringstream ss;
	
	int argsCount=getAgrsCount();
	EffectArgument* args=getAgrs();
	
	for(int i=0;i<argsCount;++i)
	{
		args[i].getArgumentStr(ss);
	}
	
	msg.pushStr(ss.str());
	
	fprintf(stderr, "Sending new instance of effect '%s', id: %d, args: %s\n", name, id, ss.str().c_str());
	
	PacketWriter pw;
	
	pw.init();
	pw.startBundle().addMessage(msg).endBundle();
	
	if(!conn.getSock().sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending instance..\n");
	}
	
}

void Effect::registerEffect() 
{
	effectsList.insert(std::pair<const char*, bool>(getName(), false));
}
