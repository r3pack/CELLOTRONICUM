#ifndef EFFECTSDEF_H
#define EFFECTSDEF_H
#include "effects.h"
#include "graphics.h"
	
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
			
			void draw()
			{
				SDL_Rect rect;
				rect.x = posX; rect.y = posY;
				rect.w = 210;
				rect.h = 300;
				SDL_SetRenderDrawColor(render, 220, 220, 220, 255);
				SDL_RenderFillRect(render, &rect);
				SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
				SDL_RenderDrawRect(render, &rect);
				
				freq.draw();
				amp.draw();
				delay.draw();
			}
			
			void receiveClick(int X, int Y)
			{
				if(freq.receiveClick(X, Y)) setAndSendArgument(BRASSAGE_FREQ, freq.getValue());
				if(amp.receiveClick(X, Y)) setAndSendArgument(BRASSAGE_AMP, amp.getValue());
				if(delay.receiveClick(X, Y)) setAndSendArgument(BRASSAGE_DELAY, delay.getValue());
			}
			
	};
	
	class Distecho : public Effect
	{
		private:
			enum Arguments {
				DISTECHO_INBUS,
				DISTECHO_OUTBUS,
				DISTECHO_DECAY,
				DISTECHO_AMP,
				DISTECHO_DELAY
			};
		
		
			static const int argsCount=5;
			EffectArgument args[argsCount];
			
			Slider decay;
			Slider amp;
			Slider delay;
			
			int posX, posY;
			
		public:
			static constexpr const char* name="eff_distecho";
			const char* getName() {return name;}
			EffectArgument* getAgrs() {return args;}
			const int getAgrsCount() {return argsCount;}
			
			Distecho(int X, int Y, int inbus=8, int outbus=0): 
			decay(X+30, Y+30, 30, 260, 0.0, 10.0, 2.0f), 
			amp(X+90, Y+30, 30, 260, 0.0, 2.0, 1.0f), 
			delay(X+150, Y+30, 30, 260, 0.0, 5.0, 5.0f), 
			posX(X), posY(Y),
			args({EffectArgument("inbus", inbus), EffectArgument("outbus", outbus), EffectArgument("decay", 2.0f), EffectArgument("amp", 1.0f), EffectArgument("delay", 5.0f)})	
			{sendInstance();}
			
			void draw()
			{
				SDL_Rect rect;
				rect.x = posX; rect.y = posY;
				rect.w = 210;
				rect.h = 300;
				SDL_SetRenderDrawColor(render, 220, 220, 220, 255);
				SDL_RenderFillRect(render, &rect);
				SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
				SDL_RenderDrawRect(render, &rect);
				
				decay.draw();
				amp.draw();
				delay.draw();
			}
			
			void receiveClick(int X, int Y)
			{
				if(decay.receiveClick(X, Y)) setAndSendArgument(DISTECHO_DECAY, decay.getValue());
				if(amp.receiveClick(X, Y)) setAndSendArgument(DISTECHO_AMP, amp.getValue());
				if(delay.receiveClick(X, Y)) setAndSendArgument(DISTECHO_DELAY, delay.getValue());
			}
			
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