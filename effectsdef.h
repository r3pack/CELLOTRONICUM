#ifndef EFFECTSDEF_H
#define EFFECTSDEF_H
#include "effects.h"
#include "graphics.h"
	
	
	struct ParamSlider
	{
		Slider* slider;
		int param;
		SDL_Texture* nameTex=NULL;
		ParamSlider(Slider* s, int p, const char* text): slider(s), param(p) {nameTex=generateText(text);}
		
		void free() {delete slider; SDL_DestroyTexture(nameTex);}
	};
	
	struct ParamBus
	{
		Bus* bus;
		int param;
		SDL_Texture* nameTex=NULL;
		ParamBus(Bus* b, int p, const char* text): bus(b), param(p) {nameTex=generateText(text);}
		
		void free() {delete bus; SDL_DestroyTexture(nameTex);}
	};
	
	enum VisulalisationType{
            VT_INBUS,
            VT_OUTBUS,
            VT_SLIDER
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
        ArgVis(VisulalisationType type)
        {
            visType=type;
        }
        ~ArgVis()
        {
            if(visType==VT_SLIDER)
            delete [] (float*)data;
        }
        
    };
    
	class EffectAutoGUI : public Effect
	{
		static constexpr int slider_width=30;
		static constexpr int slider_period=20;
		static constexpr int slider_height=160;
		static constexpr int slider_top_padding=35;
		static constexpr int slider_bottom_padding=30;
		
		std::vector <ParamSlider> sliders;
		std::vector <ParamBus> buses;
		
		
		int posX, posY;
		
		int width, height;
			
		int handlePosX, handlePosY;
		
		bool focus;
		
		SDL_Texture* nameTex;
		
		public:
		
		virtual ArgVis* getArgumentVisuals()=0;
		
		void initGUI(int X, int Y)
		{
			posX=X;
			posY=Y;
			EffectArgument* args=getAgrs();
			int argsCount=getAgrsCount();
			
			height=slider_top_padding+slider_bottom_padding+slider_height;
			
			int x=width=slider_period+Bus::size+slider_period;
			
			ArgVis* argvis=getArgumentVisuals();
			
			int bus_y=slider_top_padding;
			int bus_y2=slider_top_padding;
			
			for(int i=0;i<argsCount;++i)
			{
				switch(argvis[i].visType)
				{
					case VT_INBUS:
					buses.push_back(ParamBus(new Bus(posX+slider_period, posY+bus_y, BT_INBUS, this, i), i, args[i].getName()));
					break;
					case VT_OUTBUS:
					buses.push_back(ParamBus(new Bus(posX, posY+bus_y2, BT_OUTBUS, this, i), i, args[i].getName()));
					break;
					case VT_SLIDER:
						float min=((float*)argvis[i].data)[0];
						float max=((float*)argvis[i].data)[1];
						printf("%f %f %f\n", min, max, args[i].getFloatValue());
						sliders.push_back(ParamSlider(new Slider(posX+x, posY+slider_top_padding, slider_width, slider_height, min, max, args[i].getFloatValue()), i, args[i].getName()));
						x+=slider_width+slider_period;
						width+=slider_width+slider_period;
					break;
				}
			}
			width+=Bus::size+slider_period;
			
			nameTex=generateText(getName());
		}
		
		void setPos(int X, int Y)
		{
			for(int i=0;i<sliders.size();++i)
			{
				sliders[i].slider->move(X-posX, Y-posY);
			}
			for(int i=0;i<buses.size();++i)
			{
				buses[i].bus->move(X-posX, Y-posY);
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
			
			for(int i=0;i<sliders.size();++i)
			{
				sliders[i].slider->draw();
				int w, h;
				SDL_QueryTexture(sliders[i].nameTex, NULL, NULL, &w, &h);
			
				nameRect.y=sliders[i].slider->getPosY()+slider_height;
				nameRect.x=sliders[i].slider->getPosX()+slider_width/2-w/2;
				nameRect.w=w;
				nameRect.h=h;		
				
				SDL_RenderCopy(render, sliders[i].nameTex, NULL, &nameRect);
			}
			
			for(int i=0;i<buses.size();++i)
			{
				buses[i].bus->draw();
			}
		}
		
		void receiveClick(int X, int Y, bool begin)
		{
			for(int i=0;i<sliders.size();++i)
			{
				if(sliders[i].slider->receiveClick(X, Y, begin)) setAndSendArgument(sliders[i].param, sliders[i].slider->getValue());
			}
			
			int lastClicked=Bus::lastClicked;
			for(int i=0;i<buses.size();++i)
			{
				if(buses[i].bus->receiveClick(X, Y, begin))
				{
					printf("lastid %d id %d\n", lastClicked, buses[i].bus->getId());
					if(lastClicked!=-1)
					{
						auto it1=busList.find(lastClicked), it2=busList.find(buses[i].bus->getId());
						if(it1==busList.end() || it2==busList.end())
						{
							fprintf(stderr, "Error: buses not found\n");
							Bus::lastClicked=-1;
							break;
						}
						
						Bus *bus1=it1->second, *bus2=it2->second;
						
						if(bus1->getType()==BT_OUTBUS) std::swap(bus1, bus2);
						
						if(bus1->getType()!=BT_INBUS || bus2->getType()!=BT_OUTBUS)
						{
							fprintf(stderr, "Error: bad buses type\n");
							Bus::lastClicked=-1;
							break;
						}
						
						
						if(bus1->getEffect() == bus2->getEffect())
						{
							fprintf(stderr, "Error: buses come from same effect\n");
							Bus::lastClicked=-1;
							break;
						}
						printf("no erro %d %d\n", bus1->getEffect(), bus2->getEffect());
						
						
						Bus::lastClicked=-1;
					}
					break;
				}
			}
		}
		
		void receiveSecondClick(int X, int Y, bool begin)
		{
			if(begin)
			{
				if(posX<=X && X<=posX+width && posY<=Y && Y<=posY+height)
				{
					handlePosX=X-posX;
					handlePosY=Y-posY;
					focus=true;
				}
				else
				focus=false;
			}
			else
			if(focus)
			setPos(X-handlePosX, Y-handlePosY);
		}
		
		~EffectAutoGUI()
		{
			for(int i=0;i<sliders.size();++i)
			{
				sliders[i].free();
			}
			SDL_DestroyTexture(nameTex);
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
			EffectArgument* getAgrs() {return args;}
			const int getAgrsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			Distecho(int X, int Y, int inbus=8, int outbus=0): 
			args({EffectArgument("inbus", inbus), EffectArgument("outbus", outbus), EffectArgument("decay", 2.0f), EffectArgument("amp", 1.0f), EffectArgument("delay", 5.0f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f), ArgVis(VT_SLIDER, 0.0f, 15.0f)})
			{sendInstance(); initGUI(X, Y);}
	};
	
	
	class Playbuf : public Effect
	{
		private:
			static const int argsCount=2;
			EffectArgument args[argsCount];
		public:
			static constexpr const char* name="eff_playbuf";
			const char* getName() {return name;}
			EffectArgument* getAgrs() {return args;}
			const int getAgrsCount() {return argsCount;}
			
			Playbuf(int bufnum, int outbus=0): args({EffectArgument("bufnum", bufnum), EffectArgument("outbus", outbus)}){sendInstance();}
			void draw() {}
			
			void receiveClick(int X, int Y) {}
	};
	
	void registerEffects();
	
#endif
