#include "osc.h"

OSCConn conn;

int OSCConn::serverPortNumber=57120;

const char* OSCConn::serverAddress="localhost";

UdpSocket OSCConn::sock;

std::map <int, std::string> OSCConn::bufferFileById;

bool OSCConn::connect() 
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

bool OSCConn::sendSimpleMessage(const char* str)
{
	PacketWriter pw;
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

bool OSCConn::startServer()
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
			while (pr.isOk() && (incomingMsg = pr.popMessage()) != NULL) 
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

bool OSCConn::quitServer()
{
	fprintf(stderr, "Sending server quit message\n");
	if(!sendSimpleMessage("/app_quit")) return false;
	return true;
}

int OSCConn::getFreeBus()
{
	sendSimpleMessage("/get_free_bus");

	while (sock.isOk())
	{
		if (sock.receiveNextPacket(30)) 
		{
			PacketReader pr(sock.packetData(), sock.packetSize());
			Message *incomingMsg;
			while (pr.isOk() && (incomingMsg = pr.popMessage()) != NULL) 
			{
				if(strcmp(incomingMsg->addressPattern().c_str(), "/free_bus")==0)
				{
					int bus=-1;
					incomingMsg->arg().popInt32(bus);
					fprintf(stderr, "Got free bus: %d\n", bus);
					return bus;
				}
			}
		}
	}
}

void OSCConn::deleteBus(int bus)
{
	PacketWriter pw;
	Message msg("/delete_bus"); 
	msg.pushInt32(bus);
	
	pw.init();
	pw.startBundle().addMessage(msg).endBundle();
	
	fprintf(stderr, "Deleting bus: %d\n", bus);
	
	if(!sock.sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending a message '/delete_bus'\n");
		return;
	}
}

void OSCConn::getFreeBuses(int num, int* buses)
{
	int busCount=0;
	
	PacketWriter pw;
	Message msg("/get_free_bus"); 
	msg.pushInt32(num);
	
	pw.init();
	pw.startBundle().addMessage(msg).endBundle();
	
	if(!sock.sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending a message '/get_free_bus'\n");
		return;
	}
	

	while (sock.isOk())
	{
		if (sock.receiveNextPacket(30)) 
		{
			PacketReader pr(sock.packetData(), sock.packetSize());
			Message *incomingMsg;
			while (pr.isOk() && (incomingMsg = pr.popMessage()) != NULL) 
			{
				if(strcmp(incomingMsg->addressPattern().c_str(), "/free_bus")==0)
				{
					int bus=-1;
					incomingMsg->arg().popInt32(bus);
					buses[busCount]=bus;
					fprintf(stderr, "Got free bus: %d\n", bus);
					++busCount;
					if(busCount>=num) return;
				}
			}
		}
	}
}

int OSCConn::loadBuffer(const char* filename)
{
	PacketWriter pw;
	Message msg("/load_buffer"); 
	msg.pushStr(filename);
	pw.init();
	pw.startBundle().addMessage(msg).endBundle();
	
	if(!sock.sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending /load_buffer message\n");
		return -1;
	}
	

	while (sock.isOk())
	{
		if (sock.receiveNextPacket(30)) 
		{
			PacketReader pr(sock.packetData(), sock.packetSize());
			Message *incomingMsg;
			while (pr.isOk() && (incomingMsg = pr.popMessage()) != NULL) 
			{
				if(strcmp(incomingMsg->addressPattern().c_str(), "/new_buffer")==0)
				{
					int bufnum=-1;
					incomingMsg->arg().popInt32(bufnum);
					bufferFileById.insert(std::pair<int, std::string>(bufnum, std::string(filename)));
					fprintf(stderr, "Loaded buffer which number: %d\n", bufnum);
					return bufnum;
				}
			}
		}
	}
}

std::string OSCConn::getBufferFileById(int id)
{
	auto it=bufferFileById.find(id);
	if(it==bufferFileById.end())
	return "";
	else
	return (*it).second;
}

void OSCConn::deleteBuffer(int bufnum)
{
	PacketWriter pw;
	Message msg("/delete_buffer"); 
	msg.pushInt32(bufnum);
	
	pw.init();
	pw.startBundle().addMessage(msg).endBundle();
	
	bufferFileById.erase(bufnum);
	
	if(!sock.sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending a message '/delete_buffer'\n");
		return;
	}
	return;
}
