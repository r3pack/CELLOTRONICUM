#include "graphics.h"
#include "effects.h"

SDL_Window *window;
SDL_Renderer *render;
SDL_Event event;

TTF_Font *font;


void initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		exit(1);
	}

	if (!(window=SDL_CreateWindow("CELLOTRONICUM", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)))
	{
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		exit(2);
	}
	
	if (!(render=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
	{
		SDL_DestroyWindow(window);
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		exit(3);
	}
	
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		exit(4);
	}
	
	font=TTF_OpenFont("FreeSans.ttf", 12);
	if(!font)
	{
		printf("TTF_OpenFont error: %s\n", TTF_GetError());
		exit(5);
	}
}
void quitSDL()
{
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}

void getOpenFile(char* filename, int size)
{
	#if defined(_MSC_VER) || defined(_WIN32)
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filename;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = size;
	ofn.lpstrFilter = "All\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir=NULL;
	ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_NOCHANGEDIR|OFN_READONLY;
	GetOpenFileName(&ofn);
	
	while (SDL_PollEvent(&event)) {}
	#else
		printf("Enter file to load: ");
		fgets(stdin, size, filename);
	#endif
}

void getSaveFile(char* filename, int size)
{
	#if defined(_MSC_VER) || defined(_WIN32)
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filename;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = size;
	ofn.lpstrFilter = "All\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir=NULL;
	ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT;
	GetSaveFileName(&ofn);
	
	while (SDL_PollEvent(&event)) {}
	#else
		printf("Enter file to save: ");
		fgets(stdin, size, filename);
	#endif
}

int Bus::lastClicked=-1;
int Bus::lastId=0;

int ControllBus::lastClicked=-1;
int ControllBus::lastId=0;

class Bus;

std::map <int, Bus*> busList;

std::map <int, ControllBus*> controllBusList;

std::set <std::pair <Bus*, Bus*> > connections;

std::set <std::pair <Bus*, Bus*> >* getConnections() {return &connections;}

void drawConnections()
{
	for(auto it=connections.begin();it!=connections.end();++it)
	{
		SDL_RenderDrawLine(render, (*it).first->getPosX()+Bus::size/2, (*it).first->getPosY()+Bus::size/2,
								   (*it).second->getPosX()+Bus::size/2, (*it).second->getPosY()+Bus::size/2);
	}
}

bool Bus::setClicked()
{
	clicked=true;
	
	if(lastClicked!=-1)
	{
		auto it=busList.find(lastClicked);
		if(it==busList.end())
		{
			fprintf(stderr, "Error: bus not found\n");
			Bus::lastClicked=-1;
			return false;
		}
		
		Bus *bus1=it->second, *bus2=this;
		
		if(bus1->getType()==BT_INBUS) std::swap(bus1, bus2);
		
		if(bus1->getType()!=BT_OUTBUS || bus2->getType()!=BT_INBUS)
		{
			if(bus1->getType()==BT_OUTBUS && bus2==bus1)
			{
				bus1->used=false;
				for(auto it=connections.begin();it!=connections.end();)
				{
					if((*it).first==bus1)
					{
						(*it).second->used=false;
						it=connections.erase(it);
					}
					else ++it;
				}
			}
			
			if(bus1->getType()==BT_INBUS && bus2==bus1)
			{
				bus1->used=false;
				for(auto it=connections.begin();it!=connections.end();++it)
				{
					if((*it).second==bus1)
					{
						(*it).first->used=false;
						connections.erase(it);
						break;
					}
				}
			}
			
			fprintf(stderr, "Error: bad buses type\n");
			Bus::lastClicked=-1;
			return false;
		}
		
		
		if(bus1->getEffect() == bus2->getEffect())
		{
			fprintf(stderr, "Error: buses come from same effect\n");
			Bus::lastClicked=-1;
			return false;
		}
		
		std::pair<std::set <std::pair<Bus*, Bus*> >::iterator, bool> connIt;
		
		if(connections.find(std::pair<Bus*, Bus*>(bus1, bus2)) != connections.end())
		{
			connections.erase(std::pair<Bus*, Bus*>(bus1, bus2));
			
			bus2->getEffect()->getArgs()[bus2->getArg()].set(OSCConn::getFreeBus());
			
			bus2->used=false;
		}
		else
		{
			if(bus2->used==true) return false;
			connIt=connections.insert(std::pair<Bus*, Bus*>(bus1, bus2));
			bus2->used=true;
			
			Effect::updateTopologicalSequence();
					
			int freebus=bus1->getEffect()->getArgs()[bus1->getArg()].getIntValue();
			
			OSCConn::deleteBus(bus2->getEffect()->getArgs()[bus2->getArg()].getIntValue());
			
			bus2->getEffect()->getArgs()[bus2->getArg()].set(freebus);
			
			bus2->getEffect()->setAndSendArgument(bus2->getArg(), freebus);
			fprintf(stderr, "Connected two buses to %d\n", freebus);
		}
		
		Bus::lastClicked=-1;
		
		return true;
	}
	else
	lastClicked=id;
	
	return false;
}

bool ControllBus::setClicked()
{
	clicked=true;
}
	
SDL_Texture* generateText(const char* text, SDL_Color color)
{
	SDL_Surface* text_surface=TTF_RenderUTF8_Blended(font, text, color);
	
	SDL_Texture *tex = SDL_CreateTextureFromSurface(render, text_surface);
	SDL_FreeSurface(text_surface);

	return tex;
}


SDL_Texture* loadTexture(const char* filename)
{
	SDL_Surface *bmp = SDL_LoadBMP(filename);
	if (!bmp){
		SDL_DestroyRenderer(render);
		SDL_DestroyWindow(window);
		printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
		SDL_Quit();
		exit(6);
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface(render, bmp);
	SDL_FreeSurface(bmp);

	return tex;
}

void drawTexture(SDL_Texture* tex, int x, int y)
{
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	SDL_Rect srcrect;
	srcrect.x = x;
	srcrect.y = y;
	srcrect.w = w;
	srcrect.h = h;
	
	SDL_RenderCopy(render, tex, NULL, &srcrect);
}

