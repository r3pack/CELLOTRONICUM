#include "graphics.h"
#include "effects.h"
#include "controllers.h"
#include "drawables.h"

SDL_Window *window;
SDL_Renderer *render;
SDL_Event event;

TTF_Font *font;

TTF_Font *monoFont;

void initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		exit(1);
	}

	if (!(window=SDL_CreateWindow("CELLOTRONICUM", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE)))
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
	
	monoFont=TTF_OpenFont("FreeMonoBold.ttf", 12);
	if(!monoFont)
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

void ShowAlert(const wchar_t* title, const wchar_t* text)
{
	 MessageBoxW(NULL, text, title, MB_OK);
}

void getCurrentDir(char* filename, int size)
{
	GetCurrentDirectory(size, filename);
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
	ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_NOCHANGEDIR|OFN_READONLY|OFN_EXPLORER;
	GetOpenFileName(&ofn);
	
	while (SDL_PollEvent(&event)) {}
	#else
		printf("Enter file to load: ");
		fgets(filename, size, stdin);
        for(int i=strlen(filename)-1;i>=0;--i)
        {
            if(filename[i]!='\n' && filename[i]!=' ') {filename[i+1]='\0'; break;}
        }
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
	ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT|OFN_EXPLORER;
	GetSaveFileName(&ofn);
	
	while (SDL_PollEvent(&event)) {}
	#else
		printf("Enter file to save: ");
		fgets(filename, size, stdin);
        for(int i=strlen(filename)-1;i>=0;--i)
        {
            if(filename[i]!='\n' && filename[i]!=' ') {filename[i+1]='\0'; break;}
        }
	#endif
}

void setColor(SDL_Color color)
{
	SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
}
	
SDL_Texture* generateText(const char* text, SDL_Color color)
{
	SDL_Surface* text_surface=TTF_RenderUTF8_Blended(font, text, color);
	
	SDL_Texture *tex = SDL_CreateTextureFromSurface(render, text_surface);
	SDL_FreeSurface(text_surface);

	return tex;
}

SDL_Texture* generateVerticalText(const char* text, SDL_Color color)
{
	std::vector <SDL_Texture*> glyphs;
	
	int w=0,h=0;
	
	
	for(int i=0;text[i]!='\0';++i)
	{
		SDL_Surface* text_surface=TTF_RenderGlyph_Blended(monoFont, text[i], color);
		SDL_Texture *tex = SDL_CreateTextureFromSurface(render, text_surface);
		
		
		w=std::max(w, text_surface->w);
		
		int miny, maxy;
		if(text[i]=='_')
		{miny=1; maxy=11;}
		else
		TTF_GlyphMetrics(font, text[i], NULL, NULL, &miny, &maxy, NULL);
		
		h+=maxy-miny+3;
		
		SDL_FreeSurface(text_surface);
		
		glyphs.push_back(tex);
	}

	SDL_Texture *tex=SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
	
	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND); 
	SDL_SetRenderTarget(render, tex);
	
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
	SDL_RenderClear(render);
	
	int p=0;
	for(int i=0;i<glyphs.size();++i)
	{
		int texW, texH;
		SDL_QueryTexture(glyphs[i], NULL, NULL, &texW, &texH);
		
		int miny, maxy;
		if(text[i]=='_')
		{miny=1; maxy=11;}
		else
		TTF_GlyphMetrics(font, text[i], NULL, NULL, &miny, &maxy, NULL);
		
		SDL_Rect glyphRect;
		glyphRect.y=p;
		glyphRect.x=0;//(w-texW)/2;
		glyphRect.w=texW;
		glyphRect.h=texH;
		p+=maxy-miny+3;
		
		if(text[i]!='_')
		SDL_RenderCopy(render, glyphs[i], NULL, &glyphRect);
		
		SDL_DestroyTexture(glyphs[i]);
	}
	
	SDL_SetRenderTarget(render, NULL);
	return tex;

}

int getFontHeight()
{
	return TTF_FontHeight(font);
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

void drawWindow(int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x=x; rect.y=y; rect.w=w; rect.h=h;
	setColor(COLOR_WIDOW_BACKGROUND);
	SDL_RenderFillRect(render, &rect);
	setColor(COLOR_WIDOW_BORDER_TOP);
	SDL_RenderDrawLine(render, x, y, x, y+h);
	SDL_RenderDrawLine(render, x, y, x+w, y);
	setColor(COLOR_WIDOW_BORDER_BOTTOM);
	SDL_RenderDrawLine(render, x, y+h, x+w, y+h);
	SDL_RenderDrawLine(render, x+w, y, x+w, y+h);
	
	rect.x+=1; rect.y+=1;
	rect.w-=1; rect.h-=1;
	setColor(COLOR_WIDOW_BORDER);
	SDL_RenderDrawRect(render, &rect);
}

SDL_Color getDarkerColor(SDL_Color color)
{
	color.r=(color.r+127)/2;
	color.g=(color.g+127)/2;
	color.b=(color.b+127)/2;
	return color;
}

