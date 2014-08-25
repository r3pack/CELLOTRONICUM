#include "effectsdef.h"



#define REGISTER_EFFECT(a, b) registerEffect(a::name, a::fullName, b);
#define REGISTER_EFFECT_EX(a, b, c) registerEffect(a::name, a::fullName, b, c);





void registerEffects()
{
	REGISTER_EFFECT(DistEcho, "Echo");
	REGISTER_EFFECT(ShiftEcho, "Echo");
	REGISTER_EFFECT(Gramophone, "Echo");
	REGISTER_EFFECT(FreqShift, "Echo");
	REGISTER_EFFECT(PitchShift, "Echo");
	REGISTER_EFFECT(RandomPitchShift, "Echo");
	
	REGISTER_EFFECT(OctaveUp, "SoundSources");
	REGISTER_EFFECT(OctaveDown, "SoundSources");
	REGISTER_EFFECT(FormantFilter, "SoundSources");
	
	REGISTER_EFFECT(Brassage, "Brassage");
	REGISTER_EFFECT(BrassageOSC, "Brassage");
	REGISTER_EFFECT(BrassagePlus, "Brassage");
	REGISTER_EFFECT(RMChorus, "Brassage");
	REGISTER_EFFECT(RMChorus2, "Brassage");
	REGISTER_EFFECT(RMDelay, "Brassage");
	REGISTER_EFFECT(RMDelayRec, "Brassage");
	REGISTER_EFFECT(WSDistortion, "Brassage");
	
	REGISTER_EFFECT(SampleDecrease, "BitCrush");
	REGISTER_EFFECT(BitCrush, "BitCrush");
	REGISTER_EFFECT(MobilePhoneLag3, "BitCrush");
	
	REGISTER_EFFECT(BLowPass, "Filters");
	REGISTER_EFFECT(BHiPass, "Filters");
	REGISTER_EFFECT(BBandPass, "Filters");
	
	REGISTER_EFFECT(Amplitude, "Analysis");
	REGISTER_EFFECT(Pitch, "Analysis");
	REGISTER_EFFECT(TartiniPitch, "Analysis");
	REGISTER_EFFECT(Goetzel, "Analysis");
	
	REGISTER_EFFECT(Harmonizer4, "Generators");
	REGISTER_EFFECT(ShepardCycleTone, "Generators");
	REGISTER_EFFECT(AYSimple, "Generators");
	REGISTER_EFFECT(YMSimple, "Generators");
	
	REGISTER_EFFECT(Playbuf, "IO_Effects");
	REGISTER_EFFECT(Mul, "IO_Effects");
	REGISTER_EFFECT(Normalizer, "IO_Effects");
	REGISTER_EFFECT(Limiter, "IO_Effects");
	REGISTER_EFFECT(Output, "IO_Effects");
	REGISTER_EFFECT(Mix, "IO_Effects");
	REGISTER_EFFECT(Mix3, "IO_Effects");
	REGISTER_EFFECT(Input, "IO_Effects");
	REGISTER_EFFECT(InputExtended, "IO_Effects");
	REGISTER_EFFECT(OutputExtended, "IO_Effects");
	
	REGISTER_EFFECT(Clipper4, "Base");
	REGISTER_EFFECT(Clipper8, "Base");
	REGISTER_EFFECT(Clipper32, "Base");
	REGISTER_EFFECT(SoftClipAmp, "Base");
	REGISTER_EFFECT(SoftClipAmp4, "Base");
	REGISTER_EFFECT(SoftClipAmp8, "Base");
	REGISTER_EFFECT(SoftClipper4, "Base");
	REGISTER_EFFECT(SoftClipper8, "Base");
};

#undef REGISTER_EFFECT
#undef REGISTER_EFFECT2

#define EFFECT_BY_NAME(a) if(strcmp(name, a::fullName)==0) return new a(X, Y);

Effect* getEffect(const char* name, int X, int Y)
{
	EFFECT_BY_NAME(DistEcho);
	EFFECT_BY_NAME(ShiftEcho);
	EFFECT_BY_NAME(Brassage);
	EFFECT_BY_NAME(BrassageOSC);
	EFFECT_BY_NAME(BrassagePlus);
	EFFECT_BY_NAME(RMChorus);
	EFFECT_BY_NAME(RMChorus2);
	EFFECT_BY_NAME(RMDelay);
	EFFECT_BY_NAME(RMDelayRec);
	EFFECT_BY_NAME(WSDistortion);
	EFFECT_BY_NAME(MobilePhoneLag3);
	EFFECT_BY_NAME(FreqShift);
	EFFECT_BY_NAME(PitchShift);
	EFFECT_BY_NAME(RandomPitchShift);
	EFFECT_BY_NAME(BLowPass);
	EFFECT_BY_NAME(BHiPass);
	EFFECT_BY_NAME(Amplitude);
	EFFECT_BY_NAME(ShepardCycleTone);
	EFFECT_BY_NAME(AYSimple);
	EFFECT_BY_NAME(YMSimple);
	EFFECT_BY_NAME(Pitch);
	EFFECT_BY_NAME(TartiniPitch);
	EFFECT_BY_NAME(Goetzel);
	EFFECT_BY_NAME(Mix);
	EFFECT_BY_NAME(Mix3);
	EFFECT_BY_NAME(Playbuf);
	EFFECT_BY_NAME(Mul);
	EFFECT_BY_NAME(Normalizer);
	EFFECT_BY_NAME(Limiter);
	EFFECT_BY_NAME(Output);
	EFFECT_BY_NAME(OutputExtended);
	EFFECT_BY_NAME(Input);
	EFFECT_BY_NAME(InputExtended);
	EFFECT_BY_NAME(Harmonizer4);
	EFFECT_BY_NAME(Gramophone);
	EFFECT_BY_NAME(SampleDecrease);
	EFFECT_BY_NAME(BitCrush);
	EFFECT_BY_NAME(Clipper4);
	EFFECT_BY_NAME(Clipper8);
	EFFECT_BY_NAME(Clipper32);
	EFFECT_BY_NAME(SoftClipAmp);
	EFFECT_BY_NAME(SoftClipAmp4);
	EFFECT_BY_NAME(SoftClipAmp8);
	EFFECT_BY_NAME(SoftClipper4);
	EFFECT_BY_NAME(SoftClipper8);
	EFFECT_BY_NAME(OctaveUp);
	EFFECT_BY_NAME(OctaveDown);
	EFFECT_BY_NAME(FormantFilter);
	return NULL;
}

#undef EFFECT_BY_NAME