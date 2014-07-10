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

void registerEffect(Effect* eff) 
{
	effectsList.insert(std::pair<const char*, bool>(eff->getName(), false));
}

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

int EffectInstance::lastId=0;
