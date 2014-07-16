#include <cstdio>
#include <cstring>
#include <chrono>
#include <thread>
#include "osc.h"
#include "effects.h"
#include "effectsdef.h"
#include "graphics.h"

void waitFor(int ms)
{
	std::chrono::milliseconds dura(ms);
	std::this_thread::sleep_for(dura);
}


#undef main
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
	
	initSDL();
	
	//Brassage br; //przykładowa instancja efektu
	
	/*printf("Dostalem busa: %d\n", OSCConn::getFreeBus());
	printf("Dostalem busa: %d\n", OSCConn::getFreeBus());
	printf("Dostalem busa: %d\n", OSCConn::getFreeBus());
	printf("Dostalem busa: %d\n", OSCConn::getFreeBus());
	printf("Dostalem busa: %d\n", OSCConn::getFreeBus());
	
	
	printf("Dostalem bufor: %d\n", OSCConn::loadBuffer("zBrody1.wav"));
	printf("Dostalem bufor: %d\n", OSCConn::loadBuffer("zBrody2.wav"));
	printf("Dostalem bufor: %d\n", OSCConn::loadBuffer("zBrody3.wav"));
	printf("Dostalem bufor: %d\n", OSCConn::loadBuffer("zBrody4.wav"));
	
	int bufnum=OSCConn::loadBuffer("zBrody3.wav");
	
	printf("Mam bufor: %d\n", bufnum);
	*/
	
	int bufnum=OSCConn::loadBuffer("zBrody3.wav");
	
	int freebus=OSCConn::getFreeBus();
	
	Playbuf playbuf(bufnum, freebus);
	
	//Distecho distecho(50, 50, freebus);
	
	auto effectInstanceList=getEffectInstanceList();
	
	bool quit = false;
	
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					quit = true;
				break;
				case SDL_KEYDOWN:
				break;
				case SDL_MOUSEMOTION:
				case SDL_MOUSEBUTTONDOWN:

					if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
					{
						int x=event.button.x;
						int y=event.button.y;
						for(auto it=effectInstanceList->begin();it!=effectInstanceList->end();++it)
						{
							it->second->receiveClick(x, y);
						}
					}
				break;
			}
		}
		
		SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
		SDL_RenderClear(render);
		
		for(auto it=effectInstanceList->begin();it!=effectInstanceList->end();++it)
		{
			it->second->draw();
		}
		SDL_RenderPresent(render);
	}
	
	quitSDL();
	fprintf(stderr, "Done\n");
}