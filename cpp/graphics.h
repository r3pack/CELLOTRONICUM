#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <map>
#include <set>
#include <cmath>
#include "colors.h"

extern SDL_Window *window;
extern SDL_Renderer *render;
extern SDL_Event event;

const int SCREEN_WIDTH=1440;
const int SCREEN_HEIGHT=900;

#ifndef MAX_PATH
	#define MAX_PATH 1024
#endif

///Inicializuje SDL-a i SDL_ttf, a także ładuje fonty
void initSDL();

///Deinicializuje SDL-a i SDL_ttf
void quitSDL();

///FUNKCJE ZALEŻNE OD SYSTEMU START!!!
///////////////////////////////////////
///wyświetla alert o podanym tytule i treści
void ShowAlert(const wchar_t* title, const wchar_t* text);
///Zapisuje do string katalog w którym znajduje się ten program
void getCurrentDir(char* filename, int size);

///Pokazuje okno do wybrania pliku do otwarcia i zapisuje wybrany plik do stringa
void getOpenFile(char* filename, int size);
///Pokazuje okno do wybrania pliku do zapisania i zapisuje wybrany plik do stringa
void getSaveFile(char* filename, int size);
////////////////////////////////////////
///FUNKCJE ZALEŻNE OD SYSTEMU STOP!!!

///Ładuje teksture z pliku (nieużywane)
SDL_Texture* loadTexture(const char* filename);

///ustawia kolor w którym będą rysowane linie, kwadraty i inne
void setColor(SDL_Color color);

///zwraca wysokość używanej czcionki
int getFontHeight();

///generuje teksture z tekstem
SDL_Texture* generateText(const char* text, SDL_Color color=COLOR_TEXT);
///generuje teksture z pionowym tekstem
SDL_Texture* generateVerticalText(const char* text, SDL_Color color=COLOR_TEXT);

///rysuje teksturę w podanym miejscu
void drawTexture(SDL_Texture* tex, int x, int y);

///rysuje okno dla efektu lub kontrolera
void drawWindow(int x, int y, int w, int h);

///Zwraca ciemniejszą/jaśniejszą wersję podanego koloru
SDL_Color getDarkerColor(SDL_Color color);

#endif
