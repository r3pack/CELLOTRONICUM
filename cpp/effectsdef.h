#ifndef EFFECTSDEF_H
#define EFFECTSDEF_H
#include "effects.h"
#include "effectgui.h"
#include "graphics.h"



	
#define EFFECT_BODY(ARGS_COUNT, FULL_NAME, SC_NAME) \
	private:\
		static const int argsCount=ARGS_COUNT;\
		EffectArgument args[argsCount];\
		ArgVis argsVis[argsCount];\
	public:\
		static constexpr const char* fullName=FULL_NAME;\
		const char* getFullName() {return fullName;}\
		static constexpr const char* name=SC_NAME;\
		const char* getName() {return name;}\
		EffectArgument* getArgs() {return args;}\
		const int getArgsCount() {return argsCount;}\
		ArgVis* getArgumentVisuals() {return argsVis;}
	
	
	
	class DistEcho : public EffectAutoGUI
	{
		EFFECT_BODY(5, "DistEcho", "eff_distecho");
		
		DistEcho(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("feedback", 0.1f), EffectArgument("amp", 1.0f), EffectArgument("delay", 0.15f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
		~DistEcho() {quitGUI();}
	};
	
	class ShiftEcho : public EffectAutoGUI
	{		
		EFFECT_BODY(6, "ShiftEcho", "eff_shiftecho");
		
		ShiftEcho(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 0.0f), EffectArgument("phase", 0.0f), EffectArgument("feedback", 0.1f), EffectArgument("delay", 0.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, -100.0f, 100.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
		~ShiftEcho() {quitGUI();}
	};
	
	
	class FBamFX : public EffectAutoGUI
	{		
		EFFECT_BODY(4, "FBamFX", "eff_fbamfx");
		
		FBamFX(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("feedback", 0.1f), EffectArgument("amp", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f)})
		{sendInstance(); initGUI(X, Y);}
		~FBamFX() {quitGUI();}
	};
	
	class FBamFXVD : public EffectAutoGUI
	{		
		EFFECT_BODY(5, "FBamFXVD", "eff_fbamfx_variable_delay");
		
		FBamFXVD(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("feedback", 0.1f), EffectArgument("amp", 1.0f), EffectArgument("delay", 0.15f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
		~FBamFXVD() {quitGUI();}
	};
	
	class Brassage : public EffectAutoGUI
	{	
		EFFECT_BODY(5, "Brassage", "eff_brassage");
		
		Brassage(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("amp", 0.5f), EffectArgument("delay", 1.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 15.0f)})
		{sendInstance(); initGUI(X, Y);}
		~Brassage() {quitGUI();}
	};
	
	class BrassageOSC : public EffectAutoGUI
	{		
		EFFECT_BODY(5, "BrassageOSC", "eff_brassage_sin");
		
		BrassageOSC(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("amp", 0.5f), EffectArgument("delay", 1.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 15.0f)})
		{sendInstance(); initGUI(X, Y);}
		~BrassageOSC() {quitGUI();}
	};
	
	class BrassagePlus : public EffectAutoGUI
	{			
		EFFECT_BODY(5, "BrassagePlus", "eff_brassage_plus");
		
		BrassagePlus(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("amp", 0.5f), EffectArgument("delay", 1.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 15.0f)})
		{sendInstance(); initGUI(X, Y);}
		~BrassagePlus() {quitGUI();}
	};
	
	class RMChorus : public EffectAutoGUI
	{	
		EFFECT_BODY(4, "RMChorus", "eff_rmchorus");
		
		RMChorus(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 20.0f), EffectArgument("delay", 0.15f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 100.0f), ArgVis(VT_SLIDER, 0.0f, 2.0f)})
		{sendInstance(); initGUI(X, Y);}
		~RMChorus() {quitGUI();}
	};
	
	class RMChorus2 : public EffectAutoGUI
	{
		EFFECT_BODY(3, "RMChorus2", "eff_rmchorus2");
		
		RMChorus2(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("delay", 0.15f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 2.0f)})
		{sendInstance(); initGUI(X, Y);}
		~RMChorus2() {quitGUI();}
	};
	
	class RMDelay : public EffectAutoGUI
	{
		EFFECT_BODY(3, "RMDelay", "eff_rmdelay");
		
		RMDelay(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("delay", 0.15f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 2.0f)})
		{sendInstance(); initGUI(X, Y);}
		~RMDelay() {quitGUI();}
	};
	
	class RMDelayRec : public EffectAutoGUI
	{
		EFFECT_BODY(3, "RMDelayRec", "eff_rmdelayrec");
		
		RMDelayRec(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("delay", 0.15f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 2.0f)})
		{sendInstance(); initGUI(X, Y, 17, 17);}
		~RMDelayRec() {quitGUI();}
	};
	
	class WSDistortion : public EffectAutoGUI
	{
		EFFECT_BODY(3, "WSDistortion", "eff_wsdistortion");
			
		WSDistortion(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("gain", 2.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 10.0f)})
		{sendInstance(); initGUI(X, Y, 17, 17);}
		~WSDistortion() {quitGUI();}
	};
	
	class MixWithSquare : public EffectAutoGUI
	{
		EFFECT_BODY(4, "MixWithSquare", "eff_mix_with_square");
		
		MixWithSquare(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("width", 0.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f)})
		{sendInstance(); initGUI(X, Y, 20, 20);}
		~MixWithSquare() {quitGUI();}
	};
	
	class MobilePhoneLag : public EffectAutoGUI
	{
		EFFECT_BODY(4, "MobilePhoneLag", "eff_mobile_phone_lag");
		
		MobilePhoneLag(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("width", 0.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f)})
		{sendInstance(); initGUI(X, Y, 20, 20);}
		~MobilePhoneLag() {quitGUI();}
	};
	
	class MobilePhoneLag2 : public EffectAutoGUI
	{
		EFFECT_BODY(4, "MobilePhoneLag2", "eff_mobile_phone_lag2");
		
		MobilePhoneLag2(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("width", 0.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f)})
		{sendInstance(); initGUI(X, Y, 20, 20);}
		~MobilePhoneLag2() {quitGUI();}
	};
	
	class MobilePhoneLag3 : public EffectAutoGUI
	{
		EFFECT_BODY(4, "MobilePhoneLag3", "eff_mobile_phone_lag3");
		
		MobilePhoneLag3(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("width", 0.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f)})
		{sendInstance(); initGUI(X, Y, 20, 20);}
		~MobilePhoneLag3() {quitGUI();}
	};
	
	class FreqShift : public EffectAutoGUI
	{
		EFFECT_BODY(3, "FreqShift", "eff_freqshift");
		
		FreqShift(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, -100.0f, 100.0f)})
		{sendInstance(); initGUI(X, Y);}
		~FreqShift() {quitGUI();}
	};
	
	class FreqShiftFromBus : public EffectAutoGUI
	{
		EFFECT_BODY(3, "FreqShift", "eff_freq_shift");
		
		FreqShiftFromBus(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq_bus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_FREQ_INBUS)})
		{sendInstance(); initGUI(X, Y);}
		~FreqShiftFromBus() {quitGUI();}
	};
	
	class PitchShift : public EffectAutoGUI
	{
		EFFECT_BODY(3, "PitchShift", "eff_pitchshift");
		
		PitchShift(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("semitones", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, -5.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
		~PitchShift() {quitGUI();}
	};
	
	class RandomPitchShift : public EffectAutoGUI
	{
		EFFECT_BODY(2, "RandomPitchShift", "eff_rand_pitchshift");
		
		RandomPitchShift(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS)})
		{sendInstance(); initGUI(X, Y, 30, 30);}
		~RandomPitchShift() {quitGUI();}
	};
	
	class Gain : public EffectAutoGUI
	{
		EFFECT_BODY(3, "Gain", "eff_mul");
		
		Gain(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("mul", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 10.0f)})
		{sendInstance(); initGUI(X, Y);}
		~Gain() {quitGUI();}
	};
	
	class Clipper4 : public EffectAutoGUI
	{
			EFFECT_BODY(4, "Clipper4", "eff_Clipper4");
			
			Clipper4(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("lo", 0.0f), EffectArgument("hi", 1.0f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
			{sendInstance(); initGUI(X, Y);}
			~Clipper4() {quitGUI();}
	};
	
	class Clipper8 : public EffectAutoGUI
	{
		EFFECT_BODY(4, "Clipper8", "eff_Clipper8");
		
		Clipper8(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("lo", 0.0f), EffectArgument("hi", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
		~Clipper8() {quitGUI();}
	};
	
	class Clipper32 : public EffectAutoGUI
	{
		EFFECT_BODY(4, "Clipper32", "eff_Clipper32");
		
		Clipper32(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("lo", 0.0f), EffectArgument("hi", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
		~Clipper32() {quitGUI();}
	};

	class SoftClipAmp : public EffectAutoGUI
	{	
		EFFECT_BODY(3, "SoftClipAmp", "eff_SoftClipAmp");
		
		SoftClipAmp(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("pregain", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f)})
		{sendInstance(); initGUI(X, Y);}
		~SoftClipAmp() {quitGUI();}
	};
	
	class SoftClipAmp4 : public EffectAutoGUI
	{
		EFFECT_BODY(3, "SoftClipAmp4", "eff_SoftClipAmp4");
		
		SoftClipAmp4(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("pregain", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f)})
		{sendInstance(); initGUI(X, Y);}
		~SoftClipAmp4() {quitGUI();}
	};
	
	class SoftClipAmp8 : public EffectAutoGUI
	{
		EFFECT_BODY(3, "SoftClipAmp8", "eff_SoftClipAmp8");
			
		SoftClipAmp8(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("pregain", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f)})
		{sendInstance(); initGUI(X, Y);}
		~SoftClipAmp8() {quitGUI();}
	};
	
	class SoftClipper4 : public EffectAutoGUI
	{
		EFFECT_BODY(2, "SoftClipper4", "eff_SoftClipper4");
		
		SoftClipper4(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS)})
		{sendInstance(); initGUI(X, Y, 20, 20);}
		~SoftClipper4() {quitGUI();}
	};
	
	class SoftClipper8 : public EffectAutoGUI
	{
		EFFECT_BODY(2, "SoftClipper8", "eff_SoftClipper8");
		
		SoftClipper8(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS)})
		{sendInstance(); initGUI(X, Y, 20, 20);}
		~SoftClipper8() {quitGUI();}
	};
	
	class AYSimple : public EffectAutoGUI
	{			
		EFFECT_BODY(4, "AYSimple", "eff_ay_simple");
		
		AYSimple(int X, int Y): 
		args({EffectArgument("freq_bus", OSCConn::getFreeBus()), EffectArgument("amp_bus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("gain", 1.0f)}),
		argsVis({ArgVis(VT_FREQ_INBUS), ArgVis(VT_AMP_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f)})
		{sendInstance(); initGUI(X, Y, 30);}
		~AYSimple() {quitGUI();}
	};
	
	class YMSimple : public EffectAutoGUI
	{
		EFFECT_BODY(4, "YMSimple", "eff_ym_simple");
		
		YMSimple(int X, int Y): 
		args({EffectArgument("freq_bus", OSCConn::getFreeBus()), EffectArgument("amp_bus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("gain", 1.0f)}),
		argsVis({ArgVis(VT_FREQ_INBUS), ArgVis(VT_AMP_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f)})
		{sendInstance(); initGUI(X, Y, 30);}
		~YMSimple() {quitGUI();}
	};
	
	class Limiter : public EffectAutoGUI
	{		
		EFFECT_BODY(4, "Limiter", "eff_limiter");
		
		Limiter(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("level", 1.0f), EffectArgument("dur", 0.01f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.01f, 0.1f)})
		{sendInstance(); initGUI(X, Y);}
		~Limiter() {quitGUI();}
	};
	
	class Normalizer : public EffectAutoGUI
	{
		EFFECT_BODY(4, "Normalizer", "eff_normalizer");
		
		Normalizer(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("level", 1.0f), EffectArgument("dur", 0.01f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.01f, 0.1f)})
		{sendInstance(); initGUI(X, Y);}
		~Normalizer() {quitGUI();}
	};
	
	class BLowPass : public EffectAutoGUI
	{		
		EFFECT_BODY(4, "BLowPass", "eff_BLowPass");
		
		BLowPass(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 100.0f), EffectArgument("rq", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
		~BLowPass() {quitGUI();}
	};
	
	class BLowPass4 : public EffectAutoGUI
	{		
		EFFECT_BODY(4, "BLowPass4", "eff_BLowPass4");
		
		BLowPass4(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 100.0f), EffectArgument("rq", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
		~BLowPass4() {quitGUI();}
	};
	
	class BHiPass : public EffectAutoGUI
	{
		EFFECT_BODY(4, "BHiPass", "eff_BHiPass");
			
		BHiPass(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5000.0f), EffectArgument("rq", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
		~BHiPass() {quitGUI();}
	};
	
	class BHiPass4 : public EffectAutoGUI
	{
		EFFECT_BODY(4, "BHiPass4", "eff_BHiPass4");
			
		BHiPass4(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5000.0f), EffectArgument("rq", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
		~BHiPass4() {quitGUI();}
	};
	
	class BPeakEQ : public EffectAutoGUI
	{
		EFFECT_BODY(5, "BPeakEQ", "eff_BPeakEQ");
			
		BPeakEQ(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5000.0f), EffectArgument("rq", 1.0f), EffectArgument("gain", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 10.0f)})
		{sendInstance(); initGUI(X, Y);}
		~BPeakEQ() {quitGUI();}
	};
	
	class BHiShelf : public EffectAutoGUI
	{
		EFFECT_BODY(5, "BHiShelf", "eff_BHiShelf");
			
		BHiShelf(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5000.0f), EffectArgument("rs", 1.0f), EffectArgument("gain", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 10.0f)})
		{sendInstance(); initGUI(X, Y);}
		~BHiShelf() {quitGUI();}
	};
	
	class BLowShelf : public EffectAutoGUI
	{
		EFFECT_BODY(5, "BLowShelf", "eff_BLowShelf");
			
		BLowShelf(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5000.0f), EffectArgument("rs", 1.0f), EffectArgument("gain", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 10.0f)})
		{sendInstance(); initGUI(X, Y);}
		~BLowShelf() {quitGUI();}
	};
	
	class BAllPass : public EffectAutoGUI
	{
		EFFECT_BODY(4, "BAllPass", "eff_BAllPass");
			
		BAllPass(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5000.0f), EffectArgument("rq", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
		~BAllPass() {quitGUI();}
	};
	
	class BBandPass : public EffectAutoGUI
	{
		EFFECT_BODY(4, "BBandPass", "eff_BBandPass");
		
		BBandPass(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 1000.0f), EffectArgument("bw", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
		~BBandPass() {quitGUI();}
	};
	
	class OctaveUp : public EffectAutoGUI
	{
		EFFECT_BODY(4, "OctaveUp", "eff_octave_up");
		
		OctaveUp(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq_bus", OSCConn::getFreeBus()), EffectArgument("mul", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_FREQ_INBUS), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y, 20);}
		~OctaveUp() {quitGUI();}
	};
	
	class OctaveDown : public EffectAutoGUI
	{		
		EFFECT_BODY(4, "OctaveDown", "eff_octave_down");
		
		OctaveDown(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq_bus", OSCConn::getFreeBus()), EffectArgument("mul", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_FREQ_INBUS), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y, 20);}
		~OctaveDown() {quitGUI();}
	};
	
	class FormantFilter : public EffectAutoGUI
	{		
		EFFECT_BODY(5, "FormantFilter", "eff_octave_down");
		
		FormantFilter(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq_bus", OSCConn::getFreeBus()), EffectArgument("freq_mul", 0.5f), EffectArgument("mul", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_FREQ_INBUS), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y, 20);}
		~FormantFilter() {quitGUI();}
	};
	
	class Amplitude : public EffectAutoGUI
	{
		EFFECT_BODY(4, "Amplitude", "eff_amplitude");
		
		Amplitude(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("attackTime", 0.01f), EffectArgument("releaseTime", 0.01f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_AMP_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
		~Amplitude() {quitGUI();}
	};
	
	class ShepardCycleTone : public EffectAutoGUI
	{
		EFFECT_BODY(4, "ShepardCycleTone", "eff_shepard_cycle_tone");
		
		ShepardCycleTone(int X, int Y): 
		args({EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq_bus", OSCConn::getFreeBus()), EffectArgument("amp_bus", OSCConn::getFreeBus()), EffectArgument("amp", 0.5f)}),
		argsVis({ArgVis(VT_OUTBUS), ArgVis(VT_FREQ_INBUS), ArgVis(VT_AMP_INBUS), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y, 30, 30);}
		~ShepardCycleTone() {quitGUI();}
	};
	
	class Pitch : public EffectAutoGUI
	{
		EFFECT_BODY(2, "Pitch", "eff_pitch");
		
		Pitch(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_FREQ_OUTBUS)})
		{sendInstance(); initGUI(X, Y);}
		~Pitch() {quitGUI();}
	};
	
	class TartiniPitch : public EffectAutoGUI
	{		
		EFFECT_BODY(3, "TartiniPitch", "eff_tartini_pitch");
			
		TartiniPitch(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("cutoff", 0.45f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_FREQ_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y, 17, 17);}
		~TartiniPitch() {quitGUI();}
	};
	
	class QitchPitch : public EffectAutoGUI
	{		
		EFFECT_BODY(5, "QitchPitch", "eff_qitch_pitch");
			
		QitchPitch(int X, int Y): 
		
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("ampThreshold", 0.01f), EffectArgument("minfreq", 0.0f), EffectArgument("maxfreq", 2500.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_FREQ_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 2500.0f), ArgVis(VT_SLIDER, 0.0f, 2500.0f)})
		{sendInstance(); initGUI(X, Y, 17, 17);}
		~QitchPitch() {quitGUI();}
	};
	
	class Goetzel : public EffectAutoGUI
	{
		EFFECT_BODY(5, "Goetzel", "eff_goetzel");
		
		Goetzel(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("freq_outbus", OSCConn::getFreeBus()), EffectArgument("amp_outbus", OSCConn::getFreeBus()), EffectArgument("freq", 440.0f), EffectArgument("overlap", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_FREQ_OUTBUS), ArgVis(VT_AMP_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 8000.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y, EffectAutoGUI::left_padding, 30);}
		~Goetzel() {quitGUI();}
	};
	
	class SampleDecrease : public EffectAutoGUI
	{
		EFFECT_BODY(3, "SampleDecrease", "eff_sample_decrese");
		
		SampleDecrease(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("samplerate", 20000.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 48000.0f)})
		{sendInstance(); initGUI(X, Y, 25, 25);}
		~SampleDecrease() {quitGUI();}
	};
	
	class BitCrush : public EffectAutoGUI
	{
		EFFECT_BODY(3, "BitCrush", "eff_bitcrush");
		
		BitCrush(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("bitSize", 16.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_GRADUALSLIDER, 1, 32)})
		{sendInstance(); initGUI(X, Y);}
		~BitCrush() {quitGUI();}
	};
	
	class Mix : public EffectAutoGUI
	{
		EFFECT_BODY(3, "Mix", "eff_mix");
		
		Mix(int X, int Y): 
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS)})
		{sendInstance(); initGUI(X, Y);}
		~Mix() {quitGUI();}
	};
	
	class MixAmp : public EffectAutoGUI
	{
		EFFECT_BODY(4, "MixAmp", "eff_mix");
		
		MixAmp(int X, int Y): 
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("max_amp1", 0.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
		~MixAmp() {quitGUI();}
	};
	
	class Mix3 : public EffectAutoGUI
	{
		EFFECT_BODY(4, "Mix3", "eff_mix3");
		
		Mix3(int X, int Y): 
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("inbus3", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS)})
		{sendInstance(); initGUI(X, Y);}
		~Mix3() {quitGUI();}
	};
	
	class Mix3Amp : public EffectAutoGUI
	{
		EFFECT_BODY(6, "Mix3Amp", "eff_mix3");
		
		float valueSlider1, valueSlider2;
		
		Mix3Amp(int X, int Y): 
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("inbus3", OSCConn::getFreeBus()), 
		EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("max_amp1", 0.3333f), EffectArgument("max_amp2", 0.3333f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)}),
		valueSlider1(0.3333f), valueSlider2(0.3333f)
		{sendInstance(); initGUI(X, Y, 25);}
		~Mix3Amp() {quitGUI();}
		
		
		void doSomething()
		{
			if(((Slider*)drawables[4].drawable)->getValue()!=valueSlider1)
			{
				valueSlider1=((Slider*)drawables[4].drawable)->getValue();
				valueSlider2=((Slider*)drawables[5].drawable)->getValue();
				if(valueSlider1+valueSlider2>1.0f)
				{
					valueSlider2=1.0f-valueSlider1;
					((Slider*)drawables[5].drawable)->setValue(valueSlider2);
				}
				
			}
			else
			if(((Slider*)drawables[5].drawable)->getValue()!=valueSlider2)
			{
				valueSlider1=((Slider*)drawables[4].drawable)->getValue();
				valueSlider2=((Slider*)drawables[5].drawable)->getValue();
				if(valueSlider1+valueSlider2>1.0f)
				{
					valueSlider1=1.0f-valueSlider2;
					((Slider*)drawables[4].drawable)->setValue(valueSlider1);
				}
			}
		}
	};
	
	class Gramophone : public EffectAutoGUI
	{
		EFFECT_BODY(8, "Gramophone", "eff_gramophone");
		
		Gramophone(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("noise_amp", 0.2f), EffectArgument("rq", 1.0f),
		EffectArgument("freq", 1000.0f), EffectArgument("imp_freq", 5.0f), EffectArgument("blip_freq", 3.0f), EffectArgument("gain", 2.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.1f, 10.0f),
		ArgVis(VT_SLIDER, 1.0f, 15000.0f), ArgVis(VT_SLIDER, 0.0f, 30.0f), ArgVis(VT_SLIDER, 0.0f, 20.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
		~Gramophone() {quitGUI();}
	};
	
	class Harmonizer4 : public EffectAutoGUI
	{
		EFFECT_BODY(20, "Harmonizer4", "eff_harmonizer_4");
		
		Harmonizer4(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), 
		EffectArgument("amp_attack", 0.02f), EffectArgument("amp_release", 0.5f),
		EffectArgument("semitones1", 0.0f), EffectArgument("amp1", 0.0f), EffectArgument("amp_threshold1", 0.02f), EffectArgument("ampmax1", 0.06f),
		EffectArgument("semitones2", 0.0f), EffectArgument("amp2", 0.0f), EffectArgument("amp_threshold2", 0.02f), EffectArgument("ampmax2", 0.06f),
		EffectArgument("semitones3", 0.0f), EffectArgument("amp3", 0.0f), EffectArgument("amp_threshold3", 0.02f), EffectArgument("ampmax3", 0.06f),
		EffectArgument("semitones4", 0.0f), EffectArgument("amp4", 0.0f), EffectArgument("amp_threshold4", 0.02f), EffectArgument("ampmax4", 0.06f)
		}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS),
		ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15)
		})
		{sendInstance(); initGUI(X, Y);}
		~Harmonizer4() {quitGUI();}
	};
	
	class Harmonizer5 : public EffectAutoGUI
	{
		EFFECT_BODY(24, "Harmonizer5", "eff_harmonizer_5");
		
		Harmonizer5(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), 
		EffectArgument("amp_attack", 0.02f), EffectArgument("amp_release", 0.5f),
		EffectArgument("semitones1", 0.0f), EffectArgument("amp1", 0.0f), EffectArgument("amp_threshold1", 0.02f), EffectArgument("ampmax1", 0.06f),
		EffectArgument("semitones2", 0.0f), EffectArgument("amp2", 0.0f), EffectArgument("amp_threshold2", 0.02f), EffectArgument("ampmax2", 0.06f),
		EffectArgument("semitones3", 0.0f), EffectArgument("amp3", 0.0f), EffectArgument("amp_threshold3", 0.02f), EffectArgument("ampmax3", 0.06f),
		EffectArgument("semitones4", 0.0f), EffectArgument("amp4", 0.0f), EffectArgument("amp_threshold4", 0.02f), EffectArgument("ampmax4", 0.06f),
		EffectArgument("semitones5", 0.0f), EffectArgument("amp5", 0.0f), EffectArgument("amp_threshold5", 0.02f), EffectArgument("ampmax5", 0.06f)
		}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS),
		ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15)
		})
		{sendInstance(); initGUI(X, Y);}
		~Harmonizer5() {quitGUI();}
	};
	
	class Harmonizer6 : public EffectAutoGUI
	{
		EFFECT_BODY(28, "Harmonizer6", "eff_harmonizer_6");
		
		Harmonizer6(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), 
		EffectArgument("amp_attack", 0.02f), EffectArgument("amp_release", 0.5f),
		EffectArgument("semitones1", 0.0f), EffectArgument("amp1", 0.0f), EffectArgument("amp_threshold1", 0.02f), EffectArgument("ampmax1", 0.06f),
		EffectArgument("semitones2", 0.0f), EffectArgument("amp2", 0.0f), EffectArgument("amp_threshold2", 0.02f), EffectArgument("ampmax2", 0.06f),
		EffectArgument("semitones3", 0.0f), EffectArgument("amp3", 0.0f), EffectArgument("amp_threshold3", 0.02f), EffectArgument("ampmax3", 0.06f),
		EffectArgument("semitones4", 0.0f), EffectArgument("amp4", 0.0f), EffectArgument("amp_threshold4", 0.02f), EffectArgument("ampmax4", 0.06f),
		EffectArgument("semitones5", 0.0f), EffectArgument("amp5", 0.0f), EffectArgument("amp_threshold5", 0.02f), EffectArgument("ampmax5", 0.06f),
		EffectArgument("semitones6", 0.0f), EffectArgument("amp6", 0.0f), EffectArgument("amp_threshold6", 0.02f), EffectArgument("ampmax6", 0.06f)
		}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS),
		ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15)
		})
		{sendInstance(); initGUI(X, Y);}
		~Harmonizer6() {quitGUI();}
	};
	
	class Harmonizer7 : public EffectAutoGUI
	{
		EFFECT_BODY(32, "Harmonizer7", "eff_harmonizer_7");
		
		Harmonizer7(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), 
		EffectArgument("amp_attack", 0.02f), EffectArgument("amp_release", 0.5f),
		EffectArgument("semitones1", 0.0f), EffectArgument("amp1", 0.0f), EffectArgument("amp_threshold1", 0.02f), EffectArgument("ampmax1", 0.06f),
		EffectArgument("semitones2", 0.0f), EffectArgument("amp2", 0.0f), EffectArgument("amp_threshold2", 0.02f), EffectArgument("ampmax2", 0.06f),
		EffectArgument("semitones3", 0.0f), EffectArgument("amp3", 0.0f), EffectArgument("amp_threshold3", 0.02f), EffectArgument("ampmax3", 0.06f),
		EffectArgument("semitones4", 0.0f), EffectArgument("amp4", 0.0f), EffectArgument("amp_threshold4", 0.02f), EffectArgument("ampmax4", 0.06f),
		EffectArgument("semitones5", 0.0f), EffectArgument("amp5", 0.0f), EffectArgument("amp_threshold5", 0.02f), EffectArgument("ampmax5", 0.06f),
		EffectArgument("semitones6", 0.0f), EffectArgument("amp6", 0.0f), EffectArgument("amp_threshold6", 0.02f), EffectArgument("ampmax6", 0.06f),
		EffectArgument("semitones7", 0.0f), EffectArgument("amp7", 0.0f), EffectArgument("amp_threshold7", 0.02f), EffectArgument("ampmax7", 0.06f)
		}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS),
		ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15)
		})
		{sendInstance(); initGUI(X, Y);}
		~Harmonizer7() {quitGUI();}
	};
	
	class Harmonizer8 : public EffectAutoGUI
	{
		EFFECT_BODY(36, "Harmonizer8", "eff_harmonizer_8");
		
		Harmonizer8(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), 
		EffectArgument("amp_attack", 0.02f), EffectArgument("amp_release", 0.5f),
		EffectArgument("semitones1", 0.0f), EffectArgument("amp1", 0.0f), EffectArgument("amp_threshold1", 0.02f), EffectArgument("ampmax1", 0.06f),
		EffectArgument("semitones2", 0.0f), EffectArgument("amp2", 0.0f), EffectArgument("amp_threshold2", 0.02f), EffectArgument("ampmax2", 0.06f),
		EffectArgument("semitones3", 0.0f), EffectArgument("amp3", 0.0f), EffectArgument("amp_threshold3", 0.02f), EffectArgument("ampmax3", 0.06f),
		EffectArgument("semitones4", 0.0f), EffectArgument("amp4", 0.0f), EffectArgument("amp_threshold4", 0.02f), EffectArgument("ampmax4", 0.06f),
		EffectArgument("semitones5", 0.0f), EffectArgument("amp5", 0.0f), EffectArgument("amp_threshold5", 0.02f), EffectArgument("ampmax5", 0.06f),
		EffectArgument("semitones6", 0.0f), EffectArgument("amp6", 0.0f), EffectArgument("amp_threshold6", 0.02f), EffectArgument("ampmax6", 0.06f),
		EffectArgument("semitones7", 0.0f), EffectArgument("amp7", 0.0f), EffectArgument("amp_threshold7", 0.02f), EffectArgument("ampmax7", 0.06f),
		EffectArgument("semitones8", 0.0f), EffectArgument("amp8", 0.0f), EffectArgument("amp_threshold8", 0.02f), EffectArgument("ampmax8", 0.06f)
		}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS),
		ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15)
		})
		{sendInstance(); initGUI(X, Y);}
		~Harmonizer8() {quitGUI();}
	};
	
	
	class Playbuf : public EffectGUI
	{
		private:
			int bufnum=-1;
			static const int argsCount=4;
			
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
			int_pair visualPositions[argsCount];
			
			char playbufFileName[MAX_PATH];
			
			void constructor(int X, int Y)
			{
				FILE* file=fopen(playbufFileName, "r");
				
				if(file==NULL) 
				{
					fprintf(stderr, "Error: File '%s' not exists\n", playbufFileName);
					strcpy(playbufFileName, "/file/unknown");
				}
				
				fclose(file);
				
				fprintf(stderr, "Loading buffer from file: %s\n", playbufFileName);
				bufnum=OSCConn::loadBuffer(playbufFileName);
				
				args[0].set(bufnum);
				*(std::string*)(argsVis[0].data)=OSCConn::getBufferFileById(bufnum);
				
				int lastSlash=0;
				
				for(int i=1;playbufFileName[i]!='\0';++i)
				{
					if((playbufFileName[i]=='/' || playbufFileName[i]=='\\') && playbufFileName[i-1]!='\\')
					{
						lastSlash=i;
					}
				}
				
				(*(std::string*)(argsVis[0].data)).erase(0, lastSlash+1);
				
				sendInstance(true); 
				
				initGUI(X, Y);
				
				int w, h;
				SDL_QueryTexture(drawables[0].nameTex, NULL, NULL, &w, &h);
				
				w=std::max(100, w);
				
				visualPositions[0].first=EffectAutoGUI::slider_period + w/2;
				visualPositions[1].first=EffectAutoGUI::slider_period + w + EffectAutoGUI::slider_period;
				
				width=visualPositions[1].first + Bus::size + EffectAutoGUI::slider_period;
				height=visualPositions[1].second + Bus::size + EffectAutoGUI::bottom_padding+h-10 + EffectAutoGUI::slider_period;
				
				visualPositions[2].first=EffectAutoGUI::slider_period*2;
				visualPositions[2].second=visualPositions[1].second + h - 10 + EffectAutoGUI::slider_period;
				
				visualPositions[3].first=visualPositions[2].first+EffectAutoGUI::slider_period*2 + Bus::size;
				visualPositions[3].second=visualPositions[1].second + h - 10 + EffectAutoGUI::slider_period;
				
				updateDrawablePositions();
			}
			
			
		public:
			static constexpr const char* fullName="Playbuf";
			const char* getFullName() {return fullName;}
			static constexpr const char* name="eff_playbuf";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			int_pair* getVisualPositions() {return visualPositions;}
			
			Playbuf(int X, int Y): args({EffectArgument("bufnum", 0), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("trigger", 1.0f), EffectArgument("loop", 0.0f)}),
			argsVis({ArgVis(VT_TEXT, std::string("")), ArgVis(VT_OUTBUS), ArgVis(VT_SWITCHBUTTON, 1.0f, -1.0f, 3, 2, true), ArgVis(VT_SWITCHBUTTON, 0.0f, 1.0f, 3, 2, false)}),
			visualPositions({int_pair(0, EffectAutoGUI::top_padding), int_pair(0, EffectAutoGUI::top_padding), int_pair(0, 0), int_pair(0, 0)})
			{
				getOpenFile(playbufFileName, MAX_PATH);
				constructor(X, Y);
			}
			
			Playbuf(const char* data): args({EffectArgument("bufnum", 0), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("trigger", 1.0f), EffectArgument("loop", 0.0f)}),
			argsVis({ArgVis(VT_TEXT, std::string("")), ArgVis(VT_OUTBUS), ArgVis(VT_SWITCHBUTTON, 1.0f, -1.0f, 3, 2, true), ArgVis(VT_SWITCHBUTTON, 0.0f, 1.0f, 3, 2, false)}),
			visualPositions({int_pair(0, EffectAutoGUI::top_padding), int_pair(0, EffectAutoGUI::top_padding), int_pair(0, 0), int_pair(0, 0)})
			{
				std::stringstream ss;
				ss<<data;
				int X, Y;
				bool loopStatus;
				ss>>X>>Y>>loopStatus;
				
				ss.ignore(1, ' ');
				ss.getline(playbufFileName, MAX_PATH);
				
				constructor(X, Y);
				
				((SwitchButton*)drawables[3].drawable)->setStatus(loopStatus);
			}
			
			
			void saveData(FILE* file) 
			{
				fprintf(file, "%d %d %d %s ", posX, posY, int(((SwitchButton*)drawables[3].drawable)->getStatus()), playbufFileName);
			}
			~Playbuf() {quitGUI(); OSCConn::deleteBuffer(bufnum);}
	};
	
	class Input : public EffectAutoGUI
	{		
		EFFECT_BODY(1, "Input", "eff_input");
		
		Input(int X, int Y): args({EffectArgument("outbus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_OUTBUS)})
		{sendInstance(); initGUI(X, Y);}
		~Input() {quitGUI();}
	};
	
	class InputExtended : public EffectAutoGUI
	{
		EFFECT_BODY(8, "InputExtended", "eff_input_extended");
		
		InputExtended(int X, int Y): args({EffectArgument("outbus1", OSCConn::getFreeBus()), EffectArgument("outbus2", OSCConn::getFreeBus()), EffectArgument("outbus3", OSCConn::getFreeBus()), EffectArgument("outbus4", OSCConn::getFreeBus()),
										   EffectArgument("outbus5", OSCConn::getFreeBus()), EffectArgument("outbus6", OSCConn::getFreeBus()), EffectArgument("outbus7", OSCConn::getFreeBus()), EffectArgument("outbus8", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_OUTBUS), ArgVis(VT_OUTBUS), ArgVis(VT_OUTBUS), ArgVis(VT_OUTBUS), ArgVis(VT_OUTBUS), ArgVis(VT_OUTBUS), ArgVis(VT_OUTBUS), ArgVis(VT_OUTBUS)})
		{sendInstance(); initGUI(X, Y, 30, 30);}
		~InputExtended() {quitGUI();}
	};
	
	class Output : public EffectAutoGUI
	{		
		EFFECT_BODY(2, "Output", "eff_output");
		
		Output(int X, int Y): args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS)})
		{sendInstance(); initGUI(X, Y);}
		~Output() {quitGUI();}
	};
	
	class OutputExtended : public EffectAutoGUI
	{			
		EFFECT_BODY(8, "OutputExtended", "eff_output_extended");
		
		OutputExtended(int X, int Y): args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("inbus3", OSCConn::getFreeBus()), EffectArgument("inbus4", OSCConn::getFreeBus()),
											EffectArgument("inbus5", OSCConn::getFreeBus()), EffectArgument("inbus6", OSCConn::getFreeBus()), EffectArgument("inbus7", OSCConn::getFreeBus()), EffectArgument("inbus8", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS)})
		{sendInstance(); initGUI(X, Y, 30, 30);}
		~OutputExtended() {quitGUI();}
	};
	
	class AFM1 : public EffectAutoGUI
	{		
		EFFECT_BODY(5, "AFM1", "eff_afm1");
		
		AFM1(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("mod_index", 1.0f), EffectArgument("c", 1.0f), EffectArgument("m", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.01f, 10.0f), ArgVis(VT_GRADUALSLIDER, 1, 20), ArgVis(VT_GRADUALSLIDER, 1, 20)})
		{sendInstance(); initGUI(X, Y);}
		~AFM1() {quitGUI();}
	};
	
	class AFM1Env : public EffectAutoGUI
	{		
		EFFECT_BODY(7, "AFM1Env", "eff_afm1env");
		
		AFM1Env(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("mod_index_mul", 1.0f), 
		EffectArgument("c", 1.0f), EffectArgument("m", 1.0f), EffectArgument("amp_attackTime", 0.01f), EffectArgument("amp_releaseTime", 0.01f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.01f, 6.0f), ArgVis(VT_GRADUALSLIDER, 1, 20), ArgVis(VT_GRADUALSLIDER, 1, 20), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y, 20);}
		~AFM1Env() {quitGUI();}
	};
	
	class AFM2 : public EffectAutoGUI
	{		
		EFFECT_BODY(5, "AFM2", "eff_afm2");
		
		AFM2(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("mod_index", 1.0f), EffectArgument("c", 1.0f), EffectArgument("m", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.01f, 10.0f), ArgVis(VT_GRADUALSLIDER, 1, 20), ArgVis(VT_GRADUALSLIDER, 1, 20)})
		{sendInstance(); initGUI(X, Y);}
		~AFM2() {quitGUI();}
	};
	
	class AFM2Env : public EffectAutoGUI
	{		
		EFFECT_BODY(7, "AFM2Env", "eff_afm2env");
		
		AFM2Env(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("mod_index_mul", 1.0f), 
		EffectArgument("c", 1.0f), EffectArgument("m", 1.0f), EffectArgument("amp_attackTime", 0.01f), EffectArgument("amp_releaseTime", 0.01f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.01f, 6.0f), ArgVis(VT_GRADUALSLIDER, 1, 20), ArgVis(VT_GRADUALSLIDER, 1, 20), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y, 20);}
		~AFM2Env() {quitGUI();}
	};
	
	class Hadamard : public EffectAutoGUI
	{		
		EFFECT_BODY(3, "Hadamard", "eff_hadamard_first");
		
		Hadamard(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("hadamard_cut", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_GRADUALSLIDER, 0, 64)})
		{sendInstance(); initGUI(X, Y);}
		~Hadamard() {quitGUI();}
	};
	
	class Hadamard2 : public EffectAutoGUI
	{		
		EFFECT_BODY(3, "Hadamard2", "eff_hadamard_last");
		
		Hadamard2(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("hadamard_cut", 64.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_GRADUALSLIDER, 0, 64)})
		{sendInstance(); initGUI(X, Y);}
		~Hadamard2() {quitGUI();}
	};
	
	class Pipe : public EffectAutoGUI
	{		
		EFFECT_BODY(2, "Pipe", "eff_pipe");
		
		Pipe(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS)})
		{sendInstance(); initGUI(X, Y);}
		~Pipe() {quitGUI();}
	};
	
	class GoetzelSinus : public EffectAutoGUI
	{
		EFFECT_BODY(3, "GoetzelSinus", "eff_goetzel_sinus");
		
		GoetzelSinus(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 440.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 20000.0f)})
		{sendInstance(); initGUI(X, Y);}
		~GoetzelSinus() {quitGUI();}
	};
	
	class Select2 : public EffectAutoGUI
	{
		EFFECT_BODY(4, "Select2", "eff_select2");
		
		Select2(int X, int Y): 
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("which", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_GRADUALSLIDER, FloatArray(2, 1.0f, 0.0f))})
		{sendInstance(); initGUI(X, Y, 25);}
		~Select2() {quitGUI();}
	};
	
	class Select3 : public EffectAutoGUI
	{
		EFFECT_BODY(5, "Select3", "eff_select3");
		
		Select3(int X, int Y): 
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("inbus3", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("which", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_GRADUALSLIDER, FloatArray(3, 2.0f, 1.0f, 0.0f))})
		{sendInstance(); initGUI(X, Y, 25);}
		~Select3() {quitGUI();}
	};
	
	class Select4 : public EffectAutoGUI
	{
		EFFECT_BODY(6, "Select4", "eff_select4");
		
		Select4(int X, int Y): 
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("inbus3", OSCConn::getFreeBus()), EffectArgument("inbus4", OSCConn::getFreeBus()),
		EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("which", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_GRADUALSLIDER, FloatArray(4, 3.0f, 2.0f, 1.0f, 0.0f))})
		{sendInstance(); initGUI(X, Y, 25);}
		~Select4() {quitGUI();}
	};
	
	class Select5 : public EffectAutoGUI
	{
		EFFECT_BODY(7, "Select5", "eff_select5");
		
		Select5(int X, int Y): 
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("inbus3", OSCConn::getFreeBus()), EffectArgument("inbus4", OSCConn::getFreeBus()),
		EffectArgument("inbus5", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("which", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_GRADUALSLIDER, FloatArray(5, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f))})
		{sendInstance(); initGUI(X, Y, 25);}
		~Select5() {quitGUI();}
	};
	
	class Compander : public EffectAutoGUI
	{
		EFFECT_BODY(7, "Compander", "eff_compander");
		
		Compander(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("thresh", 0.5f), 
		EffectArgument("slopeBelow", 1.0f), EffectArgument("slopeAbove", 1.0f), EffectArgument("clampTime", 0.01f), EffectArgument("relaxTime", 0.1f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 3.0f), ArgVis(VT_SLIDER, 0.0f, 3.0f), ArgVis(VT_SLIDER, 0.0f, 0.1f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
		~Compander() {quitGUI();}
	};
	
	class WarmChorus : public EffectAutoGUI
	{
		EFFECT_BODY(6, "WarmChorus", "eff_warm_chorus");
		
		WarmChorus(int X, int Y): 
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("amp_attack", 0.02f), 
		EffectArgument("amp_release", 0.5f), EffectArgument("max_delay", 0.2f), EffectArgument("hadamard_cut", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.01f, 0.5f), ArgVis(VT_GRADUALSLIDER, 0, 25)})
		{sendInstance(); initGUI(X, Y);}
		~WarmChorus() {quitGUI();}
	};
	

	
	void registerEffects();
	
	Effect* getEffect(const char* name, int X=0, int Y=0);
	
#endif
