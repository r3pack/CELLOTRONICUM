#include "osc.h"
#include <chrono>
#include "graphics.h"

OSCConn conn;

int OSCConn::serverPortNumber=57120;

const char* OSCConn::serverAddress="localhost";

UdpSocket OSCConn::sock;

std::map <int, std::string> OSCConn::bufferFileById;

std::chrono::time_point<std::chrono::system_clock> operationStart;

bool OSCConn::recordIsStarted=false;

void setOperationStart()
{
	operationStart=std::chrono::system_clock::now();
}

bool checkIfTimeout(double seconds)
{
	
	std::chrono::duration<double> time=std::chrono::system_clock::now() - operationStart;
	if(time.count()>seconds) return true;
	else return false;
}


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
	
	setOperationStart();
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
		if(checkIfTimeout(1.0f))
		{
			fprintf(stderr, "Waiting for server to boot...\n");
			return startServer();
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

void OSCConn::startRecord()
{
	if(recordIsStarted)
	{
		fprintf(stderr, "Error: Record is already started.\n");
	}
	recordIsStarted=true;
	
	fprintf(stderr, "Record is started - output is recording now.\n");
	sendSimpleMessage("/start_record");
}

void OSCConn::stopRecord()
{
	if(!recordIsStarted)
	{
		fprintf(stderr, "Error: Record is already stopped.\n");
	}
	recordIsStarted=false;
	fprintf(stderr, "Record is stopped.\n");
	sendSimpleMessage("/stop_record");
}

void OSCConn::recordToFile()
{
	PacketWriter pw;
	Message msg("/record_to_file"); 
	
	char filename[MAX_PATH];
	
	getSaveFile(filename, MAX_PATH);
	
	msg.pushStr(filename);
	
	pw.init();
	pw.startBundle().addMessage(msg).endBundle();
	
	fprintf(stderr, "Saving record to file: %s\n", filename);
	
	if(!sock.sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending a message '/record_to_file'\n");
		return;
	}
}

int OSCConn::getFreeBus()
{
	sendSimpleMessage("/get_free_bus");

	setOperationStart();
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
		if(checkIfTimeout(1.0f))
		{
			printf("Fail to get free bus (Timeout)\n");
			return 0;
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
	
	setOperationStart();
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
		if(checkIfTimeout(3.0f))
		{
			printf("Fail to get free buses (Timeout)\n");
			while(busCount<num) buses[busCount++]=0;
			return;
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
	
	setOperationStart();
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
		if(checkIfTimeout(3.0f))
		{
			printf("Fail to load buffer (Timeout)\n");
			return -1;
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
	
	fprintf(stderr, "Deleting buffer which number: %d\n", bufnum);
	
	if(!sock.sendPacket(pw.packetData(), pw.packetSize()))
	{
		fprintf(stderr, "Error sending a message '/delete_buffer'\n");
		return;
	}
	return;
}
