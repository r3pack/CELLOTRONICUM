#include "graphics.h"

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

	if (!(window=SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 1024, SDL_WINDOW_SHOWN)))
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


int Bus::lastClicked=-1;
int Bus::lastId=0;

class Bus;

std::map <int, Bus*> busList;

std::set <std::pair <Bus*, Bus*> > connections;

std::pair <Bus*, Bus*> lastConnection;

std::pair <Bus*, Bus*> getLastConnection() {return lastConnection;}

void drawConnections()
{
	for(auto it=connections.begin();it!=connections.end();++it)
	{
		SDL_RenderDrawLine(render, (*it).first->getPosX()+Bus::size/2, (*it).first->getPosY()+Bus::size/2,
								   (*it).second->getPosX()+Bus::size/2, (*it).second->getPosY()+Bus::size/2);
	}
}

bool Bus::receiveClick(int X, int Y, bool begin)
{
	X-=posX;
	Y-=posY;
	if(X>=0 && X<=size && Y>=0 && Y<=size && begin)
	{
		clicked=true;
		
		printf("lastid %d id %d\n", lastClicked, getId());
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
			
			if(bus1->getType()==BT_OUTBUS) std::swap(bus1, bus2);
			
			if(bus1->getType()!=BT_INBUS || bus2->getType()!=BT_OUTBUS)
			{
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
			
			auto connIt=connections.insert(std::pair<Bus*, Bus*>(bus1, bus2));
			
			lastConnection=*(connIt.first);
			
			Bus::lastClicked=-1;
			
			return connIt.second;
		}
		else
		lastClicked=id;
		
		return false;
	}
	return false;
}

SDL_Texture* generateText(const char* text)
{
	SDL_Color color={0,0,0};
	SDL_Surface* text_surface=TTF_RenderText_Blended(font, text, color);
	
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

