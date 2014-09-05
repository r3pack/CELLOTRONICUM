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
			static bool recordIsStarted; ///czy nagrywanie jest włączone
		
			static int serverPortNumber; ///numer portu serwera

			static const char* serverAddress; ///adres serwera jako tekst - moży być to domena lub adres ip

			static UdpSocket sock; ///socket (klasa z biblioteki oscptk)
			
			static std::map <int, std::string> bufferFileById; ///słownik plików z próbkami po id wczytanych buforów
			
			OSCConn() {}
			
		public:
			
			///ustawia port
			static void setPort(int sPN) {serverPortNumber=sPN;} 
			
			///ustawia adres serwera i ewentualnie port
			static void setServer(const char* sA, int sPN=57120) {serverAddress=sA; serverPortNumber=sPN;}
			
			///Nawiązuje połączenie z serwerem (nie wiem czy to się wiąże w wysyłanie czegokolwiek)
			static bool connect();
			
			///Czy z socketem jest wszystko ok
			static bool isOk() {return sock.isOk();}
			
			///zwraca ostatni komunikat błędu
			static const char* getError() {return sock.errorMessage().c_str();}
			
			///Zwraca adres serwera
			static const char* getServer() {return serverAddress;}
			
			///Zwraca port serwera
			static int getPort() {return serverPortNumber;}
			
			///Zwraca socket
			static UdpSocket& getSock() {return sock;}
			
			///Wysyła prostą wiadomość tekstową do serwera (przydatne do poleceń bez parametrów)
			static bool sendSimpleMessage(const char* str);
			
			///Startuje serwer SuperCollidera
			static bool startServer();

			///Wyłącza serwer i interpreter SuperCollidera
			static bool quitServer();
			
			///Pobiera wolny bus od SC
			static int getFreeBus();
			
			///Pobiera kilka wolnych busów od SC i zapisuje je do tablicy
			static void getFreeBuses(int num, int* buses);
			
			///Ładuje bufor do SC i zwara jego id
			static int loadBuffer(const char* filename);
			
			///Alokuje bufor o zadanym rozmiarze (w sekundach)
			static int allocBuffer(float seconds);
			
			///zwraca nazwę pliku z próbką po id bufora
			static std::string getBufferFileById(int id);
			
			///Usuwa bufor o podanym id
			static void deleteBuffer(int bufnum);
			
			///Usuwa bus o podanym id
			static void deleteBus(int bus);
			
			///Zaczyna nagrywanie
			static void startRecord();
			
			///Kończy nagrywanie
			static void stopRecord();
			
			///Informuje czy dźwięk jest nagrywany
			static bool isRecording() {return recordIsStarted;}
			
			///Ustawia plik do nagrania (trzeba wykonać PRZED rozpoczęciem nagrywania)
			static void recordToFile();
	};
	
#endif