#ifndef CONTROLLERS_H
#define CONTROLLERS_H
#include "graphics.h"
#include "drawables.h"
#include <list>
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
	friend class ControllBus;
	friend class Slider;
	friend class Effect;

	int id;
	static int lastId;
	
	SDL_Texture* nameTex;
	
	int handlePosX, handlePosY;
	
	bool focus=false;
	bool paused=false;
	
	Button* pauseButton;
	
	protected:
	
	std::vector <ParamControllBus> outBuses;
	
	std::list <std::pair<int, Slider*> > controlledSliders;
	
	int posX, posY;
	
	int width=0;
	
	public:
	static const int bus_period=35;
	static const int top_padding=35;
	static const int bottom_padding=30;
	
	
	virtual float getValue(int id) = 0;
	virtual bool valueIsReady(int id) {return true;}
	virtual const char* getName() = 0;
	virtual int getBusCount() = 0;
	virtual const char* const* getBusNames() = 0;
	
	static constexpr int height=top_padding+bottom_padding+ControllBus::size;
	
	int getId() {return id;}
	
	bool isPaused() {return paused;}
	
	Controller()
	{
		id=lastId++;
		getControllerInstanceList()->insert(std::pair<int, Controller*>(id, this));
	}
	
	void step()
	{
		if(paused) return;
		for(auto it=controlledSliders.begin();it!=controlledSliders.end();++it)
		{
			if(valueIsReady(it->first))
			it->second->setNormalizedValue(getValue(it->first));
		}
	}
	
	void initGUI(int X, int Y)
	{
		posX=X;
		posY=Y;
		nameTex=generateText(getName());
		
		pauseButton=new Button(X+2, Y+2, 0);
		
		int x=bus_period;
		
		int busCount=getBusCount();
		for(int i=0;i<busCount;++i)
		{
			ControllBus* bus=new ControllBus(posX+x, posY+top_padding, BT_OUTBUS, this);
			outBuses.push_back(ParamControllBus(bus, i, getBusNames()[i]));
			controllerByBus.insert(std::pair<ControllBus*, Controller*>(bus, this));
			x+=bus_period+ControllBus::size;
		}
		width=x;
	}
	
	virtual ~Controller()
	{
		for(int i=0;i<outBuses.size();++i)
		{
			controllerByBus.erase(outBuses[i].bus);
		}
		
		for(auto it=controlledSliders.begin();it!=controlledSliders.end();++it)
		{
			it->second->controlledBy=NULL;
		}
		
		getControllerInstanceList()->erase(id);
		
		SDL_DestroyTexture(nameTex);
		
		delete pauseButton;
	}
	
	void setPos(int X, int Y)
	{
		for(int i=0;i<outBuses.size();++i)
		{
			outBuses[i].bus->move(X-posX, Y-posY);
		}
		pauseButton->move(X-posX, Y-posY);
		posX=X;
		posY=Y;
	}
	
	bool receiveClick(int X, int Y, MouseEvent me)
	{
		if(!(posX<=X && X<=posX+width && posY<=Y && Y<=posY+height)) return false;

		if(pauseButton->receiveClick(X, Y, me)) 
		{
			paused=!paused;
		}
		
		for(int i=0;i<outBuses.size();++i)
		{
			outBuses[i].bus->receiveClick(X, Y, me);
		}
		return true;
	}
	
	bool receiveSecondClick(int X, int Y, MouseEvent me)
	{
		for(int i=0;i<outBuses.size();++i)
		{
			if(outBuses[i].bus->receiveSecondClick(X, Y, me)) return true;
		}
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
	
	void saveData(FILE* file);
	
	void loadData(char* str);
	
	void draw()
	{
		drawWindow(posX, posY, width, height);
	
		int w, h;
		SDL_QueryTexture(nameTex, NULL, NULL, &w, &h);
		
		SDL_Rect nameRect;
		nameRect.y=posY+2;
		nameRect.x=posX+width/2-w/2;
		nameRect.w=w;
		nameRect.h=h;
		
		SDL_RenderCopy(render, nameTex, NULL, &nameRect);
		
		pauseButton->setSymbol(int(isPaused()));
		pauseButton->draw();
		
		for(int i=0;i<outBuses.size();++i)
		{
			outBuses[i].draw();
		}
		
		for(auto it=controlledSliders.begin();it!=controlledSliders.end();++it)
		{
			ControllBus* bus=outBuses[it->first].bus;
			Slider* slider=it->second;
			
			if(bus->getPosY()+ControllBus::size/2 <= slider->getPosY() + slider->getHeight()/2)
			SDL_RenderDrawLine(render, bus->getPosX()+ControllBus::size/2, bus->getPosY()+ControllBus::size/2,
								       slider->getPosX()+slider->getWidth()/2,  slider->getPosY());
			else
			SDL_RenderDrawLine(render, bus->getPosX()+ControllBus::size/2, bus->getPosY()+ControllBus::size/2,
								       slider->getPosX()+slider->getWidth()/2,  slider->getPosY()+slider->getHeight());
		}
		
	}
	
};

void registerController(const char* name);

#endif