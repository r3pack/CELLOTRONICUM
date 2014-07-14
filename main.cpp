#include <cstdio>
#include <cstring>
#include <chrono>
#include <thread>
#include "osc.h"
#include "effects.h"
#include "effectsdef.h"

void waitFor(int ms)
{
	std::chrono::milliseconds dura(ms);
	std::this_thread::sleep_for(dura);
}

int main (int argc, char** argv)
{
	if(argc>1)
	{
		OSCConn::setServer(argv[1]);
		if(argc>2)
		{
			OSCConn::setPort(atoi(argv[2])); 
		}
	}
	
	registerEffects();
	
	if(!OSCConn::connect()) exit(1);
	
	if(!OSCConn::startServer()) exit(2);
	
	if(!checkEffectsList()) {OSCConn::quitServer(); exit(3);}
	
	
	//Brassage br; //przykładowa instancja efektu
	
	waitFor(3000);
	
	printf("Dostalem busa: %d\n", OSCConn::getFreeBus());
	printf("Dostalem busa: %d\n", OSCConn::getFreeBus());
	printf("Dostalem busa: %d\n", OSCConn::getFreeBus());
	printf("Dostalem busa: %d\n", OSCConn::getFreeBus());
	printf("Dostalem busa: %d\n", OSCConn::getFreeBus());
	
	
	printf("Dostalem bufor: %d\n", OSCConn::loadBuffer("zBrody1.wav"));
	//printf("Dostalem bufor: %d\n", OSCConn::loadBuffer("zBrody2.wav"));
	//printf("Dostalem bufor: %d\n", OSCConn::loadBuffer("zBrody3.wav"));
	//printf("Dostalem bufor: %d\n", OSCConn::loadBuffer("zBrody4.wav"));
	
	int bufnum=OSCConn::loadBuffer("zBrody4.wav");
	
	printf("Mam bufor: %d\n", bufnum);
	
	Playbuf playbuf;
	
	
	waitFor(3000);
	
	OSCConn::quitServer();
	
	fprintf(stderr, "Done\n");
}