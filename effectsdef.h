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
	
	class EffectAutoGUI : public Effect
	{
		static constexpr int slider_width=30;
		static constexpr int slider_period=20;
		static constexpr int slider_height=160;
		static constexpr int slider_top_padding=25;
		static constexpr int slider_bottom_padding=30;
		
		std::vector <ParamSlider> sliders;
		
		int posX, posY;
		
		int width, height;
			
		int handlePosX, handlePosY;
		
		bool focus;
		
		SDL_Texture* nameTex;
		
		public:
		
		
	
		void initGUI(int X, int Y)
		{
			posX=X;
			posY=Y;
			EffectArgument* args=getAgrs();
			int argsCount=getAgrsCount();
			
			width=slider_period;
			height=slider_top_padding+slider_bottom_padding+slider_height;
			
			int x=slider_period;
			for(int i=0;i<argsCount;++i)
			{
				if(strncmp(args[i].getName(), "inbus", 5)==0)
				{
					
				}
				else
				if(strncmp(args[i].getName(), "outbus", 6)==0)
				{
					
				}
				else
				{
					sliders.push_back(ParamSlider(new Slider(posX+x, posY+slider_top_padding, slider_width, slider_height, 0.0f, 10.0f, 5.0f), i, args[i].getName()));
					x+=slider_width+slider_period;
					width+=slider_width+slider_period;
				}
			}
			
			
			nameTex=generateText(getName());
		}
		
		void setPos(int X, int Y)
		{
			posX=X; posY=Y;
			int x=slider_period;
			for(int i=0;i<sliders.size();++i)
			{
				sliders[i].slider->setPos(posX+x, posY+slider_top_padding);
				x+=slider_width+slider_period;
			}
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
		}
		
		void receiveClick(int X, int Y, bool begin)
		{
			for(int i=0;i<sliders.size();++i)
			{
				if(sliders[i].slider->receiveClick(X, Y)) setAndSendArgument(sliders[i].param, sliders[i].slider->getValue());
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
	
	
	
	
	class Brassage : public Effect
	{
		private:
			enum Arguments {
				BRASSAGE_INBUS,
				BRASSAGE_OUTBUS,
				BRASSAGE_FREQ,
				BRASSAGE_AMP,
				BRASSAGE_DELAY
			};
		
		
			static const int argsCount=5;
			EffectArgument args[argsCount];
			
			Slider freq;
			Slider amp;
			Slider delay;
			
			int posX, posY;
			
			int width=210, height=300;
			
			int handlePosX, handlePosY;
			
			bool focus=false;
			
		public:
			static constexpr const char* name="eff_brassage";
			const char* getName() {return name;}
			EffectArgument* getAgrs() {return args;}
			const int getAgrsCount() {return argsCount;}
			
			Brassage(int X, int Y, int inbus=8, int outbus=0): 
			freq(X+30, Y+30, 30, 260, 0.0, 100.0, 5.0f), 
			amp(X+90, Y+30, 30, 260, 0.0, 2.0, 0.5f), 
			delay(X+150, Y+30, 30, 260, 0.0, 5.0, 1.5f), 
			posX(X), posY(Y),
			args({EffectArgument("inbus", inbus), EffectArgument("outbus", outbus), EffectArgument("freq", 5.0f), EffectArgument("amp", 0.5f), EffectArgument("delay", 1.5f)})	
			{sendInstance();}
			
			
			void setPos(int X, int Y)
			{
				posX=X; posY=Y;
				freq.setPos(posX+30, posY+30);
				amp.setPos(posX+90, posY+30);
				delay.setPos(posX+150, posY+30);
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
				
				freq.draw();
				amp.draw();
				delay.draw();
			}
			
			void receiveClick(int X, int Y, bool begin)
			{
				if(freq.receiveClick(X, Y)) setAndSendArgument(BRASSAGE_FREQ, freq.getValue());
				if(amp.receiveClick(X, Y)) setAndSendArgument(BRASSAGE_AMP, amp.getValue());
				if(delay.receiveClick(X, Y)) setAndSendArgument(BRASSAGE_DELAY, delay.getValue());
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
			
	};
	
	class Distecho : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=5;
			EffectArgument args[argsCount];
			
		public:
			static constexpr const char* name="eff_distecho";
			const char* getName() {return name;}
			EffectArgument* getAgrs() {return args;}
			const int getAgrsCount() {return argsCount;}
			
			Distecho(int X, int Y, int inbus=8, int outbus=0): 
			args({EffectArgument("inbus", inbus), EffectArgument("outbus", outbus), EffectArgument("decay", 2.0f), EffectArgument("amp", 1.0f), EffectArgument("delay", 5.0f)})	
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