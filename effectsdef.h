#ifndef EFFECTSDEF_H
#define EFFECTSDEF_H
#include "effects.h"
	
	class Brassage : public Effect
	{
		const char* getName() {return "eff_brassage";}
		
		static const int argsCount=2;
		EffectArgument args[argsCount]={EffectArgument("arg1", 23), EffectArgument("arg2", 234)};
		
		EffectArgument* getAgrs() {return args;}
		const int getAgrsCount() {return argsCount;}
		
		public:
		Brassage(){}
	};
	
	
	void registerEffects();
	
#endif