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
	
	waitFor(5000);
	
	quitServer();
	
	fprintf(stderr, "Done\n");
}