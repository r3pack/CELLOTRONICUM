#include "effectsdef.h"



#define REGISTER_EFFECT(a, b) registerEffect(a::name, a::fullName, b);
#define REGISTER_EFFECT_EX(a, b, c) registerEffect(a::name, a::fullName, b, c);

void registerEffects()
{
	REGISTER_EFFECT(FreqShift, "Spectral");
	REGISTER_EFFECT(FreqShiftFromBus, "Spectral");
	REGISTER_EFFECT(PitchShift, "Spectral");
	REGISTER_EFFECT(RandomPitchShift, "Spectral");
	REGISTER_EFFECT(OctaveUp, "Spectral");
	REGISTER_EFFECT(OctaveDown, "Spectral");
	REGISTER_EFFECT(FormantFilter, "Spectral");
	REGISTER_EFFECT(Hadamard, "Spectral");
	
	REGISTER_EFFECT_EX(DistEcho, "Time-based", "Echo");
	REGISTER_EFFECT_EX(ShiftEcho, "Time-based", "Echo");
	REGISTER_EFFECT_EX(FBamFX, "Time-based", "Echo");
	REGISTER_EFFECT_EX(FBamFXVD, "Time-based", "Echo");
	
	REGISTER_EFFECT_EX(Brassage, "Time-based", "Brassage");
	REGISTER_EFFECT_EX(BrassageOSC, "Time-based", "Brassage");
	REGISTER_EFFECT_EX(BrassagePlus, "Time-based", "Brassage");
	
	REGISTER_EFFECT_EX(RMChorus, "Time-based", "RM-based");
	REGISTER_EFFECT_EX(RMChorus2, "Time-based", "RM-based");
	REGISTER_EFFECT_EX(RMDelay, "Time-based", "RM-based");
	REGISTER_EFFECT_EX(RMDelayRec, "Time-based", "RM-based");
	
	REGISTER_EFFECT(BLowPass, "Filters");
	REGISTER_EFFECT(BLowPass4, "Filters");
	REGISTER_EFFECT(BLowShelf, "Filters");
	REGISTER_EFFECT(BHiPass, "Filters");
	REGISTER_EFFECT(BHiPass4, "Filters");
	REGISTER_EFFECT(BHiShelf, "Filters");
	REGISTER_EFFECT(BBandPass, "Filters");
	REGISTER_EFFECT(BPeakEQ, "Filters");
	REGISTER_EFFECT(BAllPass, "Filters");
	
	REGISTER_EFFECT(Amplitude, "Analysis");
	REGISTER_EFFECT(Pitch, "Analysis");
	REGISTER_EFFECT(TartiniPitch, "Analysis");
	REGISTER_EFFECT(QitchPitch, "Analysis");
	REGISTER_EFFECT(Goetzel, "Analysis");
	
	REGISTER_EFFECT_EX(Harmonizer4, "Generators", "Harmonic");
	REGISTER_EFFECT_EX(Harmonizer5, "Generators", "Harmonic");
	REGISTER_EFFECT_EX(Harmonizer6, "Generators", "Harmonic");
	REGISTER_EFFECT_EX(Harmonizer7, "Generators", "Harmonic");
	REGISTER_EFFECT_EX(Harmonizer8, "Generators", "Harmonic");
	REGISTER_EFFECT_EX(GoetzelSinus, "Generators", "Harmonic");
	
	REGISTER_EFFECT_EX(ShepardCycleTone, "Generators", "Synthesizers");
	REGISTER_EFFECT_EX(AYSimple, "Generators", "Synthesizers");
	REGISTER_EFFECT_EX(YMSimple, "Generators", "Synthesizers");
	
	REGISTER_EFFECT_EX(Playbuf, "Basics", "Buffers");
	
	REGISTER_EFFECT_EX(Gain, "Basics", "Loudness");
	REGISTER_EFFECT_EX(Normalizer, "Basics", "Loudness");
	REGISTER_EFFECT_EX(Limiter, "Basics", "Loudness");
	REGISTER_EFFECT_EX(Compander, "Basics", "Loudness");
	
	REGISTER_EFFECT_EX(Pipe, "Basics", "Mixers");
	REGISTER_EFFECT_EX(Mix, "Basics", "Mixers");
	REGISTER_EFFECT_EX(MixAmp, "Basics", "Mixers");
	REGISTER_EFFECT_EX(Mix3, "Basics", "Mixers");
	REGISTER_EFFECT_EX(Mix3Amp, "Basics", "Mixers");
	REGISTER_EFFECT_EX(Select2, "Basics", "Mixers");
	REGISTER_EFFECT_EX(Select3, "Basics", "Mixers");
	REGISTER_EFFECT_EX(Select4, "Basics", "Mixers");
	REGISTER_EFFECT_EX(Select5, "Basics", "Mixers");
	
	REGISTER_EFFECT_EX(Input, "Basics", "IO");
	REGISTER_EFFECT_EX(Output, "Basics", "IO");
	REGISTER_EFFECT_EX(InputExtended, "Basics", "IO");
	REGISTER_EFFECT_EX(OutputExtended, "Basics", "IO");

	
	REGISTER_EFFECT_EX(Clipper4, "Distortions", "Clippers");
	REGISTER_EFFECT_EX(Clipper8, "Distortions", "Clippers");
	REGISTER_EFFECT_EX(Clipper32, "Distortions", "Clippers");
	REGISTER_EFFECT_EX(SoftClipAmp, "Distortions", "Clippers");
	REGISTER_EFFECT_EX(SoftClipAmp4, "Distortions", "Clippers");
	REGISTER_EFFECT_EX(SoftClipAmp8, "Distortions", "Clippers");
	REGISTER_EFFECT_EX(SoftClipper4, "Distortions", "Clippers");
	REGISTER_EFFECT_EX(SoftClipper8, "Distortions", "Clippers");
	REGISTER_EFFECT_EX(WSDistortion, "Distortions", "Waveshapers");
	REGISTER_EFFECT_EX(SampleDecrease, "Distortions", "Sound Damage");
	REGISTER_EFFECT_EX(BitCrush, "Distortions", "Sound Damage");
	REGISTER_EFFECT_EX(MixWithSquare, "Distortions", "Sound Damage");
	REGISTER_EFFECT_EX(MobilePhoneLag, "Distortions", "Sound Damage");
	REGISTER_EFFECT_EX(MobilePhoneLag2, "Distortions", "Sound Damage");
	REGISTER_EFFECT_EX(MobilePhoneLag3, "Distortions", "Sound Damage");
	REGISTER_EFFECT_EX(Gramophone, "Distortions", "Sound Damage");
	
	
	REGISTER_EFFECT(AFM1, "Natural-Synthetic");
	REGISTER_EFFECT(AFM1Env, "Natural-Synthetic");
	REGISTER_EFFECT(AFM2, "Natural-Synthetic");
	REGISTER_EFFECT(AFM2Env, "Natural-Synthetic");
	
	
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
	EFFECT_BY_NAME(MixWithSquare);
	EFFECT_BY_NAME(MobilePhoneLag);
	EFFECT_BY_NAME(MobilePhoneLag2);
	EFFECT_BY_NAME(MobilePhoneLag3);
	EFFECT_BY_NAME(FreqShift);
	EFFECT_BY_NAME(FreqShiftFromBus);
	EFFECT_BY_NAME(PitchShift);
	EFFECT_BY_NAME(RandomPitchShift);
	EFFECT_BY_NAME(BLowPass);
	EFFECT_BY_NAME(BLowPass4);
	EFFECT_BY_NAME(BLowShelf);
	EFFECT_BY_NAME(BHiPass);
	EFFECT_BY_NAME(BHiPass4);
	EFFECT_BY_NAME(BHiShelf);
	EFFECT_BY_NAME(BAllPass);
	EFFECT_BY_NAME(BPeakEQ);
	EFFECT_BY_NAME(BBandPass);
	EFFECT_BY_NAME(Amplitude);
	EFFECT_BY_NAME(ShepardCycleTone);
	EFFECT_BY_NAME(AYSimple);
	EFFECT_BY_NAME(YMSimple);
	EFFECT_BY_NAME(Pitch);
	EFFECT_BY_NAME(TartiniPitch);
	EFFECT_BY_NAME(QitchPitch);
	EFFECT_BY_NAME(Goetzel);
	EFFECT_BY_NAME(Mix);
	EFFECT_BY_NAME(MixAmp);
	EFFECT_BY_NAME(Mix3);
	EFFECT_BY_NAME(Mix3Amp);
	EFFECT_BY_NAME(Playbuf);
	EFFECT_BY_NAME(Gain);
	EFFECT_BY_NAME(Normalizer);
	EFFECT_BY_NAME(Limiter);
	EFFECT_BY_NAME(Output);
	EFFECT_BY_NAME(OutputExtended);
	EFFECT_BY_NAME(Input);
	EFFECT_BY_NAME(InputExtended);
	EFFECT_BY_NAME(Harmonizer4);
	EFFECT_BY_NAME(Harmonizer5);
	EFFECT_BY_NAME(Harmonizer6);
	EFFECT_BY_NAME(Harmonizer7);
	EFFECT_BY_NAME(Harmonizer8);
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
	EFFECT_BY_NAME(AFM1);
	EFFECT_BY_NAME(AFM1Env);
	EFFECT_BY_NAME(AFM2);
	EFFECT_BY_NAME(AFM2Env);
	EFFECT_BY_NAME(Hadamard);
	EFFECT_BY_NAME(Pipe);
	EFFECT_BY_NAME(GoetzelSinus);
	EFFECT_BY_NAME(Select2);
	EFFECT_BY_NAME(Select3);
	EFFECT_BY_NAME(Select4);
	EFFECT_BY_NAME(Select5);
	EFFECT_BY_NAME(Compander);
	EFFECT_BY_NAME(FBamFX);
	EFFECT_BY_NAME(FBamFXVD);
	return NULL;
}

#undef EFFECT_BY_NAME