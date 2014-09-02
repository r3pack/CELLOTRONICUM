#ifndef DRAWABLES_H
#define DRAWABLES_H
#include "graphics.h"

	class Effect;
	class Bus;
	class ControllBus;
	class ValueGifter;
	class Controller;
	
	extern std::map <int, Bus*> busList;

	extern std::map <int, ControllBus*> controllBusList;

	extern std::map <int, ValueGifter*> valueGifterList;

	std::set <std::pair <Bus*, Bus*> >* getConnections();

	enum BusType{
		BT_INBUS,
		BT_OUTBUS,
		BT_FREQ_INBUS,
		BT_FREQ_OUTBUS,
		BT_AMP_INBUS,
		BT_AMP_OUTBUS
	};

	enum MouseEvent{
		ME_PRESS,
		ME_REPEAT,
		ME_RELEASE
	};

	void drawConnections();
	
	void setOptimalPrecision(float value, std::stringstream& ss);

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
		virtual bool receiveKeyboardEvent(SDL_Scancode scancode) {return false;}
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
		
		protected:
		
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
				case 3:
				break;
				default:
				SDL_RenderDrawLine(render, posX, posY, posX+size-1, posY+size-1);
				SDL_RenderDrawLine(render, posX, posY+size-1, posX+size-1, posY);
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
	
	class SwitchButton : public Button
	{
		float value1;
		float value2;
		
		int symbol1;
		int symbol2;
		
		bool isTrigger;
		
		Effect* effect;
		int argument;
		
		bool status=false;
	
		public:
		SwitchButton(int X, int Y, float v1, float v2, int s1, int s2, bool iT, Effect* e, int a): 
		Button(X, Y, s1), value1(v1), value2(v2), symbol1(s1), symbol2(s2), isTrigger(iT), effect(e), argument(a) {}
		
		bool getStatus() {return status;}
		
		void setStatus(bool s);
		
		bool receiveClick(int X, int Y, MouseEvent me);
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
		
		void removeConnections();
		
		void removeBus();
		
		~Bus()
		{
			removeBus();
		}
		
		void draw()
		{
			if(lastClicked!=id) clicked=false;
			
			SDL_Color color;
			if(type==BT_INBUS || type==BT_OUTBUS)
			color=COLOR_AUDIO_BUS;
			else if(type==BT_FREQ_INBUS || type==BT_FREQ_OUTBUS)
			color=COLOR_FREQ_BUS;
			else if(type==BT_AMP_INBUS || type==BT_AMP_OUTBUS)
			color=COLOR_AMP_BUS;
			
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
		
		bool receiveClick(int X, int Y, MouseEvent me);
		
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
		
		static bool connectControllBusWithValueGifter();
		
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

	class ValueGifter : public Drawable
	{
		friend class ControllBus;
		friend class Controller;
		friend class Effect;
		
		protected:
		static int lastId;
		int id;
		
		bool clicked=false;
		
		Effect* effect;
		int argument;
		
		Controller* controlledBy=NULL;
		
		public:
		
		static int lastClicked;
		
		ValueGifter()
		{
			id=lastId++;
		}
		
		void removeConnections();
		
		void setClicked();
		
		virtual void setNormalizedValue(float nv)=0;
		
	};
	
	class EntryBox : public Drawable{
		friend class Slider;
		int width;
		const int height;
		int posX;
		int posY;
		
		SDL_Texture* valueTex=NULL;
		
		std::string data;
		
		float value;
		
		static int lastId;
		int id;
		static int lastClicked;
		
		Effect* effect;
		int argument;
		
		bool clicked=false;
		
		bool textToRemove=true;
		
		public:
		
		EntryBox(int pX, int pY, int w, float v, Effect* e, int a):
		width(w), posX(pX), posY(pY), height(getFontHeight())
		{
			effect=e;
			argument=a;
			value=v;
			std::stringstream ss;
			setOptimalPrecision(value, ss);
			ss<<v;
			data=ss.str();
			id=lastId++;
			valueTex=generateText(data.c_str());
		}
		
		~EntryBox() {SDL_DestroyTexture(valueTex);}
		
		bool receiveClick(int X, int Y, MouseEvent me)
		{
			if(me!=ME_PRESS && me!=ME_REPEAT) return false;

			X-=posX;
			Y-=posY;
			if(X>=0 && X<=getWidth() && Y>=0 && Y<=height)
			{
				if(me==ME_PRESS) {clicked=true; textToRemove=true;}
				else
				if(me==ME_REPEAT && clicked) {clicked=true; textToRemove=true; return true;}
				else
				if(me==ME_REPEAT) return false;
				if(lastClicked==id)
				{
					lastClicked=-1;
					if(checkValue()) sendValue();
				}
				else
				lastClicked=id;
				return true;
			}
			clicked=false;
			return false;
		}
		
		bool receiveSecondClick(int X, int Y, MouseEvent me)
		{
			if(me!=ME_PRESS) return false;
			
			X-=posX; 
			Y-=posY;
			if(X>=0 && X<=getWidth() && Y>=0 && Y<=height)
			{
				lastClicked=-1;
				std::stringstream ss;
				setOptimalPrecision(value, ss);
				ss<<value;
				data=ss.str();
				updateValue();
				return true;
			}
			return false;
		}
		
		bool receiveKeyboardEvent(SDL_Scancode scancode)
		{
			if(id!=lastClicked) {textToRemove=false; return false;}
			
			if(scancode==SDL_SCANCODE_BACKSPACE)
			{
				textToRemove=false;
			}
			else
			if(textToRemove) 
			{
				data.clear();
				textToRemove=false;
				updateValue();
			}
			
			switch(scancode)
			{
				case SDL_SCANCODE_0:
				case SDL_SCANCODE_KP_0:
					data.push_back('0');
					updateValue();	
				return true;
				case SDL_SCANCODE_1:
				case SDL_SCANCODE_KP_1:
					data.push_back('1');
					updateValue();
				return true;
				case SDL_SCANCODE_2:
				case SDL_SCANCODE_KP_2:
					data.push_back('2');
					updateValue();
				return true;
				case SDL_SCANCODE_3:
				case SDL_SCANCODE_KP_3:
					data.push_back('3');
					updateValue();
				return true;
				case SDL_SCANCODE_4:
				case SDL_SCANCODE_KP_4:
					data.push_back('4');
					updateValue();
				return true;
				case SDL_SCANCODE_5:
				case SDL_SCANCODE_KP_5:
					data.push_back('5');
					updateValue();
				return true;
				case SDL_SCANCODE_6:
				case SDL_SCANCODE_KP_6:
					data.push_back('6');
					updateValue();
				return true;
				case SDL_SCANCODE_7:
				case SDL_SCANCODE_KP_7:
					data.push_back('7');
					updateValue();
				return true;
				case SDL_SCANCODE_8:
				case SDL_SCANCODE_KP_8:
					data.push_back('8');
					updateValue();
				return true;
				case SDL_SCANCODE_9:
				case SDL_SCANCODE_KP_9:
					data.push_back('9');
					updateValue();
				return true;
				case SDL_SCANCODE_PERIOD:
				case SDL_SCANCODE_COMMA:
				case SDL_SCANCODE_KP_COMMA:
				case SDL_SCANCODE_KP_PERIOD:
					data.push_back('.');
					updateValue();
				return true;
				case SDL_SCANCODE_MINUS:
				case SDL_SCANCODE_KP_MINUS:
				case SDL_SCANCODE_KP_PLUSMINUS:
					data.push_back('-');
					updateValue();
				return true;
				case SDL_SCANCODE_BACKSPACE:
					if(data.size()>0)
					{
						data.pop_back();
						updateValue();
					}
				return true;
				case SDL_SCANCODE_DELETE:
					data="";
					updateValue();
				return true;
				case SDL_SCANCODE_RETURN:
				case SDL_SCANCODE_RETURN2:
					lastClicked=-1;
					if(checkValue()) sendValue();
				return true;
				default:
				return true;
			}
			return false;
		}
		
		void sendValue();
		
		void setValue(float v)
		{
			value=v;
			std::stringstream ss;
			setOptimalPrecision(value, ss);
			ss<<value;
			data=ss.str();
			updateValue();
		}
		
		float getValue()
		{
			return value;
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
		
		bool checkValue()
		{
			int periodCount=0;
			
			for(int i=(data[0]=='-'?1:0);data[i]!='\0';++i)
			{
				if(data[i]=='.') ++periodCount;
				else
				if(data[i]=='-') periodCount+=2;
			}
			
			if(periodCount>=2)
			{
				std::stringstream ss;
				ss.setf(std::ios::fixed);
				ss.precision(2);
				ss<<value;
				data=ss.str();
				updateValue();
			}
			else
			{
				value=atof(data.c_str());
			}
		}
		
		void updateValue()
		{
			SDL_DestroyTexture(valueTex);
			valueTex=generateText(data.c_str());
		}
		
		void draw()
		{		
			SDL_Rect rect;
			rect.x = posX;
			rect.y = posY;
			rect.w = getWidth();
			rect.h = height;
			
			setColor((id==lastClicked)?COLOR_ENTRYBOX_BACKGROUND_CLICKED:COLOR_ENTRYBOX_BACKGROUND);
			SDL_RenderFillRect(render, &rect);
			setColor((id==lastClicked)?COLOR_ENTRYBOX_BORDER_CLICKED:COLOR_ENTRYBOX_BORDER);
			SDL_RenderDrawRect(render, &rect);
			
			if(id==lastClicked)
			{
				SDL_Rect rect2=rect;
				rect2.x-=1;
				rect2.y-=1;
				rect2.w+=2;
				rect2.h+=2;
				
				SDL_RenderDrawRect(render, &rect2);
			}
			
			int w, h;
			SDL_QueryTexture(valueTex, NULL, NULL, &w, &h);
			
			SDL_Rect valueRect;
			valueRect.y=posY;
			valueRect.x=posX+getWidth()-w-2;
			valueRect.w=w;
			valueRect.h=h;
			
			SDL_RenderCopy(render, valueTex, NULL, &valueRect);
		}
		
		int getWidth() {
			int w;
			SDL_QueryTexture(valueTex, NULL, NULL, &w, NULL);
			w+=4;
			if(data=="") w=0;
			if(w>width) return w; else return width;
		}
		int getHeight() {return height;}
		
	};
	
	class Slider : public ValueGifter{
		friend class ControllBus;
		friend class Controller;
		friend class Effect;

		float rangeBegin;
		float rangeEnd;
		int width;
		int height;
		int posX;
		int posY;
		
		int level;
		
		EntryBox entryBox;
		
		EntryBox rangeBeginBox;
		EntryBox rangeEndBox;
		
		bool editRange=false;
		
		float lastValue;
		float value;
		
		void setRangeFromEntryBoxes()
		{
			rangeBegin=rangeBeginBox.getValue();
			rangeEnd=rangeEndBox.getValue();
			
			rangeBeginBox.setValue(rangeBegin);
			rangeEndBox.setValue(rangeEnd);
			
			rangeBeginBox.setPos(posX+width/2-rangeBeginBox.getWidth()/2, posY+height/2);
			rangeEndBox.setPos(posX+width/2-rangeEndBox.getWidth()/2, posY+height/2-3-rangeBeginBox.getHeight()+1);
			
			value=std::min(value, std::max(rangeBegin, rangeEnd));
			value=std::max(value, std::min(rangeBegin, rangeEnd));
			
			setValue(value, false, true);
		}
		
		public:
		
		static const int slider_bus_height=8;
		static const int entry_box_width=30;
		
		Slider(int pX, int pY, int w, int h, float rB, float rE, float l, Effect* e, int a):
		rangeBegin(rB), rangeEnd(rE), width(w), height(h), posX(pX), posY(pY), level(int((1.0f-(l-rB)/(rE-rB)) * float(height))), value(l), lastValue(l),
		entryBox(0, 0, entry_box_width, l, e, a), rangeBeginBox(0, 0, entry_box_width, rB, NULL, 0), rangeEndBox(0, 0, entry_box_width, rE, NULL, 0)
		{
			effect=e; 
			argument=a;
			
			entryBox.setPos(posX+width/2-entryBox.getWidth()/2, posY+height);
			
			valueGifterList.insert(std::pair<int, ValueGifter*>(id, this));
		}
		
		~Slider();
		
		bool receiveClick(int X, int Y, MouseEvent me)
		{
			if(entryBox.receiveClick(X, Y, me)) return true;
			if(editRange)
			{
				bool out=false;
				if(rangeBeginBox.receiveClick(X, Y, me)) out=true;
				else
				if(rangeEndBox.receiveClick(X, Y, me)) out=true;
				
				if(out)
				{
					setRangeFromEntryBoxes();
					return true;
				}
			}
			if(me!=ME_PRESS && me!=ME_REPEAT) return false;
			X-=posX;
			Y-=posY;
			if(X>=0 && X<=width && Y>=-15 && Y<=height+15)
			{
				editRange=false;
				if(Y<0 && Y>=-slider_bus_height && me==ME_PRESS) 
				{
					setClicked();
					return true;
				}
		
				if(Y<0) Y=0;
				else
				if(Y>height) Y=height;
				
				float normalizedLevel=1.0f-(float(Y)/float(height));
				setValue(rangeBegin+(rangeEnd-rangeBegin)*normalizedLevel);
				
				entryBox.setValue(getValue());
				entryBox.setPos(posX+width/2-entryBox.getWidth()/2, posY+height);
				
				return true;
			}
			return false;
		}
		
		bool receiveSecondClick(int X, int Y, MouseEvent me)
		{
			if(entryBox.receiveSecondClick(X, Y, me)) return true;
			X-=posX; Y-=posY;
			if(X>=0 && X<=width && Y<0 && Y>=-slider_bus_height && me==ME_PRESS) 
			{
				if(controlledBy!=NULL)
				{
					removeConnections();
				}
			
				return true;
			}
			else if(X>=0 && X<=width && Y>=0 && Y<=height && me==ME_PRESS) 
			{
				editRange=!editRange;
				if(editRange)
				{
					rangeBeginBox.setValue(rangeBegin);
					rangeEndBox.setValue(rangeEnd);
					
					rangeBeginBox.setPos(posX+width/2-rangeBeginBox.getWidth()/2, posY+height/2);
					rangeEndBox.setPos(posX+width/2-rangeEndBox.getWidth()/2, posY+height/2-3-rangeBeginBox.getHeight()+1);
				}
				if(!editRange)
				{
					EntryBox::lastClicked=-1;
				}
				return true;
			}
			return false;
		}
		
		bool receiveKeyboardEvent(SDL_Scancode scancode)
		{
			if(entryBox.receiveKeyboardEvent(scancode))
			{
				setValue(entryBox.getValue(), false);
				entryBox.setPos(posX+width/2-entryBox.getWidth()/2, posY+height);
				return true;
			}
			if(editRange)
			{
				bool out=false;
				if(rangeBeginBox.receiveKeyboardEvent(scancode))
				{
					rangeBeginBox.setPos(posX+width/2-rangeBeginBox.getWidth()/2, posY+height/2);
					out=true;
				}
				else if(rangeEndBox.receiveKeyboardEvent(scancode))
				{
					rangeEndBox.setPos(posX+width/2-rangeEndBox.getWidth()/2, posY+height/2-3-rangeBeginBox.getHeight()+1);
					out=true;
				}
				
				if(out && scancode==SDL_SCANCODE_RETURN)
				{
					setRangeFromEntryBoxes();
				}
				
				return out;
			}
			return false;
		}
		
		float getValue()
		{
			return value;
		}
		
		void setValue(float v, bool skipEntryBox=false, bool forceSet=false);
		
		void setNormalizedValue(float nv)
		{
			setValue((rangeEnd-rangeBegin)*nv+rangeBegin);
		}
		
		void setPos(int X, int Y)
		{
			posX=X;
			posY=Y;
			entryBox.setPos(X+width/2-entryBox.getWidth()/2, Y+height);
			rangeBeginBox.setPos(posX+width/2-rangeBeginBox.getWidth()/2, posY+height/2);
			rangeEndBox.setPos(posX+width/2-rangeEndBox.getWidth()/2, posY+height/2-3-rangeBeginBox.getHeight()+1);
		}
		
		void move(int X, int Y)
		{
			posX+=X;
			posY+=Y;
			entryBox.move(X, Y);
			rangeBeginBox.move(X, Y);
			rangeEndBox.move(X, Y);
		}
		
		int getPosX(){return posX;}
		int getPosY(){return posY;}
		
		float getRangeBegin() {return rangeBegin;}
		float getRangeEnd() {return rangeEnd;}
		
		void setRangeBegin(float rB) {rangeBegin=rB;}
		void setRangeEnd(float rE) {rangeEnd=rE;}
		
		void draw()
		{
			if(lastClicked!=id) clicked=false;
			
			SDL_Rect rect1;
			rect1.x = posX;
			rect1.y = posY;
			rect1.w = width;
			rect1.h = height;
			SDL_Rect rect2=rect1;
			
			level=(level>=0)?level:0;
			level=(level<=height)?level:height;
			
			rect2.y+=level;
			rect2.h-=level;
			
			
			setColor(COLOR_SLIDER2);
			SDL_RenderFillRect(render, &rect1);
			
			SDL_Color color;
			
			if(controlledBy!=NULL)
			color=COLOR_SLIDER_CONTROLLED;
			else
			color=COLOR_SLIDER1;
			
			if(clicked)
			color=getDarkerColor(color);
			
			setColor(color);
			
			SDL_RenderFillRect(render, &rect2);
			setColor(COLOR_SLIDER_BORDER);
			SDL_RenderDrawRect(render, &rect1);
			
			SDL_Rect controllRect;
			controllRect.x = posX;
			controllRect.y = posY-slider_bus_height+1;
			controllRect.w = width;
			controllRect.h = slider_bus_height;
			
			setColor((clicked?getDarkerColor(COLOR_CONTROLL_BUS):COLOR_CONTROLL_BUS));
			SDL_RenderFillRect(render, &controllRect);
			setColor(COLOR_SLIDER_BORDER);
			SDL_RenderDrawRect(render, &controllRect);
			
			entryBox.draw();
			
			if(editRange)
			{
				rangeBeginBox.draw();
				rangeEndBox.draw();
			}
		}
		
		int getWidth() {return width;}
		int getHeight() {return height;}
		
	};
	
	class GradualSlider : public ValueGifter{
		friend class ControllBus;
		friend class Controller;
		friend class Effect;
		
		static const int slider_bus_height=8;

		int gradualCount;
		float* graduals;
		
		int width;
		int height;
		int posX;
		int posY;
		
		SDL_Texture* valueTex=NULL;
		
		int lastValue;
		int value;
		
		public:
		
		GradualSlider(int pX, int pY, int w, int h, int gC, float* g, float l, Effect* e, int a):
		width(w), height(h), posX(pX), posY(pY), gradualCount(gC), graduals(g)
		{
			effect=e; 
			argument=a;
			value=lastValue=0;
			for(int i=0;i<gradualCount;++i)
			{
				if(graduals[i]==l) 
				{
					value=lastValue=i;
				}
			}
			
			id=lastId++;
			std::ostringstream buff;
			
			buff.unsetf(std::ios::scientific);
			
			buff<<graduals[value];
			
			valueTex=generateText(buff.str().c_str());
			
			valueGifterList.insert(std::pair<int, ValueGifter*>(id, this));
		}
		
		~GradualSlider();
		
		bool receiveClick(int X, int Y, MouseEvent me)
		{
			if(me!=ME_PRESS && me!=ME_REPEAT) return false;
			X-=posX;
			Y-=posY;
			if(X>=0 && X<=width && Y>=-15 && Y<=height+15)
			{
				if(Y<0 && Y>=-slider_bus_height && me==ME_PRESS) 
				{
					setClicked();
					return true;
				}
			
				if(Y<0) Y=0;
				else
				if(Y>height) Y=height;
				
				float normalizedLevel=1.0f-(float(Y)/float(height));
				
				setNormalizedValue(normalizedLevel);
				
				return true;
			}
			return false;
		}
		
		bool receiveSecondClick(int X, int Y, MouseEvent me)
		{
			X-=posX; Y-=posY;
			if(X>=0 && X<=width && Y<0 && Y>=-slider_bus_height && me==ME_PRESS) 
			{
				if(controlledBy!=NULL)
				{
					removeConnections();
				}
			
				return true;
			}
			return false;
		}
		
		float getValue()
		{
			return graduals[value];
		}
		
		void setValue(int v);
		
		void setNormalizedValue(float nv)
		{
			setValue(std::max(std::min(int(nv*float(gradualCount)), gradualCount-1), 0));
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
			int level=height-int(float(value)/float(gradualCount-1)*float(height));
		
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
			
			SDL_Color color;
			
			if(controlledBy!=NULL)
			color=COLOR_SLIDER_CONTROLLED;
			else
			color=COLOR_SLIDER1;
			
			if(clicked)
			color=getDarkerColor(color);
			
			setColor(color);
			
			SDL_RenderFillRect(render, &rect2);
			setColor(COLOR_SLIDER_BORDER);
			SDL_RenderDrawRect(render, &rect1);
			
			SDL_Rect controllRect;
			controllRect.x = posX;
			controllRect.y = posY-slider_bus_height+1;
			controllRect.w = width;
			controllRect.h = slider_bus_height;
			
			setColor((clicked?getDarkerColor(COLOR_CONTROLL_BUS):COLOR_CONTROLL_BUS));
			SDL_RenderFillRect(render, &controllRect);
			setColor(COLOR_SLIDER_BORDER);
			SDL_RenderDrawRect(render, &controllRect);
			
			int w, h;
			SDL_QueryTexture(valueTex, NULL, NULL, &w, &h);
			
			SDL_Rect valueRect;
			//valueRect.y=posY+(level-h>=0?level-h:0);
			valueRect.y=posY+height;
			valueRect.x=posX+width/2-w/2;
			valueRect.w=w;
			valueRect.h=h;
			
			SDL_RenderCopy(render, valueTex, NULL, &valueRect);
		}
		
		int getWidth() {return width;}
		int getHeight() {return height;}
	};
	
	
	
#endif