#ifndef EFFECTSDEF_H
#define EFFECTSDEF_H
#include "effects.h"
	
	class Brassage : public Effect
	{
		private:
			static const int argsCount=2;
			EffectArgument args[argsCount]={EffectArgument("freq", 0), EffectArgument("arg2", 234)};
		public:
			static constexpr const char* name="eff_brassage";
			const char* getName() {return name;}
			EffectArgument* getAgrs() {return args;}
			const int getAgrsCount() {return argsCount;}
			
			Brassage(){}
	};
	
	
	class Playbuf : public Effect
	{
		private:
			static const int argsCount=1;
			EffectArgument args[argsCount];
		public:
			static constexpr const char* name="eff_playbuf";
			const char* getName() {return name;}
			EffectArgument* getAgrs() {return args;}
			const int getAgrsCount() {return argsCount;}
			
			Playbuf(int bufnum): args({EffectArgument("bufnum", bufnum)}){sendInstance();}
	};
	
	void registerEffects();
	
#endif