#include <cstdio>
#include <cstring>
#include <chrono>
#include <thread>
#include "osc.h"
#include "effects.h"
#include "effectsdef.h"
#include "graphics.h"
#include "controllersdef.h"

EffectCreator effectCreator;

void waitFor(int ms)
{
	std::chrono::milliseconds dura(ms);
	std::this_thread::sleep_for(dura);
}

char fileStr[MAX_PATH];

bool checkInputs()
{
	bool quit = false;
	
	auto effectInstanceList=getEffectInstanceList();
	
	auto controllerInstanceList=getControllerInstanceList();

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				quit = true;
			break;
			case SDL_MOUSEBUTTONDOWN:
				{
					int x=event.button.x;
					int y=event.button.y;
					if(event.button.button==SDL_BUTTON_LEFT)
					{
						for(auto it=effectInstanceList->rbegin();it!=effectInstanceList->rend();++it)
						{
							if(it->second->receiveClick(x, y, ME_PRESS))break;
						}
						
						for(auto it=controllerInstanceList->rbegin();it!=controllerInstanceList->rend();++it)
						{
							if(it->second->receiveClick(x, y, ME_PRESS))break;
						}
					}
					else
					if(event.button.button==SDL_BUTTON_RIGHT)
					{
						for(auto it=effectInstanceList->rbegin();it!=effectInstanceList->rend();++it)
						{
							if(it->second->receiveSecondClick(x, y, ME_PRESS))break;
						}
						
						for(auto it=controllerInstanceList->rbegin();it!=controllerInstanceList->rend();++it)
						{
							if(it->second->receiveSecondClick(x, y, ME_PRESS))break;
						}
					}
					else
					if(event.button.button==SDL_BUTTON_MIDDLE)
					{
						for(auto it=effectInstanceList->rbegin();it!=effectInstanceList->rend();)
						{
							auto it2=it;
							++it;
							if(it2->second->receiveThridClick(x, y, ME_PRESS))break;
						}
						
						for(auto it=controllerInstanceList->rbegin();it!=controllerInstanceList->rend();++it)
						{
							auto it2=it;
							++it;
							if(it2->second->receiveThridClick(x, y, ME_PRESS))break;
						}
					}
				}
			break;
			case SDL_MOUSEBUTTONUP:
				{
					int x=event.button.x;
					int y=event.button.y;
					if(event.button.button==SDL_BUTTON_LEFT)
					{
						for(auto it=effectInstanceList->rbegin();it!=effectInstanceList->rend();++it)
						{
							it->second->receiveClick(x, y, ME_RELEASE);
						}
						for(auto it=controllerInstanceList->rbegin();it!=controllerInstanceList->rend();++it)
						{
							it->second->receiveClick(x, y, ME_RELEASE);
						}
					}
					else
					if(event.button.button==SDL_BUTTON_RIGHT)
					{
						for(auto it=effectInstanceList->rbegin();it!=effectInstanceList->rend();++it)
						{
							it->second->receiveSecondClick(x, y, ME_RELEASE);
						}
						for(auto it=controllerInstanceList->rbegin();it!=controllerInstanceList->rend();++it)
						{
							it->second->receiveSecondClick(x, y, ME_RELEASE);
						}
					}
					else
					if(event.button.button==SDL_BUTTON_MIDDLE)
					{
						for(auto it=effectInstanceList->rbegin();it!=effectInstanceList->rend();)
						{
							auto it2=it;
							++it;
							it2->second->receiveThridClick(x, y, ME_RELEASE);
						}
						for(auto it=controllerInstanceList->rbegin();it!=controllerInstanceList->rend();++it)
						{
							auto it2=it;
							++it;
							it2->second->receiveThridClick(x, y, ME_RELEASE);
						}
					}
				}
			break;
			case SDL_MOUSEMOTION:
				{
					int x=event.button.x;
					int y=event.button.y;
					if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
					{
						for(auto it=effectInstanceList->rbegin();it!=effectInstanceList->rend();++it)
						{
							if(it->second->receiveClick(x, y, ME_REPEAT))break;
						}
						for(auto it=controllerInstanceList->rbegin();it!=controllerInstanceList->rend();++it)
						{
							if(it->second->receiveClick(x, y, ME_REPEAT))break;
						}
					}
					else
					if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
					{
						for(auto it=effectInstanceList->rbegin();it!=effectInstanceList->rend();++it)
						{
							if(it->second->receiveSecondClick(x, y, ME_REPEAT))break;
						}
						for(auto it=controllerInstanceList->rbegin();it!=controllerInstanceList->rend();++it)
						{
							if(it->second->receiveSecondClick(x, y, ME_REPEAT))break;
						}
					}
					else
					if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE))
					{
						for(auto it=effectInstanceList->rbegin();it!=effectInstanceList->rend();)
						{
							auto it2=it;
							++it;
							if(it2->second->receiveThridClick(x, y, ME_REPEAT))break;
						}
						for(auto it=controllerInstanceList->rbegin();it!=controllerInstanceList->rend();++it)
						{
							auto it2=it;
							++it;
							if(it2->second->receiveThridClick(x, y, ME_REPEAT))break;
						}
					}
				}
			break;
			case SDL_KEYDOWN:
				
				auto it=effectInstanceList->begin();
				for(;it!=effectInstanceList->end();++it)
				{
					if(it->second->receiveKeyboardEvent(event.key.keysym.scancode))break;
				}
				
				if(it==effectInstanceList->end())
				effectCreator.receiveKeyboardEvent(event.key.keysym.scancode);
				
				const Uint8 *state = SDL_GetKeyboardState(NULL);
			
				if(state[SDL_SCANCODE_LCTRL] && state[SDL_SCANCODE_S])
				{
					getSaveFile(fileStr, MAX_PATH);
					Effect::saveToFile(fileStr);
				}
				else if(state[SDL_SCANCODE_LCTRL] && state[SDL_SCANCODE_L])
				{
					Effect::saveToFile("session_before_load.cello");
					Effect::clearAll();
					getOpenFile(fileStr, MAX_PATH);
					Effect::loadFromFile(fileStr);
				}
				else if(state[SDL_SCANCODE_LCTRL] && state[SDL_SCANCODE_LALT] && state[SDL_SCANCODE_E])
				{
					Effect::saveToFile("session_before_erase.cello");
					Effect::clearAll();
				}
				else if(state[SDL_SCANCODE_LALT] && state[SDL_SCANCODE_R])
				{
					OSCConn::recordToFile();
				}
				else if(!state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_LCTRL] && state[SDL_SCANCODE_R])
				{
					OSCConn::startRecord();
				}
				else if(state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_LCTRL] && state[SDL_SCANCODE_R])
				{
					OSCConn::stopRecord();
				}
				
			break;
		}
	}
	
	return quit;
}

inline bool existsTest(const char* name) 
{
    if(FILE *file = fopen(name, "r")) 
	{
        fclose(file);
        return true;
    } 
	else
    return false;
}

const char* SC_PATH_FILE="scpath.txt";

const char* SC_MAIN_FILE="sc\\main.scd";

char sclangPath[MAX_PATH];

bool launchSuperCollider()
{
	char currentDir[MAX_PATH];
	getCurrentDir(currentDir, MAX_PATH);
	
	char sclangPathDirectory[MAX_PATH];
	
	for(int i=strlen(sclangPath)-1;i>=1;--i)
	{
		if((sclangPath[i]=='/' || sclangPath[i]=='\\') && sclangPath[i-1]!='\\')
		{
			strncpy(sclangPathDirectory, sclangPath, i);
			sclangPathDirectory[i]='\0';
			break;
		}
		if(i==1) return false;
	}
	
	char tab[MAX_PATH*2+10];
	sprintf(tab, "-d \"%s\" \"%s\\%s\"", sclangPathDirectory, currentDir, SC_MAIN_FILE);
	
	//przykładowe polecenie: "C:\Program Files (x86)\SuperCollider-3.6.6\sclang.exe" -d "C:\Program Files (x86)\SuperCollider-3.6.6" "C:\Users\praktykant\CELLOTRONICUM\main.scd"
	
	printf("Executing: %s %s...\n", sclangPath, tab);
	
	ShellExecute(NULL, "open", sclangPath, tab, NULL, SW_SHOWDEFAULT);
	
	return true;
}

void saveSCPath()
{
	FILE* pathFile=fopen(SC_PATH_FILE, "w");
	fprintf(pathFile, "%s", sclangPath);
	fclose(pathFile);
}

bool getSCPath()
{
	FILE* pathFile=fopen(SC_PATH_FILE, "r");
	if(pathFile!=NULL)
	{
		fgets(sclangPath, MAX_PATH, pathFile);
		if(existsTest(sclangPath))
		{
			return true;
		}
	}
	fclose(pathFile);
	
	ShowAlert(L"SuperCollider Path", L"To launch program you must provide path to sclang in SuperCollider folder.");
	getOpenFile(sclangPath, MAX_PATH);
	
	printf("Selected path: %s\n", sclangPath);
	
	if(existsTest(sclangPath))
	{
		return true;
	}
	else
	{
		ShowAlert(L"SuperCollider Path", L"Patch to sclang is incorrect!");
		return false;
	}
}

#undef main
int main (int argc, char** argv)
{
	if(getSCPath() && launchSuperCollider());
	else
	{
		fprintf(stderr, "Cant get sclang patch - exiting\n");
		exit(0);
	}
	
	if(argc>1)
	{
		OSCConn::setServer(argv[1]);
		if(argc>2)
		{
			OSCConn::setPort(atoi(argv[2])); 
		}
	}
	
	registerEffects();
	registerControllers();
	
	if(!OSCConn::connect()) exit(1);
	
	if(!OSCConn::startServer()) exit(2);
	
	if(!checkEffectsList()) {OSCConn::quitServer(); exit(3);}
	
	saveSCPath();
	
	initSDL();
	
	effectCreator.init();
	
	auto effectInstanceList=getEffectInstanceList();
	
	auto controllerInstanceList=getControllerInstanceList();
	
	
	while (!checkInputs())
	{
		for(auto it=controllerInstanceList->rbegin();it!=controllerInstanceList->rend();++it)
		{
			it->second->step();
		}
		
		setColor(COLOR_CLEARCOLOR);
		SDL_RenderClear(render);
		
		for(auto it=effectInstanceList->begin();it!=effectInstanceList->end();++it)
		{
			it->second->doSomething();
		}
		
		for(auto it=effectInstanceList->begin();it!=effectInstanceList->end();++it)
		{
			it->second->draw();
		}
		
		for(auto it=controllerInstanceList->rbegin();it!=controllerInstanceList->rend();++it)
		{
			it->second->draw();
		}

		drawConnections();
		
		int screen_width;
		SDL_GetWindowSize(window, &screen_width, NULL);

		effectCreator.draw(screen_width-EffectCreator::menu_period, 0);
		
		SDL_RenderPresent(render);
	}
	
	Effect::saveToFile("last_session.cello");
	
	Effect::clearAll();
	
	quitSDL();
	
	OSCConn::quitServer();
	fprintf(stderr, "Done\n");
}