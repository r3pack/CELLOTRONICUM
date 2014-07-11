#ifndef OSC_H
#define OSC_H

	#define _WIN32_WINNT 0x501
	#define OSCPKT_OSTREAM_OUTPUT
	#include "oscpkt/oscpkt.hh"
	#include "oscpkt/udp.hh"

	using namespace oscpkt;
	
	class OSCConnection
	{
		private:
			int serverPortNumber=57120;

			const char* serverAddress="localhost";

			UdpSocket sock;
			
		public:
			
			OSCConnection() {}
			
			OSCConnection(const char* sA, int sPN=57120) {serverAddress=sA; serverPortNumber=sPN;}
			
			void setPort(int sPN) {serverPortNumber=sPN;}
			
			void setServer(const char* sA, int sPN=57120) {serverAddress=sA; serverPortNumber=sPN;}
			
			bool connect();
			
			bool isOk() {return sock.isOk();}
			
			const char* getError() {return sock.errorMessage().c_str();}
			
			const char* getServer() {return serverAddress;}
			
			int getPort() {return serverPortNumber;}
			
			UdpSocket& getSock() {return sock;}
			
			bool sendSimpleMessage(const char* str);
			
			bool startServer();

			bool quitServer();
	};
	
	extern OSCConnection conn;
	
#endif