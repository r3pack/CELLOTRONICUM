#ifndef EFFECTSDEF_H
#define EFFECTSDEF_H
#include "effects.h"
#include "graphics.h"
	
	
	struct ParamDrawable
	{
		Drawable* drawable;
		int param;
		SDL_Texture* nameTex=NULL;
		ParamDrawable(Drawable* d, int p, const char* text): drawable(d), param(p) {nameTex=generateText(text);}
		
		void draw() 
		{
			drawable->draw();
			int w, h;
			SDL_QueryTexture(nameTex, NULL, NULL, &w, &h);
		
			SDL_Rect nameRect;
			nameRect.x=drawable->getPosX() + drawable->getWidth()/2 - w/2;
			nameRect.y=drawable->getPosY() + drawable->getHeight(); 
			nameRect.w=w;
			nameRect.h=h;		
			
			SDL_RenderCopy(render, nameTex, NULL, &nameRect);
		}
		
		void free() {delete drawable; SDL_DestroyTexture(nameTex);}
	};
	
	enum VisulalisationType{
			VT_NONE,
            VT_INBUS,
            VT_OUTBUS,
            VT_SLIDER,
			VT_TEXT
    };
	
    struct ArgVis
    {
        VisulalisationType visType;
        void* data=NULL;
        
        ArgVis(VisulalisationType type, float min, float max)
        {
            visType=VT_SLIDER;
            data=new float[2];
			((float*)data)[0]=min;
			((float*)data)[1]=max;
        }
		ArgVis(VisulalisationType type, std::string str)
        {
            visType=VT_TEXT;
            data=new std::string(str);
        }
        ArgVis(VisulalisationType type)
        {
            visType=type;
        }
        ~ArgVis()
        {
            if(visType==VT_SLIDER)
            delete [] (float*)data;
			else
			if(visType==VT_TEXT)
			delete (std::string*)data;
        }
        
    };
	
	typedef std::pair<int, int> int_pair;
	
	class EffectGUI : public Effect
	{	
		Button* pauseButton;
		
		int handlePosX, handlePosY;
		
		bool focus=false;
		
		SDL_Texture* nameTex;
		
		protected:
		
		std::vector <ParamDrawable> drawables;
		
		int posX, posY;
		
		int width, height;
		
		public:
		
		static constexpr int slider_width=30;
		static constexpr int slider_height=160;
		
		virtual int_pair* getVisualPositions()=0;
		
		virtual ArgVis* getArgumentVisuals()=0;
		
		void initGUI(int X, int Y, int W=0, int H=0)
		{
			posX=X;
			posY=Y;
			
			width=W;
			height=H;
			
			pauseButton=new Button(X, Y, 0);
			
			EffectArgument* args=getArgs();
			int argsCount=getArgsCount();
			
			ArgVis* argvis=getArgumentVisuals();
			
			std::pair<int, int>* argpos=getVisualPositions();
			
			for(int i=0;i<argsCount;++i)
			{
				switch(argvis[i].visType)
				{
					case VT_INBUS:
					drawables.push_back(ParamDrawable(new Bus(posX+argpos[i].first, posY+argpos[i].second, BT_INBUS, this, i), i, args[i].getName()));
					break;
					case VT_OUTBUS:
					drawables.push_back(ParamDrawable(new Bus(posX+argpos[i].first, posY+argpos[i].second, BT_OUTBUS, this, i), i, args[i].getName()));
					break;
					case VT_SLIDER:
					{
						float min=((float*)argvis[i].data)[0];
						float max=((float*)argvis[i].data)[1];
						drawables.push_back(ParamDrawable(new Slider(posX+argpos[i].first, posY+argpos[i].second, slider_width, slider_height, min, max, args[i].getFloatValue()), i, args[i].getName()));
					}
					break;
					case VT_TEXT:
						drawables.push_back(ParamDrawable(new Point(posX+argpos[i].first, posY+argpos[i].second), i, ((std::string*)argvis[i].data)->c_str()));
					break;
				}
			}
			
			nameTex=generateText(getName());
		}
		
		int updateDrawablePositions()
		{
			EffectArgument* args=getArgs();
			int argsCount=getArgsCount();
			
			std::pair<int, int>* argpos=getVisualPositions();
			
			for(int i=0;i<argsCount;++i)
			{
				drawables[i].drawable->setPos(posX+argpos[i].first, posY+argpos[i].second);
			}
		}
		
		
		void setPos(int X, int Y)
		{
			pauseButton->move(X-posX, Y-posY);
			
			for(int i=0;i<drawables.size();++i)
			{
				drawables[i].drawable->move(X-posX, Y-posY);
			}
			posX=X; posY=Y;
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
			
			pauseButton->setSymbol(int(isPaused()));
			pauseButton->draw();
			
			
			
			for(int i=0;i<drawables.size();++i)
			{
				drawables[i].draw();
			}
			
		}
		
		bool receiveClick(int X, int Y, MouseEvent me)
		{
			if(!(posX<=X && X<=posX+width && posY<=Y && Y<=posY+height)) return false;
			if(pauseButton->receiveClick(X, Y, me)) 
			{
				paused=!paused;
				if(paused)
					pauseInstance();
				else
					unpauseInstance();
			}
			
			ArgVis* argumentVisuals=getArgumentVisuals();
			
			for(int i=0;i<drawables.size();++i)
			{
				if(drawables[i].drawable->receiveClick(X, Y, me))
				{
					if(argumentVisuals[i].visType==VT_SLIDER)
					{
						setAndSendArgument(drawables[i].param, ((Slider*)drawables[i].drawable)->getValue());
					}
				}
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
				deleteInstance();
				
				delete this;
				return true;
			}
			else return false;
		}
		
		virtual void saveData(FILE* file) 
		{
			int argsCount=getArgsCount();
			EffectArgument* args=getArgs();
			ArgVis* argumentVisuals=getArgumentVisuals();
			
			fprintf(file, "%d %d ", posX, posY);
			
			for(int i=0;i<argsCount;++i)
			{
				if(argumentVisuals[i].visType==VT_SLIDER)
				{
					fprintf(file, "%d %f ", i, args[i].getFloatValue());
				}
			}
			
		}
		
		virtual void loadData(char* str) 
		{
			int argsCount=getArgsCount();
			EffectArgument* args=getArgs();
			ArgVis* argumentVisuals=getArgumentVisuals();
			
			std::stringstream ss;
			ss<<str;
			
			int ptr=0, X, Y;
			
			ss>>X>>Y;
			
			setPos(X, Y);
			
			int id;
			float value;
			
			while(ss>>id>>value)
			{					
				args[id].set(value);
				
				((Slider*)drawables[id].drawable)->setValue(value);
			}
		}
		
		virtual ~EffectGUI()
		{
			for(int i=0;i<drawables.size();++i)
			drawables[i].free();
			SDL_DestroyTexture(nameTex);
			delete pauseButton;
		}
		
	};
	
    
	class EffectAutoGUI : public EffectGUI
	{
		std::pair<int, int>* visualPositions=NULL;
		
		public:
		
		static constexpr int slider_period=20;
		static constexpr int top_padding=35;
		static constexpr int bottom_padding=30;
		static constexpr int bus_period=35;
		
		std::pair<int, int>* getVisualPositions()
		{
			return visualPositions;
		}
		
		void initGUI(int X, int Y)
		{
			int width=0, height=0;
		
			posX=X;
			posY=Y;
			
			EffectArgument* args=getArgs();
			int argsCount=getArgsCount();
			
			visualPositions= new std::pair<int, int>[argsCount];
			
			int x=width=slider_period+Bus::size+slider_period;
			
			ArgVis* argvis=getArgumentVisuals();
			
			int bus_y=top_padding;
			int slider_y=0;
			int bus_y2=top_padding;
			
			for(int i=0;i<argsCount;++i)
			{
				switch(argvis[i].visType)
				{
					case VT_INBUS:
						visualPositions[i]=int_pair(0+slider_period, bus_y);
						bus_y+=bus_period;
					break;
					case VT_OUTBUS:
						visualPositions[i]=int_pair(0, bus_y2);
						bus_y2+=bus_period;
					break;
					case VT_SLIDER:
						slider_y=slider_height;
						visualPositions[i]=int_pair(x, 0+top_padding);
						x+=slider_width+slider_period;
					break;
				}
			}
			
			height=bottom_padding+std::max(std::max(bus_y, bus_y2), top_padding+slider_y);
			
			width=x;
			
			for(int i=0;i<argsCount;++i)
			{
				if(argvis[i].visType==VT_OUTBUS)
				{
					visualPositions[i].first=x;
				}
			}
			
			width+=Bus::size+slider_period;
			
			
			EffectGUI::initGUI(X, Y, width, height);
		}
		
		virtual ~EffectAutoGUI()
		{
			delete [] visualPositions;
		}
		
	};
	
	
	class Distecho : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=5;
			EffectArgument args[argsCount];
			
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_distecho";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			Distecho(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("decay", 2.0f), EffectArgument("amp", 1.0f), EffectArgument("delay", 0.15f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
			{sendInstance(); initGUI(X, Y);}
	};
	
	
	class Playbuf : public EffectGUI
	{
		private:
			static const int argsCount=2;
			
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
			int_pair visualPositions[argsCount];
			
			char playbufFileName[MAX_PATH];
			
			void constructor(int X, int Y)
			{
				FILE* file=fopen(playbufFileName, "r");
				
				if(file==NULL) 
				{
					fprintf(stderr, "Error: File '%s' not exists\n", playbufFileName);
					strcpy(playbufFileName, "/file/unknown");
				}
				
				fclose(file);
				
				fprintf(stderr, "Loading buffer from file: %s\n", playbufFileName);
				int bufnum=OSCConn::loadBuffer(playbufFileName);
				
				args[0].set(bufnum);
				*(std::string*)(argsVis[0].data)=OSCConn::getBufferFileById(bufnum);
				
				int lastSlash=0;
				
				for(int i=1;playbufFileName[i]!='\0';++i)
				{
					if((playbufFileName[i]=='/' || playbufFileName[i]=='\\') && playbufFileName[i-1]!='\\')
					{
						lastSlash=i;
					}
				}
				
				(*(std::string*)(argsVis[0].data)).erase(0, lastSlash+1);
				
				sendInstance(true); 
				
				initGUI(X, Y);
				
				int w, h;
				SDL_QueryTexture(drawables[0].nameTex, NULL, NULL, &w, &h);
				
				visualPositions[0].first=EffectAutoGUI::slider_period + w/2;
				visualPositions[1].first=EffectAutoGUI::slider_period + w + EffectAutoGUI::slider_period;
				
				width=visualPositions[1].first + Bus::size + EffectAutoGUI::slider_period;
				height=visualPositions[1].second + Bus::size + EffectAutoGUI::bottom_padding;
				updateDrawablePositions();
			}
			
			
		public:
			static constexpr const char* name="eff_playbuf";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			int_pair* getVisualPositions() {return visualPositions;}
			
			Playbuf(int X, int Y): args({EffectArgument("bufnum", 0), EffectArgument("outbus", OSCConn::getFreeBus())}),
			argsVis({ArgVis(VT_TEXT, std::string("")), ArgVis(VT_OUTBUS)}),
			visualPositions({int_pair(0, EffectAutoGUI::top_padding), int_pair(0, EffectAutoGUI::top_padding)})
			{
				getOpenFile(playbufFileName, MAX_PATH);
				
				constructor(X, Y);
			}
			
			Playbuf(const char* data): args({EffectArgument("bufnum", 0), EffectArgument("outbus", OSCConn::getFreeBus())}),
			argsVis({ArgVis(VT_TEXT, std::string("")), ArgVis(VT_OUTBUS)}),
			visualPositions({int_pair(0, EffectAutoGUI::top_padding), int_pair(0, EffectAutoGUI::top_padding)})
			{
				std::stringstream ss;
				ss<<data;
				int X, Y;
				ss>>X>>Y;
				
				ss.ignore(1, ' ');
				ss.getline(playbufFileName, MAX_PATH);
				
				constructor(X, Y);
			}
			
			
			void saveData(FILE* file) 
			{
				fprintf(file, "%d %d %s ", posX, posY, playbufFileName);
			}
	};
	
	class Input : public EffectAutoGUI
	{
		private:
			static const int argsCount=1;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
		public:
			static constexpr const char* name="eff_input";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			Input(int X, int Y): args({EffectArgument("outbus", OSCConn::getFreeBus())}),
			argsVis({ArgVis(VT_OUTBUS)})
			{sendInstance(); initGUI(X, Y);}
	};
	
	class Output : public EffectAutoGUI
	{
		private:
			static const int argsCount=2;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
		public:
			static constexpr const char* name="eff_output";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			Output(int X, int Y): args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus())}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS)})
			{sendInstance(); initGUI(X, Y);}
	};
	
	void registerEffects();
	
	Effect* getEffect(const char* name, int X=0, int Y=0);
	
#endif
