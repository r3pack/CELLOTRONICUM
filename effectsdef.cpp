#include "effectsdef.h"
 
const char*const Brassage::name="eff_brassage";
const char*const Playbuf::name="eff_brassage";
 
void registerEffects()
{
	registerEffect(Brassage::name);
	registerEffect(Playbuf::name);
};