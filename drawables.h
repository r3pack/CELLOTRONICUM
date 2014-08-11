#ifndef DRAWABLES_H
#define DRAWABLES_H
#include "graphics.h"

	class Effect;
	class Bus;
	class ControllBus;
	class Slider;
	class Controller;
	
	extern std::map <int, Bus*> busList;

	extern std::map <int, ControllBus*> controllBusList;

	extern std::map <int, Slider*> sliderList;

	std::set <std::pair <Bus*, Bus*> >* getConnections();

	enum BusType{
		BT_INBUS,
		BT_OUTBUS
	};

	enum MouseEvent{
		ME_PRESS,
		ME_REPEAT,
		ME_RELEASE
	};

	void drawConnections();

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
		virtual bool receiveSecondClick(int X, int Y, MouseEvent me) {return false;}
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
			
			setColor(COLOR_BUTTON_BACKGROUND);
			SDL_RenderFillRect(render, &rect);
			setColor(COLOR_BUTTON_BORDER);
			SDL_RenderDrawRect(render, &rect);
			
			switch(symbol)
			{
				case 0:
				SDL_RenderDrawLine(render, posX+2, posY+2, posX+3, posY+2);
				SDL_RenderDrawLine(render, posX+2, posY+3, posX+5, posY+3);
				SDL_RenderDrawLine(render, posX+2, posY+4, posX+7, posY+4);
				SDL_RenderDrawLine(render, posX+2, posY+5, posX+9, posY+5);
				SDL_RenderDrawLine(render, posX+2, posY+6, posX+11, posY+6);
				SDL_RenderDrawLine(render, posX+2, posY+7, posX+12, posY+7);
				SDL_RenderDrawLine(render, posX+2, posY+8, posX+11, posY+8);
				SDL_RenderDrawLine(render, posX+2, posY+9, posX+9, posY+9);
				SDL_RenderDrawLine(render, posX+2, posY+10, posX+7, posY+10);
				SDL_RenderDrawLine(render, posX+2, posY+11, posX+5, posY+11);
				SDL_RenderDrawLine(render, posX+2, posY+12, posX+3, posY+12);
				break;
				case 1:
				SDL_RenderDrawLine(render, posX+3, posY+3, posX+3, posY+11);
				SDL_RenderDrawLine(render, posX+4, posY+3, posX+4, posY+11);
				SDL_RenderDrawLine(render, posX+5, posY+3, posX+5, posY+11);
				SDL_RenderDrawLine(render, posX+9, posY+3, posX+9, posY+11);
				SDL_RenderDrawLine(render, posX+10, posY+3, posX+10, posY+11);
				SDL_RenderDrawLine(render, posX+11, posY+3, posX+11, posY+11);
				break;
				default:
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
		friend class Effect;
		
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
			
			SDL_Color color=COLOR_AUDIO_BUS;
			
			SDL_Rect rect;
			rect.x = posX;
			rect.y = posY;
			rect.w = size;
			rect.h = size;
			if(clicked)
				setColor(getDarkerColor(color));
			else
				setColor(color);
			SDL_RenderFillRect(render, &rect);
			setColor(COLOR_BUS_BORDER);
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
		
		bool receiveSecondClick(int X, int Y, MouseEvent me);
		
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
		friend class Slider;
		friend class Effect;
		
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
			
			SDL_Color color=COLOR_CONTROLL_BUS;
			
			SDL_Rect rect;
			rect.x = posX;
			rect.y = posY;
			rect.w = size;
			rect.h = size;
			if(clicked)
				setColor(getDarkerColor(color));
			else
				setColor(color);
			SDL_RenderFillRect(render, &rect);
			setColor(COLOR_BUS_BORDER);
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
		
		bool receiveSecondClick(int X, int Y, MouseEvent me);
		
		static bool connectControllBusWithSlider();
		
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
		friend class ControllBus;
		friend class Controller;
		friend class Effect;
		
		static int lastId;
		int id;
		static int lastClicked;
		bool clicked=false;
		Controller* controlledBy=NULL;

		float rangeBegin;
		float rangeEnd;
		int width;
		int height;
		int posX;
		int posY;
		
		int level;
		
		SDL_Texture* valueTex=NULL;
		
		Effect* effect;
		int argument;
		
		float lastValue;
		float value;
		
		void removeConnections();
		
		public:
		
		Slider(int pX, int pY, int w, int h, float rB, float rE, float l, Effect* e, int a):
		rangeBegin(rB), rangeEnd(rE), width(w), height(h), posX(pX), posY(pY), level(int((1.0f-(l-rB)/(rE-rB)) * float(height))), value(l), lastValue(l),
		effect(e), argument(a)
		{
			id=lastId++;
			std::ostringstream buff;
			buff.setf(std::ios::fixed, std:: ios::floatfield);
			if(value>=10.0f || value<=-10.0f)
			buff.precision(1);
			else
			buff.precision(2);
			buff<<getValue();
			
			valueTex=generateText(buff.str().c_str());
			
			sliderList.insert(std::pair<int, Slider*>(id, this));
		}
		
		~Slider();
		
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
				
				float normalizedLevel=1.0f-(float(Y)/float(height));
				setValue(rangeBegin+(rangeEnd-rangeBegin)*normalizedLevel);
				
				return true;
			}
			return false;
		}
		
		bool receiveSecondClick(int X, int Y, MouseEvent me)
		{
			X-=posX; Y-=posY;
			if(X>=0 && X<=width && Y>=0 && Y<=height && me==ME_PRESS) 
			{
				setClicked();
				return true;
			}
			return false;
		}
		
		void setClicked();
		
		float getValue()
		{
			return value;
		}
		
		void setValue(float v);
		
		void setNormalizedValue(float nv)
		{
			setValue((rangeEnd-rangeBegin)*nv+rangeBegin);
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
			if(lastClicked!=id) clicked=false;
		
			SDL_Rect rect1;
			rect1.x = posX;
			rect1.y = posY;
			rect1.w = width;
			rect1.h = height;
			SDL_Rect rect2=rect1;
			rect2.y+=level;
			rect2.h-=level;
			
			
			setColor(COLOR_SLIDER2);
			SDL_RenderFillRect(render, &rect1);
			if(clicked)
			setColor(getDarkerColor(COLOR_SLIDER1));
			else
			{
				if(controlledBy!=NULL)
				setColor(COLOR_CONTROLL_BUS);
				else
				setColor(COLOR_SLIDER1);
			}
			SDL_RenderFillRect(render, &rect2);
			setColor(COLOR_SLIDER_BORDER);
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