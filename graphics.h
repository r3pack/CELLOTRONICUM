#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <map>
#include <set>
#include <cmath>

extern SDL_Window *window;
extern SDL_Renderer *render;
extern SDL_Event event;

const int SCREEN_WIDTH=1824;
const int SCREEN_HEIGHT=1024;

void initSDL();

void quitSDL();

SDL_Texture* loadTexture(const char* filename);

SDL_Texture* generateText(const char* text, SDL_Color color={0,0,0});

void drawTexture(SDL_Texture* tex, int x, int y);

enum BusType{
	BT_INBUS,
	BT_OUTBUS
};

class Effect;

class Bus;

extern std::map <int, Bus*> busList;

std::set <std::pair <Bus*, Bus*> >* getConnections();

std::pair <Bus*, Bus*> getLastConnection();

void drawConnections();

enum MouseEvent{
	ME_PRESS,
	ME_REPEAT,
	ME_RELEASE
};


class Button{
	int posX, posY;
	int symbol;
	
	public:
	static constexpr int size=15;
	
	Button(int X, int Y, int s): posX(X), posY(Y), symbol(s) {}
	
	void setSymbol(int s) {symbol=s;}
	
	void draw()
	{
		SDL_Rect rect;
		rect.x = posX;
		rect.y = posY;
		rect.w = size;
		rect.h = size;
		
		SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
		SDL_RenderFillRect(render, &rect);
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		SDL_RenderDrawRect(render, &rect);
		
		switch (symbol)
		{
			case 0:
			SDL_RenderDrawLine(render, posX, posY, posX+size-2, posY+size/2);
			SDL_RenderDrawLine(render, posX, posY+size-2, posX+size-2, posY+size/2);
			break;
			case 1:
			SDL_RenderDrawLine(render, posX+size/4, posY+size/4, posX+size/4, posY+3*size/4);
			SDL_RenderDrawLine(render, posX+3*size/4, posY+size/4, posX+3*size/4, posY+3*size/4);
			break;
			case 2:
			SDL_RenderDrawLine(render, posX, posY, posX+size, posY+size);
			SDL_RenderDrawLine(render, posX, posY+size, posX+size, posY);
			break;
		}
	}
	
	void move(int X, int Y)
	{
		posX+=X;
		posY+=Y;
	}
	
	bool receiveClick(int X, int Y, MouseEvent me)
	{
		X-=posX; Y-=posY;
		if(X>=0 && X<=size && Y>=0 && Y<=size && me==ME_PRESS) return true;
		return false;
	}
};


class Bus{
	static int lastId;
    int id;
    
    bool clicked=false;
   
    int posX, posY;
	
	BusType type;
	
	Effect* effect;
	int argument;
	
	public:
	static int lastClicked;
	
	static constexpr int size=15;
	
	int getId() {return id;}
	Effect* getEffect() {return effect;}
	
	int getArg() {return argument;}
	
	int getType() {return type;}
	
	Bus(int X, int Y, BusType t, Effect* e, int a)
	{
		effect=e;
		argument=a;
		posX=X;
		posY=Y;
		type=t;
		id=lastId;
		++lastId;
		busList.insert(std::pair<int, Bus*>(id, this));
	}
	
	void removeBus()
	{
		for(auto it=getConnections()->begin();it!=getConnections()->end();)
		{
			if((*it).first==this || (*it).second==this)
			it=getConnections()->erase(it);
			else
			++it;
		}
		busList.erase(id);
	}
	
	~Bus()
	{
		removeBus();
	}
    
	void draw()
	{
		if(lastClicked!=id) clicked=false;
		
		SDL_Rect rect;
		rect.x = posX;
		rect.y = posY;
		rect.w = size;
		rect.h = size;
		if(clicked)
			SDL_SetRenderDrawColor(render, 205, 205, 255, 255);
		else
			SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
		SDL_RenderFillRect(render, &rect);
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		SDL_RenderDrawRect(render, &rect);
	}
    
	bool receiveClick(int X, int Y, MouseEvent me);
	
	void setPos(int X, int Y)
	{
		posX=X;
		posY=Y;
	}
	
	int getPosX(){return posX;}
	int getPosY(){return posY;}
	
	void move(int X, int Y)
	{
		posX+=X;
		posY+=Y;
	}
	
};



class Slider{
	float rangeBegin;
	float rangeEnd;
	int width;
	int height;
	int posX;
	int posY;
	
	int level;
	
	SDL_Texture* valueTex=NULL;
	
	float lastValue=nan("");
	
	public:
	
	Slider(int pX, int pY, int w, int h, float rB, float rE, float l):
	rangeBegin(rB), rangeEnd(rE), width(w), height(h), posX(pX), posY(pY), level(int((1.0f-(l-rB)/(rE-rB)) * float(height))) {}
	~Slider() {/*SDL_DestroyTexture(valueTex);*/}
	
	bool receiveClick(int X, int Y, MouseEvent me)
	{
		if(me!=ME_PRESS && me!=ME_REPEAT) return false;
		X-=posX;
		Y-=posY;
		if(X>=0 && X<=width && Y>=0 && Y<=height)
		{
			level=Y;
			return true;
		}
		return false;
	}
	
	float getValue()
	{
		float normalizedLevel=1.0f-(float(level)/float(height));
		return rangeBegin+(rangeEnd-rangeBegin)*normalizedLevel;
	}
	
	void setPos(int X, int Y)
	{
		posX=X;
		posY=Y;
	}
	
	void move(int X, int Y)
	{
		posX+=X;
		posY+=Y;
	}
	
	int getPosX(){return posX;}
	int getPosY(){return posY;}
	
	void draw()
	{
		SDL_Rect rect1;
		rect1.x = posX;
		rect1.y = posY;
		rect1.w = width;
		rect1.h = height;
		SDL_Rect rect2=rect1;
		rect2.y+=level;
		rect2.h-=level;
		
		
		SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
		SDL_RenderFillRect(render, &rect1);
		SDL_SetRenderDrawColor(render, 205, 205, 255, 255);
		SDL_RenderFillRect(render, &rect2);
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		SDL_RenderDrawRect(render, &rect1);
		
		if(!(lastValue>=(getValue()-0.01) && lastValue<=(getValue()+0.01)))
		{
			SDL_DestroyTexture(valueTex);
			std::ostringstream buff;
			buff.setf(std::ios::fixed, std:: ios::floatfield);
			buff.precision(2);
			buff<<getValue();
			
			valueTex=generateText(buff.str().c_str());
			lastValue=getValue();
		}
		
		int w, h;
		SDL_QueryTexture(valueTex, NULL, NULL, &w, &h);
		
		SDL_Rect valueRect;
		valueRect.y=posY+level-h;
		valueRect.x=posX+width/2-w/2;
		valueRect.w=w;
		valueRect.h=h;
		
		SDL_RenderCopy(render, valueTex, NULL, &valueRect);
	}
	
	
};
#endif
