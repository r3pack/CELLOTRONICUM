#include <cstdio>
#include <cstring>
#include <chrono>
#include <thread>
#include "osc.h"
#include "effects.h"
#include "effectsdef.h"
#include "graphics.h"

EffectCreator effectCreator;

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
	
	effectCreator.init();
	
	
	/*int bufnum=OSCConn::loadBuffer("zBrody3.wav");
	
	Playbuf playbuf(50, 500, bufnum);
	
	Distecho distecho(50, 50);
	Distecho distecho2(350, 50);
	
	Output output(350, 500);*/
	
	//playbuf.moveBefore(&distecho);
	
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
				case SDL_MOUSEBUTTONDOWN:
					if(event.button.button==SDL_BUTTON_LEFT)
					{
						int x=event.button.x;
						int y=event.button.y;
						for(auto it=effectInstanceList->begin();it!=effectInstanceList->end();++it)
						{
							it->second->receiveClick(x, y, ME_PRESS);
						}
					}
					else
					if(event.button.button==SDL_BUTTON_RIGHT)
					{
						int x=event.button.x;
						int y=event.button.y;
						for(auto it=effectInstanceList->begin();it!=effectInstanceList->end();++it)
						{
							it->second->receiveSecondClick(x, y, ME_PRESS);
						}
					}
					else
					if(event.button.button==SDL_BUTTON_MIDDLE)
					{
						int x=event.button.x;
						int y=event.button.y;
						for(auto it=effectInstanceList->begin();it!=effectInstanceList->end();)
						{
							auto it2=it;
							++it;
							it2->second->receiveThridClick(x, y, ME_PRESS);
						}
					}
				break;
				case SDL_MOUSEBUTTONUP:
					if(event.button.button==SDL_BUTTON_LEFT)
					{
						int x=event.button.x;
						int y=event.button.y;
						for(auto it=effectInstanceList->begin();it!=effectInstanceList->end();++it)
						{
							it->second->receiveClick(x, y, ME_RELEASE);
						}
					}
					else
					if(event.button.button==SDL_BUTTON_RIGHT)
					{
						int x=event.button.x;
						int y=event.button.y;
						for(auto it=effectInstanceList->begin();it!=effectInstanceList->end();++it)
						{
							it->second->receiveSecondClick(x, y, ME_RELEASE);
						}
					}
					else
					if(event.button.button==SDL_BUTTON_MIDDLE)
					{
						int x=event.button.x;
						int y=event.button.y;
						for(auto it=effectInstanceList->begin();it!=effectInstanceList->end();)
						{
							auto it2=it;
							++it;
							it2->second->receiveThridClick(x, y, ME_RELEASE);
						}
					}
				break;
				case SDL_MOUSEMOTION:
					if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
					{
						int x=event.button.x;
						int y=event.button.y;
						for(auto it=effectInstanceList->begin();it!=effectInstanceList->end();++it)
						{
							it->second->receiveClick(x, y, ME_REPEAT);
						}
					}
					else
					if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
					{
						int x=event.button.x;
						int y=event.button.y;
						for(auto it=effectInstanceList->begin();it!=effectInstanceList->end();++it)
						{
							it->second->receiveSecondClick(x, y, ME_REPEAT);
						}
					}
					else
					if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE))
					{
						int x=event.button.x;
						int y=event.button.y;
						for(auto it=effectInstanceList->begin();it!=effectInstanceList->end();)
						{
							auto it2=it;
							++it;
							it2->second->receiveThridClick(x, y, ME_REPEAT);
						}
					}
				break;
				case SDL_KEYDOWN:
					effectCreator.receiveKeyboardEvent(event.key.keysym.scancode);
				break;
			}
		}
		
		SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
		SDL_RenderClear(render);
		
		for(auto it=effectInstanceList->begin();it!=effectInstanceList->end();++it)
		{
			it->second->draw();
		}
		
		drawConnections();
		effectCreator.draw(SCREEN_WIDTH-effectCreator.getWidth()-20, 0);
		
		SDL_RenderPresent(render);
	}
	
	quitSDL();
	
	OSCConn::quitServer();
	fprintf(stderr, "Done\n");
}