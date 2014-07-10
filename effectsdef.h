#ifndef EFFECTSDEF_H
#define EFFECTSDEF_H
#include "effects.h"
	
	class Brassage : public Effect
	{
		const char* getName() {return "eff_brassage";}
	};
	
	class Brassage2 : public Effect
	{
		const char* getName() {return "eff_brassage2";}
	};
	
	extern Brassage brassage;
	
	extern Brassage2 brassage2;
	
	void registerEffects();
	
#endif