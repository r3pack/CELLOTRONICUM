#ifndef OSC_H
#define OSC_H

	#define _WIN32_WINNT 0x501
	#define OSCPKT_OSTREAM_OUTPUT
	#include "oscpkt/oscpkt.hh"
	#include "oscpkt/udp.hh"

	using namespace oscpkt;
	
	class OSCConn
	{
		private:
			static int serverPortNumber;

			static const char* serverAddress;

			static UdpSocket sock;
			
		public:
			
			static void setPort(int sPN) {serverPortNumber=sPN;}
			
			static void setServer(const char* sA, int sPN=57120) {serverAddress=sA; serverPortNumber=sPN;}
			
			static bool connect();
			
			static bool isOk() {return sock.isOk();}
			
			static const char* getError() {return sock.errorMessage().c_str();}
			
			static const char* getServer() {return serverAddress;}
			
			static int getPort() {return serverPortNumber;}
			
			static UdpSocket& getSock() {return sock;}
			
			static bool sendSimpleMessage(const char* str);
			
			static bool startServer();

			static bool quitServer();
			
			static int getFreeBus()
			{
				sendSimpleMessage("/get_free_bus");
	
				while (sock.isOk())
				{
					if (sock.receiveNextPacket(30)) 
					{
						PacketReader pr(sock.packetData(), sock.packetSize());
						Message *incomingMsg;
						while (pr.isOk() && (incomingMsg = pr.popMessage()) != 0) 
						{
							if(strcmp(incomingMsg->addressPattern().c_str(), "/free_bus")==0)
							{
								int bus=-1;
								incomingMsg->arg().popInt32(bus);
								return bus;
							}
						}
					}
				}
			}
			
			static int loadBuffer(const char* filename)
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
						while (pr.isOk() && (incomingMsg = pr.popMessage()) != 0) 
						{
							if(strcmp(incomingMsg->addressPattern().c_str(), "/new_buffer")==0)
							{
								int bufnum=-1;
								incomingMsg->arg().popInt32(bufnum);
								return bufnum;
							}
						}
					}
				}
			}
	};
	
#endif