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

void getOpenFile(char* filename, int size);
void getSaveFile(char* filename, int size);

SDL_Texture* loadTexture(const char* filename);

SDL_Texture* generateText(const char* text, SDL_Color color={0,0,0});

void drawTexture(SDL_Texture* tex, int x, int y);

enum BusType{
	BT_INBUS,
	BT_OUTBUS
};

class Effect;
class Bus;
class ControllBus;
class Controller;

extern std::map <int, Bus*> busList;

extern std::map <int, ControllBus*> controllBusList;

std::set <std::pair <Bus*, Bus*> >* getConnections();

void drawConnections();

enum MouseEvent{
	ME_PRESS,
	ME_REPEAT,
	ME_RELEASE
};

class Drawable{
	public:
	virtual void draw() = 0;
	virtual void setPos(int X, int Y) = 0;
	virtual void move(int X, int Y) = 0;
	virtual int getPosX() = 0;
	virtual int getPosY() = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual bool receiveClick(int X, int Y, MouseEvent me) = 0;
	virtual ~Drawable() {}
};

class Point : public Drawable{
	int posX, posY;
	
	public:
	void draw() {}
	
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
	
	int getWidth() {return 0;}
	int getHeight() {return 0;}
	
	bool receiveClick(int X, int Y, MouseEvent me) {return false;}
	
	Point(int X, int Y): posX(X), posY(Y) {}
};

class Button : public Drawable{
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
		
		switch(symbol)
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
	
	bool receiveClick(int X, int Y, MouseEvent me)
	{
		X-=posX; Y-=posY;
		if(X>=0 && X<=size && Y>=0 && Y<=size && me==ME_PRESS) return true;
		return false;
	}
	
	int getWidth() {return size;}
	int getHeight() {return size;}
};


class Bus : public Drawable{
	static int lastId;
    int id;
    
    bool clicked=false;
   
    int posX, posY;
	
	BusType type;
	
	Effect* effect;
	int argument;
	
	bool used=false;
	
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
			{
				(*it).first->used=false;
				(*it).second->used=false;
				it=getConnections()->erase(it);
			}
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
    
	bool receiveClick(int X, int Y, MouseEvent me)
	{
		X-=posX;
		Y-=posY;
		if(X>=0 && X<=size && Y>=0 && Y<=size && me==ME_PRESS)
		{
			return setClicked();
		}
		return false;
	}
	
	bool setClicked();
	
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
	
	int getWidth() {return size;}
	int getHeight() {return size;}
	
};


class ControllBus : public Drawable{
	static int lastId;
    int id;
    
    bool clicked=false;
   
    int posX, posY;
	
	BusType type;
	
	Controller* controller;
	
	bool used=false;
	
	public:
	static int lastClicked;
	
	static constexpr int size=15;
	
	Controller* getController() {return controller;}
	
	int getType() {return type;}
	
	ControllBus(int X, int Y, BusType t, Controller* c)
	{
		controller=c;
		posX=X;
		posY=Y;
		type=t;
		id=lastId;
		++lastId;
		controllBusList.insert(std::pair<int, ControllBus*>(id, this));
	}
	
	void removeBus()
	{
		controllBusList.erase(id);
	}
	
	~ControllBus()
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
			SDL_SetRenderDrawColor(render, 205, 255, 205, 255);
		else
			SDL_SetRenderDrawColor(render, 255, 255, 205, 255);
		SDL_RenderFillRect(render, &rect);
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		SDL_RenderDrawRect(render, &rect);
	}
    
	bool receiveClick(int X, int Y, MouseEvent me)
	{
		X-=posX;
		Y-=posY;
		if(X>=0 && X<=size && Y>=0 && Y<=size && me==ME_PRESS)
		{
			return setClicked();
		}
		return false;
	}
	
	bool setClicked();
	
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
	
	int getWidth() {return size;}
	int getHeight() {return size;}
	
};



class Slider : public Drawable{
	float rangeBegin;
	float rangeEnd;
	int width;
	int height;
	int posX;
	int posY;
	
	int level;
	
	SDL_Texture* valueTex=NULL;
	
	float lastValue;
	float value;
	
	public:
	
	Slider(int pX, int pY, int w, int h, float rB, float rE, float l):
	rangeBegin(rB), rangeEnd(rE), width(w), height(h), posX(pX), posY(pY), level(int((1.0f-(l-rB)/(rE-rB)) * float(height))), value(l), lastValue(l) 
	{
		std::ostringstream buff;
		buff.setf(std::ios::fixed, std:: ios::floatfield);
		buff.precision(2);
		buff<<getValue();
		
		valueTex=generateText(buff.str().c_str());
	}
	~Slider() {SDL_DestroyTexture(valueTex);}
	
	bool receiveClick(int X, int Y, MouseEvent me)
	{
		if(me!=ME_PRESS && me!=ME_REPEAT) return false;
		X-=posX;
		Y-=posY;
		if(X>=0 && X<=width && Y>=-15 && Y<=height+15)
		{
			if(Y<0) Y=0;
			else
			if(Y>height) Y=height;
			level=Y;
			float normalizedLevel=1.0f-(float(level)/float(height));
			value=rangeBegin+(rangeEnd-rangeBegin)*normalizedLevel;
			
			if(!(lastValue>=(value-0.001) && lastValue<=(value+0.001)))
			{
				SDL_DestroyTexture(valueTex);
				std::ostringstream buff;
				buff.setf(std::ios::fixed, std:: ios::floatfield);
				buff.precision(2);
				buff<<getValue();
				
				valueTex=generateText(buff.str().c_str());
				lastValue=getValue();
			}
			return true;
		}
		return false;
	}
	
	float getValue()
	{
		return value;
	}
	
	void setValue(float v)
	{
		value=v;
	}
	
	void setNormalizedValue(float nv)
	{
		value=(rangeEnd-rangeBegin)*nv+rangeBegin;
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
		
		int w, h;
		SDL_QueryTexture(valueTex, NULL, NULL, &w, &h);
		
		SDL_Rect valueRect;
		valueRect.y=posY+level-h;
		valueRect.x=posX+width/2-w/2;
		valueRect.w=w;
		valueRect.h=h;
		
		SDL_RenderCopy(render, valueTex, NULL, &valueRect);
	}
	
	int getWidth() {return width;}
	int getHeight() {return height;}
	
};
#endif
