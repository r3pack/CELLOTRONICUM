#ifndef EFFECTGUI_H
#define EFFECTGUI_H
#include "drawables.h"

	struct ParamDrawable
	{
		Drawable* drawable;
		SDL_Texture* nameTex=NULL;
		ParamDrawable(Drawable* d, const char* text): drawable(d) {nameTex=generateText(text);}
		
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
			VT_FREQ_INBUS,
			VT_FREQ_OUTBUS,
			VT_AMP_INBUS,
			VT_AMP_OUTBUS,
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
		friend class Controller;
	
		Button* pauseButton;
		
		int handlePosX, handlePosY;
		
		bool focus=false;
		
		SDL_Texture* nameTex;
		
		protected:
		
		std::vector <ParamDrawable> drawables;
		
		int posX, posY;
		
		int width, height;
		
		public:
		
		static const int slider_width=30;
		static const int slider_height=160;
		
		virtual int_pair* getVisualPositions()=0;
		
		virtual ArgVis* getArgumentVisuals()=0;
		
		void initGUI(int X, int Y, int W=0, int H=0)
		{
			posX=X;
			posY=Y;
			
			width=W;
			height=H;
			
			pauseButton=new Button(X+2, Y+2, 0);
			
			EffectArgument* args=getArgs();
			int argsCount=getArgsCount();
			
			ArgVis* argvis=getArgumentVisuals();
			
			std::pair<int, int>* argpos=getVisualPositions();
			
			for(int i=0;i<argsCount;++i)
			{
				switch(argvis[i].visType)
				{
					case VT_INBUS:
					drawables.push_back(ParamDrawable(new Bus(posX+argpos[i].first, posY+argpos[i].second, BT_INBUS, this, i), args[i].getName()));
					break;
					case VT_OUTBUS:
					drawables.push_back(ParamDrawable(new Bus(posX+argpos[i].first, posY+argpos[i].second, BT_OUTBUS, this, i), args[i].getName()));
					break;
					case VT_FREQ_INBUS:
					drawables.push_back(ParamDrawable(new Bus(posX+argpos[i].first, posY+argpos[i].second, BT_FREQ_INBUS, this, i), args[i].getName()));
					break;
					case VT_FREQ_OUTBUS:
					drawables.push_back(ParamDrawable(new Bus(posX+argpos[i].first, posY+argpos[i].second, BT_FREQ_OUTBUS, this, i), args[i].getName()));
					break;
					case VT_AMP_INBUS:
					drawables.push_back(ParamDrawable(new Bus(posX+argpos[i].first, posY+argpos[i].second, BT_AMP_INBUS, this, i), args[i].getName()));
					break;
					case VT_AMP_OUTBUS:
					drawables.push_back(ParamDrawable(new Bus(posX+argpos[i].first, posY+argpos[i].second, BT_AMP_OUTBUS, this, i), args[i].getName()));
					break;
					case VT_SLIDER:
					{
						float min=((float*)argvis[i].data)[0];
						float max=((float*)argvis[i].data)[1];
						drawables.push_back(ParamDrawable(new Slider(posX+argpos[i].first, posY+argpos[i].second, slider_width, slider_height, min, max, args[i].getFloatValue(), this, i), args[i].getName()));
					}
					break;
					case VT_TEXT:
						drawables.push_back(ParamDrawable(new Point(posX+argpos[i].first, posY+argpos[i].second), ((std::string*)argvis[i].data)->c_str()));
					break;
				}
			}
			
			nameTex=generateText(getName());
		}
		
		void quitGUI()
		{
			for(int i=0;i<drawables.size();++i)
			drawables[i].free();
			EffectArgument* args=getArgs();
			int argsCount=getArgsCount();
			ArgVis* argvis=getArgumentVisuals();
		
			for(int i=0;i<argsCount;++i)
			{
				if(argvis[i].visType==VT_OUTBUS || argvis[i].visType==VT_INBUS)
				{
					OSCConn::deleteBus(args[i].getIntValue());
				}
			}
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
				if(drawables[i].drawable->receiveClick(X, Y, me)) break;
			}
			
			return true;
		}
		
		bool receiveSecondClick(int X, int Y, MouseEvent me)
		{
			for(int i=0;i<drawables.size();++i)
			{
				if(drawables[i].drawable->receiveSecondClick(X, Y, me)) return true;
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
			SDL_DestroyTexture(nameTex);
			delete pauseButton;
		}
		
	};
	
    
	class EffectAutoGUI : public EffectGUI
	{
		std::pair<int, int>* visualPositions=NULL;
		
		public:
		
		static const int slider_period=20;
		static const int top_padding=35;
		static const int bottom_padding=30;
		static const int bus_period=35;
		
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
			
			int extra_period=slider_period;
			
			for(int i=0;i<argsCount;++i)
			{
				switch(argvis[i].visType)
				{
					case VT_INBUS:
					case VT_FREQ_INBUS:
					case VT_AMP_INBUS:
						visualPositions[i]=int_pair(0+slider_period, bus_y);
						bus_y+=bus_period;
					break;
					case VT_OUTBUS:
					case VT_FREQ_OUTBUS:
					case VT_AMP_OUTBUS:
						visualPositions[i]=int_pair(0, bus_y2);
						bus_y2+=bus_period;
					break;
					case VT_SLIDER:
						slider_y=slider_height;
						visualPositions[i]=int_pair(x, 0+top_padding);
						x+=slider_width+slider_period;
						extra_period=0;
					break;
				}
			}
			
			height=bottom_padding+std::max(std::max(bus_y, bus_y2), top_padding+slider_y);
			
			x+=extra_period;
			
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
	
#endif
