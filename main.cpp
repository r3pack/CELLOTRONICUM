#include <cstdio>
#include <cstring>
#include <chrono>
#include <thread>

#define _WIN32_WINNT 0x501
#define OSCPKT_OSTREAM_OUTPUT
#include "oscpkt/oscpkt.hh"
#include "oscpkt/udp.hh"


using namespace oscpkt;

int serverPortNumber=57120;

const char* serverAddress="localhost";

UdpSocket sock;

PacketReader pr;
PacketWriter pw;

void waitFor(int ms)
{
	std::chrono::milliseconds dura(ms);
    std::this_thread::sleep_for(dura);
}

bool sendSimpleMessage(const char* str)
{
	Message msg(str); 
	pw.init();
	pw.startBundle().addMessage(msg).endBundle();
	
	if(!sock.sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending a message '%s'\n", str);
		return false;
	}
	return true;
}


bool startServer()
{
	if(!sendSimpleMessage("/app_start")) return false;

	int pid=0;
	bool statusOK=false;
	
	while (sock.isOk() && !statusOK)
	{
		if (sock.receiveNextPacket(30)) 
		{
			PacketReader pr(sock.packetData(), sock.packetSize());
			Message *incomingMsg;
			while (pr.isOk() && (incomingMsg = pr.popMessage()) != 0) 
			{
				if(strcmp(incomingMsg->addressPattern().c_str(), "/status_ok")==0)
				{
					incomingMsg->arg().popInt32(pid);
					fprintf(stderr, "Server working, pid: %d\n", pid);
					statusOK=true;
					break;
				}
			}
		}
	}
	return statusOK;
}

bool quitServer()
{
	fprintf(stderr, "Sending server quit message\n");
	if(!sendSimpleMessage("/app_quit")) return false;
	return true;
}


bool getEffects()
{
	const int MAX_EFFECTS=1000;

	if(!sendSimpleMessage("/app_list_effects")) return false;

	int effectCount=MAX_EFFECTS;
	int effectReceived=0;

	
	while (sock.isOk() && effectReceived < effectCount)
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
					fprintf(stderr, "Got effect '%s'\n", name.c_str());
					++effectReceived;
					
					name="/"+name;
					sendSimpleMessage(name.c_str());
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
	
	
	return true;
}

int main (int argc, char** argv)
{
	if(argc>1)
	{
		serverAddress=argv[1];
		if(argc>2)
		{
			serverPortNumber=atoi(argv[2]);
		}
	}
	
	sock.connectTo(serverAddress, serverPortNumber);
	
	
	if (!sock.isOk()) 
	{
		fprintf(stderr, "Error connection to %s:%d : %s\n", serverAddress, serverPortNumber, sock.errorMessage().c_str());
		exit(1);
	}
	
	fprintf(stderr, "Client started, will send packets to %s:%d\n", serverAddress, serverPortNumber);
	
	
	startServer();
	
	getEffects();
	
	waitFor(3000);
	
	quitServer();
	
	fprintf(stderr, "Done\n");
}