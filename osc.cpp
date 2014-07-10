#include "osc.h"

OSCConnection conn;

bool OSCConnection::connect() 
{
	sock.connectTo(serverAddress, serverPortNumber);
	if(!conn.isOk()) 
	{
		fprintf(stderr, "Error connection to %s:%d : %s\n", conn.getServer(), conn.getPort(), conn.getError());
		return false;
	}
	
	fprintf(stderr, "Client started, will send packets to %s:%d\n", conn.getServer(), conn.getPort());
	return true;
}

bool OSCConnection::sendSimpleMessage(const char* str)
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

bool OSCConnection::startServer()
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
	
	if(!statusOK)
	{
		fprintf(stderr, "Error starting the server. Exiting...\n"); 
	}
	
	return statusOK;
}

bool OSCConnection::quitServer()
{
	fprintf(stderr, "Sending server quit message\n");
	if(!sendSimpleMessage("/app_quit")) return false;
	return true;
}
