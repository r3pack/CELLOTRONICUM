#ifndef CONTROLLERS_H
#define CONTROLLERS_H
#include "graphics.h"
#include "drawables.h"
#include <list>
#include <vector>
#include <cstring>


///Komparator porównujący 2 cstringi
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


///Struktura zawierająca ControllBus i taksturę z wyrenderowaną nazwą
struct ParamControllBus
{
	ControllBus* bus; ///wskaźnik na bus kontrolujący

	SDL_Texture* nameTex=NULL; ///tekstura z nazwą
	ParamControllBus(ControllBus* b, const char* text): bus(b) {nameTex=generateText(text);}
	
	///rysuje bus kontrolujący i jego nazwę
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
	
	///zwalnia pamięc 
	void free() {delete bus; SDL_DestroyTexture(nameTex);}
};

class Controller{
	friend class ControllBus;
	friend class ValueGifter;
	friend class Slider;
	friend class GradualSlider;
	friend class Effect;

	int id; /// numer identyfikacyjny kontrolera
	static int lastId; /// ostatnio przydzielone id
	
	SDL_Texture* nameTex; /// tekstura z nazwą okna
	
	int handlePosX, handlePosY; ///miejsce ciągnięcia okna myszą
	
	bool focus=false; ///czy okno jest ciągnięte
	bool paused=false; ///czy kontroler jest zpauzowany
	
	Button* pauseButton; ///przycisk od pauzowania efektu
	
	protected:
	
	std::vector <ParamControllBus> outBuses; ///busy wyjściowe
	
	std::list <std::pair<int, ValueGifter*> > controlledValueGifters; ///wektor z informacjami które busy kontrolują które obiekty rysowalne kontrolujące parametry (suwaki)
	
	int posX, posY; ///pozycja okna (lewy górny róg)
	
	int width=0; ///szerokość okna
	
	public:
	static const int bus_period=35; ///odległość pozioma między busami oraz jednocześnie lewy i prawy margines
	static const int top_padding=35; ///górny margines
	static const int bottom_padding=30; ///dolny margines
	
	///zwraca wartość busa o zadanym id (do implementacji przez kontroler)
	virtual float getValue(int id) = 0;
	///zwraca czy bus jest gotowy do zwrócenia wartości (do implementacji przez kontroler - domyślnie jest zawsze dostępny)
	virtual bool valueIsReady(int id) {return true;}
	///zwraca nazwę kontrolera (do implementacji przez kontroler)
	virtual const char* getName() = 0;
	///zwraca ilość busów (do implementacji przez kontroler)
	virtual int getBusCount() = 0;
	///zwraca nazwy kolejnych busów (do implementacji przez kontroler)
	virtual const char* const* getBusNames() = 0;
	
	static constexpr int height=top_padding+bottom_padding+ControllBus::size; ///domyślna wysokość kontrolera
	
	///zwraca unikalne id kontrolera
	int getId() {return id;}
	
	///zwraca czy kontroler jest zpauzowany
	bool isPaused() {return paused;}
	
	Controller()
	{
		id=lastId++;
		getControllerInstanceList()->insert(std::pair<int, Controller*>(id, this));
	}
	
	///ustawia odpowiednie wartości kontrolowanym obiektom rysowalnym
	void step()
	{
		if(paused) return;
		for(auto it=controlledValueGifters.begin();it!=controlledValueGifters.end();++it)
		{
			if(valueIsReady(it->first))
			it->second->setNormalizedValue(getValue(it->first));
		}
	}
	
	///inicializuje GUIs
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
			outBuses.push_back(ParamControllBus(bus, getBusNames()[i]));
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
		
		for(auto it=controlledValueGifters.begin();it!=controlledValueGifters.end();++it)
		{
			it->second->controlledBy=NULL;
		}
		
		getControllerInstanceList()->erase(id);
		
		SDL_DestroyTexture(nameTex);
		
		delete pauseButton;
	}
	
	///ustawia pozycję okna (lewy górny róg)
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
		if(pauseButton->receiveClick(X, Y, me)) 
		{
			paused=!paused;
			return true;
		}
		
		if(me==ME_PRESS)
		{
			if(posX<=X && X<=posX+width && posY<=Y && Y<=posY+Button::size)
			{
				handlePosX=X-posX;
				handlePosY=Y-posY;
				focus=true;
				return true;
			}
			else
			focus=false;
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
		
		for(int i=0;i<outBuses.size();++i)
		{
			if(outBuses[i].bus->receiveClick(X, Y, me)) return true;
		}
		
		return false;
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
	
	///zapisuje wszystkie dane do strumienia pliku
	void saveData(FILE* file);
	
	///wczytuje wszystkie dane z cstringa
	void loadData(char* str);
	
	///rysuje okno
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
		
		for(auto it=controlledValueGifters.begin();it!=controlledValueGifters.end();++it)
		{
			ControllBus* bus=outBuses[it->first].bus;
			ValueGifter* valueGifter=it->second;
			
			if(bus->getPosY()+ControllBus::size/2 <= valueGifter->getPosY() + valueGifter->getHeight()/2)
			SDL_RenderDrawLine(render, bus->getPosX()+ControllBus::size/2, bus->getPosY()+ControllBus::size/2,
								       valueGifter->getPosX()+valueGifter->getWidth()/2,  valueGifter->getPosY()-Slider::slider_bus_height/2);
			else
			SDL_RenderDrawLine(render, bus->getPosX()+ControllBus::size/2, bus->getPosY()+ControllBus::size/2,
								       valueGifter->getPosX()+valueGifter->getWidth()/2,  valueGifter->getPosY()+valueGifter->getHeight());
		}
		
	}
	
};

///rejestruje kontroler o podanej nazwie
void registerController(const char* name);

#endif