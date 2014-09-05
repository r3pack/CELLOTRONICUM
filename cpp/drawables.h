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

	///Typ busa - wejściowy lub wyjściowy + rodzaj
	enum BusType{
		BT_INBUS,
		BT_OUTBUS,
		BT_FREQ_INBUS,
		BT_FREQ_OUTBUS,
		BT_AMP_INBUS,
		BT_AMP_OUTBUS,
		BT_FEEDBACK_INBUS,
		BT_FEEDBACK_OUTBUS
	};

	///rodzaj zdarzenia(kliknięcia) myszy
	enum MouseEvent{
		ME_PRESS,
		ME_REPEAT,
		ME_RELEASE
	};

	///rysuje połączenia pomiędzy busami
	void drawConnections();
	
	///ustawia optymalną ilość miejść po przecinku dla wartości i dla danego strumienia 
	void setOptimalPrecision(float value, std::stringstream& ss);

	///Klasa bazowa dla obiektu rysowalnego
	class Drawable{
		public:
		///rysowanie obiektu 
		virtual void draw() = 0;
		///ustawianie pozycji
		virtual void setPos(int X, int Y) = 0;
		///przesuwanie obiektu o zadaną współżędną
		virtual void move(int X, int Y) = 0;
		///zwraca wymiar X pozycji okna
		virtual int getPosX() = 0;
		///zwraca wymiar Y pozycji okna
		virtual int getPosY() = 0;
		//zwraca szerokość okna
		virtual int getWidth() = 0;
		//zwraca wysokość okna
		virtual int getHeight() = 0;
		//odbiera pierwszy klawisz myszy
		virtual bool receiveClick(int X, int Y, MouseEvent me) = 0;
		//odbiera drugi klawisz myszy
		virtual bool receiveSecondClick(int X, int Y, MouseEvent me) {return false;}
		//odbiera trzeci klawisz myszy
		virtual bool receiveKeyboardEvent(SDL_Scancode scancode) {return false;}
		virtual ~Drawable() {}
	};

	///Obiekt rysowalny: punkt materialny - nie robi praktycznie nic
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

	///Obiekt rysowalny: przycisk - pauzuje efekt/kontroler, klasa bazowa dla SwitchButton
	class Button : public Drawable{
		int posX, posY; ///pozycja obiektu
		
		protected:
		
		int symbol; ///identyfikator symbolu który jest wyświetlany na przycisku
		
		public:
		static constexpr int size=15; ///wysokość/szerokość przycisku
		
		Button(int X, int Y, int s): posX(X), posY(Y), symbol(s) {}
		
		///ustawia dany symbol
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
	
	///Obiekt rysowalny: przełącznik - ustawia jedną z dwóch wartości reprezentowanych przez 2 symbole
	class SwitchButton : public Button
	{
		float value1;
		float value2;
		
		int symbol1;
		int symbol2;
		
		bool isTrigger; ///flaga która jeżeli jest ustawina powoduje, że przycisk sam odskakuje
		
		Effect* effect; ///kontrolowany efekt
		int argument;  ///kontrolowany argument w efekcie
		
		bool status=false; ///stan przycisku
	
		public:
		SwitchButton(int X, int Y, float v1, float v2, int s1, int s2, bool iT, Effect* e, int a): 
		Button(X, Y, s1), value1(v1), value2(v2), symbol1(s1), symbol2(s2), isTrigger(iT), effect(e), argument(a) {}
		
		///zwraca status
		bool getStatus() {return status;}
		
		///ustawia status
		void setStatus(bool s);
		
		bool receiveClick(int X, int Y, MouseEvent me);
	};

	///Obiekt rysowalny: bus - łączy wyjścia jednego efektu z wyściamy innego efektu. Możliwe wyjścia to strumień dźwięku, częstotliwości lub amplitudy
	class Bus : public Drawable{
		friend class Effect;
		
		static int lastId; ///ostatnio przyznany identyfikator dla Busów +1
		int id; ///identyfikator busa
		bool clicked=false; ///wewnętrzna informacja czy bus jest kliknięty
		int posX, posY; ///pozycja busa
		BusType type; ///typ busa - wejściowy/wyjściowy i typ danych
		Effect* effect; ///efekt w którym jest ten bus 
		int argument; ///numer argumentu odpowiadającego busowi
		bool used=false; ///czy bus jest aktualnie używany (podpięty do czegoś)
		
		public:
		
		static int lastClicked; ///ostatnio kliknięty bus (jego identyfikator)
		
		static constexpr int size=15; ///szerokość/wysokość busa
		
		///zwraca identyfikator
		int getId() {return id;}
		///zwraca efekt
		Effect* getEffect() {return effect;}
		///zwraca argument
		int getArg() {return argument;}
		///zwraca typ busa
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
		
		///usuwa wszystkie połączenia wychodzące/wchodzące do/z busa 
		void removeConnections();
		
		///usuwa busa z listy połączeń (lista connections)
		void removeBus();
		
		///wykonuje zdarzenie po poprawnym kliknięciu (wykonanie tej metody kolejno na dwóch busach połączy je, o ile typy się zgadzają)
		bool setClicked();
		
		~Bus()
		{
			removeBus();
		}
		
		void draw()
		{
			if(lastClicked!=id) clicked=false;
			
			SDL_Color color;
			if(type==BT_INBUS || type==BT_OUTBUS || type==BT_FEEDBACK_INBUS || type==BT_FEEDBACK_OUTBUS)
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

	///Obiekt rysowalny: bus kontrolujący - łączy wyjście kontrolera z dawcami wartości (ValueGifter) (aktualnie tylko suwak (Slider) i suwak stopniowy (GradualSlider))
	class ControllBus : public Drawable{
		friend class Slider;
		friend class Effect;
		
		static int lastId; ///ostatnio przyznany identyfikator dla Busów kontrolujących +1
		int id; ///identyfikator busa kontrolującego
		bool clicked=false; ///wewnętrzna informacja czy bus jest kliknięty
		int posX, posY; ///pozycja busa
		Controller* controller; ///kontroler do którego należy ten bus
		bool used=false; ///czy bus jest aktualnie używany (podpięty do czegoś)
		
		public:
		static int lastClicked; ///ostatnio kliknięty bus (jego identyfikator)
		
		static constexpr int size=15; ///szerokość/wysokość busa
		
		///zwraca kontroler
		Controller* getController() {return controller;}
		
		ControllBus(int X, int Y, Controller* c)
		{
			controller=c;
			posX=X;
			posY=Y;
			id=lastId;
			++lastId;
			controllBusList.insert(std::pair<int, ControllBus*>(id, this));
		}
		
		///usuwa bus z listy busów (controllBusList)
		void removeBus()
		{
			controllBusList.erase(id);
		}
		
		///wykonuje zdarzenie po poprawnym kliknięciu (wykonanie tej metody na busie kontrolującym i suwaku połączy je)
		bool setClicked();
		
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

	///Klasa pochodna od drawable: dawca wartości (coś w tym stylu) jest to klasa która przekazuje wartości do parametrów i może być kontrolowana przez kontroler.  
	class ValueGifter : public Drawable
	{
		friend class ControllBus;
		friend class Controller;
		friend class Effect;
		
		protected:
	
		static int lastId; 	///ostatnio przyznany numer identyfikacyjny +1
		int id; ///numer identyfikacyjny
		bool clicked=false; ///czy podłączenie do kontrolera jest aktualnie kliknięte
		Effect* effect; ///kontrolowany efekt
		int argument; ///argument do którego przekazywane są wartości
		Controller* controlledBy=NULL; ///wskaźnik na kontroler który kontroluje ten obiekt
		
		public:
		
		static int lastClicked; ///identyfikator ostatnio klikniętego dawcy wartości
		
		ValueGifter()
		{
			id=lastId++;
		}
		
		///usuwa połączenie z kontrolera do tego obiektu
		void removeConnections();
		
		///wykonuje zdarzenie po poprawnym kliknięciu (wykonanie tej metody na busie kontrolującym i suwaku połączy je)
		void setClicked();
		
		///ustawia wartość na podstawie znormalizowanej wartości (od 0 do 1) - ułamek odpowiada zapełnieniu dla suwaka
		virtual void setNormalizedValue(float nv)=0;
	};
	
	///Obiekt rysowalny: pole do wpisywania. Używany jako osobny element do zmiany wartości. Zawiera go także suwak. 
	class EntryBox : public Drawable{
		friend class Slider;

		int width; ///szerokośc pola
		const int height; ///wysokość pola (jest stała)
		int posX, posY; ///pozycja pola
		SDL_Texture* valueTex=NULL; ///tekstura z tekstem w polu
		std::string data; ///string z tekstem w polu
		float value; ///wartość odpowiadająca tekstu
		static int lastId; ///ostatnio przypisany identyfikator +1
		int id; ///identyfikator pola
		static int lastClicked; ///ostatnio kliknięte pole
		
		Effect* effect; ///efekt w którym jest ten bus 
		int argument; ///numer argumentu odpowiadającego busowi
		
		bool clicked=false; ///czy jest kliknięty (tekst jest wprowadzany)
		
		bool textToRemove=true; ///czy tekst ma być usunięty przed wprowadzeniem następnego znaku (po kliknięciu)
		
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
				case SDL_SCANCODE_KP_ENTER:
				case SDL_SCANCODE_RETURN2:
					lastClicked=-1;
					if(checkValue()) sendValue();
				return true;
				default:
				return true;
			}
			return false;
		}
		
		///ustawia wartość argumentu w SC
		void sendValue();
		
		///ustawia wartość 
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
		
		///sprawdza czy wpisana wartośc jest liczbą - jeżeli tak to ustawia ją, wpp. przywraca poprzednią
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
		
		///aktualizuje taksture z tekstem
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
	
	///Obiekt rysowalny: duwak - płynnie ustawia wartości z danego przedziału
	class Slider : public ValueGifter{
		friend class ControllBus;
		friend class Controller;
		friend class Effect;

		float rangeBegin; ///początek przedziału suwaka
		float rangeEnd; ///koniec przedziału suwaka
		int width; ///szerokość suwaka
		int height; ///wysokośc suwaka
		int posX, posY; ///pozycja suwaka (lewy górny róg)
		
		int level; ///odległość między górną krawędzią suwaka, a górną częścią zapełnionej części suwaka
		
		EntryBox entryBox; ///pole do wpisania wartości argumentu
		EntryBox rangeBeginBox; ///pole do wpisania początku przedziału
		EntryBox rangeEndBox; ///pole do wpisania końca przedziału
		
		bool editRange=false; ///czy przedział jest edytowany (czy pola mają być widoczne)
		
		float lastValue; ///ostatnia wartość przed aktualizowaniem pola
		float value; ///aktualna wartość
		
		///ustawia przedział z pól do wpisywania
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
		
		static const int slider_bus_height=8; ///wysokość busa do podpięcia kontrolera (szerokość jest taka sama jak szerokość całego suwaka)
		static const int entry_box_width=30; ///minimalna szerokość pola do wpisywania
		
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
				setValue(entryBox.getValue(), true);
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
	
	///Obiekt rysowalny: suwak stopniowy - przełącza pomiędzy wartościamy z podanej tablicy
	class GradualSlider : public ValueGifter{
		friend class ControllBus;
		friend class Controller;
		friend class Effect;
		
		static const int too_much_graduals_threshold=10; ///od jakiej liczby zmienić sposób wyświetlania suwaka na taki który jest przystosowany do większej ilości stopni
		
		int gradualCount; ///ilość stopni suwaka
		float* graduals; ///tablica z wartościami
		
		int width; ///szerokość suwaka
		int height; ///wysokośc suwaka
		int posX, posY; ///pozycja suwaka (lewy górny róg)
		
		SDL_Texture* valueTex=NULL; ///tekstura z wyrenderowaną wartością
		
		int lastValue; ///ostatnia wartość przed aktualizowaniem pola (numer w tablicy graduals)
		int value; ///aktualna wartość (numer w tablicy graduals)
		
		public:
		
		static const int slider_bus_height=8; ///wysokość busa do podpięcia kontrolera (szerokość jest taka sama jak szerokość całego suwaka)
		
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
			
			if(gradualCount>too_much_graduals_threshold)
			{
				SDL_Color color;
				
				if(controlledBy!=NULL)
				color=COLOR_SLIDER_CONTROLLED;
				else
				color=COLOR_SLIDER1;
				
				if(clicked)
				color=getDarkerColor(color);
				setColor(color);
				
				SDL_RenderFillRect(render, &rect2);
			}
			
			SDL_Rect controllRect;
			controllRect.x = posX;
			controllRect.y = posY-slider_bus_height+1;
			controllRect.w = width;
			controllRect.h = slider_bus_height;
			
			setColor((clicked?getDarkerColor(COLOR_CONTROLL_BUS):COLOR_CONTROLL_BUS));
			SDL_RenderFillRect(render, &controllRect);
			
			setColor(COLOR_SLIDER_BORDER);
			
			if(gradualCount<=too_much_graduals_threshold)
			{
				for(int i=0;i<gradualCount;++i)
				{
					int lineHeight=int((float(i)/float(gradualCount))*float(height));
					if(gradualCount-i-1==value)
					{
						SDL_Rect rect;
						rect.x = posX;
						rect.y = posY+lineHeight;
						rect.w = width;
						rect.h = int((float(i+1)/float(gradualCount))*float(height))-lineHeight;
						SDL_Color color;
			
						if(controlledBy!=NULL)
						color=COLOR_SLIDER_CONTROLLED;
						else
						color=COLOR_SLIDER1;
						
						if(clicked)
						color=getDarkerColor(color);
						setColor(color);
						SDL_RenderFillRect(render, &rect);
						setColor(COLOR_SLIDER_BORDER);
					}

					SDL_RenderDrawLine(render, posX,       posY+lineHeight,
											   posX+width-1, posY+lineHeight);
				}
			}
			
			setColor(COLOR_SLIDER_BORDER);
			SDL_RenderDrawRect(render, &controllRect);
			
			setColor(COLOR_SLIDER_BORDER);
			SDL_RenderDrawRect(render, &rect1);
			
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