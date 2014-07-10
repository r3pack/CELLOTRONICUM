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
		conn.setServer(argv[1]);
		if(argc>2)
		{
			conn.setPort(atoi(argv[2])); 
		}
	}
	
	registerEffects();
	
	if(!conn.connect()) exit(1);
	
	if(!conn.startServer()) exit(2);
	
	if(!checkEffectsList()) {conn.quitServer(); exit(3);}
	
	waitFor(3000);
	
	conn.quitServer();
	
	fprintf(stderr, "Done\n");
}