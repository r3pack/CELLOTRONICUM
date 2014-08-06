#ifndef CONTROLLERS_H
#define CONTROLLERS_H
#include "graphics.h"
#include <vector>
#include <cstring>

struct cmpCStr2
{
   bool operator()(char const *a, char const *b)
   {
	  return std::strcmp(a, b) < 0;
   }
};

extern std::map <ControllBus*, Controller*> controllerByBus;

std::map <int, Controller*>* getControllerInstanceList();

std::set<const char*, cmpCStr2>* getControllerList();

struct ParamControllBus
{
	ControllBus* bus;
	int param;
	SDL_Texture* nameTex=NULL;
	ParamControllBus(ControllBus* b, int p, const char* text): bus(b), param(p) {nameTex=generateText(text);}
	
	void draw() 
	{
		bus->draw();
		int w, h;
		SDL_QueryTexture(nameTex, NULL, NULL, &w, &h);
	
		SDL_Rect nameRect;
		nameRect.x=bus->getPosX() + bus->getWidth()/2 - w/2;
		nameRect.y=bus->getPosY() + bus->getHeight(); 
		nameRect.w=w;
		nameRect.h=h;		
		
		SDL_RenderCopy(render, nameTex, NULL, &nameRect);
	}
	
	void free() {delete bus; SDL_DestroyTexture(nameTex);}
};

class Controller{
	int id;
	static int lastId;
	
	SDL_Texture* nameTex;
	
	int handlePosX, handlePosY;
	
	bool focus=false;
	
	protected:
	
	std::vector <ParamControllBus> outBuses;
	
	int posX, posY;
	
	int width=height;
	
	public:
	
	static constexpr int bus_period=30;
	static constexpr int height=50;
	
	int getId() {return id;}
	
	Controller()
	{
		id=lastId++;
		getControllerInstanceList()->insert(std::pair<int, Controller*>(id, this));
	}
	
	void initGUI(int X, int Y)
	{
		posX=X;
		posY=Y;
		nameTex=generateText(getName());
		
		for(int i=0;i<outBuses.size();++i)
		{
			ControllBus* bus=new ControllBus(X, Y, BT_OUTBUS, this);
			outBuses.push_back(ParamControllBus(bus, i, getName()));
			controllerByBus.insert(std::pair<ControllBus*, Controller*>(bus, this));
		}
	}
	
	virtual ~Controller()
	{
		for(int i=0;i<outBuses.size();++i)
		{
			controllerByBus.erase(outBuses[i].bus);
		}
		getControllerInstanceList()->erase(id);
		
		SDL_DestroyTexture(nameTex);
	}
	
	
	virtual float getValue(int id) = 0;
	virtual const char* getName() = 0;
	
	void setPos(int X, int Y)
	{
		for(int i=0;i<outBuses.size();++i)
		{
			outBuses[i].bus->move(X-posX, Y-posY);
		}
	}
	
	bool receiveClick(int X, int Y, MouseEvent me)
	{
		if(!(posX<=X && X<=posX+width && posY<=Y && Y<=posY+height)) return false;

		for(int i=0;i<outBuses.size();++i)
		{
			outBuses[i].bus->receiveClick(X, Y, me);
		}
		return true;
	}
	
	bool receiveSecondClick(int X, int Y, MouseEvent me)
	{
		if(me==ME_PRESS)
		{
			if(posX<=X && X<=posX+width && posY<=Y && Y<=posY+height)
			{
				handlePosX=X-posX;
				handlePosY=Y-posY;
				focus=true;
				return true;
			}
			else
			focus=false;
			return false;
		}
		else if(me==ME_REPEAT && focus)
		{
			setPos(X-handlePosX, Y-handlePosY);
			return true;
		}
		else if(me==ME_RELEASE)
		{
			focus=false;
			return true;
		}
		return false;
	}
	
	bool receiveThridClick(int X, int Y, MouseEvent me)
	{
		if(posX<=X && X<=posX+width && posY<=Y && Y<=posY+height && me==ME_PRESS)
		{
			for(int i=0;i<outBuses.size();++i)
			{
				outBuses[i].free();
			}
			delete this;
			return true;
		}
		else return false;
	}
	
	void draw()
	{
		SDL_Rect rect;
		rect.x = posX; rect.y = posY;
		rect.w = width;
		rect.h = height;
		SDL_SetRenderDrawColor(render, 220, 220, 220, 255);
		SDL_RenderFillRect(render, &rect);
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		SDL_RenderDrawRect(render, &rect);
	
	
		int w, h;
		SDL_QueryTexture(nameTex, NULL, NULL, &w, &h);
		
		SDL_Rect nameRect;
		nameRect.y=posY+2;
		nameRect.x=posX+width/2-w/2;
		nameRect.w=w;
		nameRect.h=h;
		
		SDL_RenderCopy(render, nameTex, NULL, &nameRect);
		
		for(int i=0;i<outBuses.size();++i)
		{
			outBuses[i].draw();
		}
		
	}
	
};

void registerController(const char* name);

#endif