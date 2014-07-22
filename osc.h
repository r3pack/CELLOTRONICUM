#ifndef OSC_H
#define OSC_H

	#define _WIN32_WINNT 0x501
	#define OSCPKT_OSTREAM_OUTPUT
	#include "oscpkt/oscpkt.hh"
	#include "oscpkt/udp.hh"
	
	#include <map>

	using namespace oscpkt;
	
	class OSCConn
	{
		private:
			static int serverPortNumber;

			static const char* serverAddress;

			static UdpSocket sock;
			
			static std::map <int, const char*> bufferFileById;
			
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
			
			static int getFreeBus();
			
			static void getFreeBuses(int num, int* buses);
			
			static int loadBuffer(const char* filename);
			
			static const char* getBufferFileById(int id);
			
			static void deleteBuffer(int bufnum);
	};
	
#endif