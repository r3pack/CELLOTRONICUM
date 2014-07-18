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

