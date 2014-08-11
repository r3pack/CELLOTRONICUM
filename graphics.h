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

const int SCREEN_WIDTH=1824;
const int SCREEN_HEIGHT=1024;

void initSDL();

void quitSDL();

void getOpenFile(char* filename, int size);
void getSaveFile(char* filename, int size);

SDL_Texture* loadTexture(const char* filename);

void setColor(SDL_Color color);

SDL_Texture* generateText(const char* text, SDL_Color color=COLOR_TEXT);

void drawTexture(SDL_Texture* tex, int x, int y);

void drawWindow(int x, int y, int w, int h);

SDL_Color getDarkerColor(SDL_Color color);

#endif
