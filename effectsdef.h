#ifndef EFFECTSDEF_H
#define EFFECTSDEF_H
#include "effects.h"
#include "effectgui.h"
#include "graphics.h"
	
	
	class DistEcho : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=5;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_distecho";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			DistEcho(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("decay", 2.0f), EffectArgument("amp", 1.0f), EffectArgument("delay", 0.15f)}),
			//argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_GRADUALSLIDER, 6, 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
			//argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_ENTRYBOX), ArgVis(VT_SLIDER, 0.0f, 2.5f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
			{sendInstance(); initGUI(X, Y);}
			~DistEcho() {quitGUI();}
	};
	
	class ShiftEcho : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=6;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_shiftecho";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			ShiftEcho(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 0.0f), EffectArgument("phase", 0.0f), EffectArgument("decay", 0.5f), EffectArgument("delay", 0.5f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, -100.0f, 100.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
			{sendInstance(); initGUI(X, Y);}
			~ShiftEcho() {quitGUI();}
	};
	
	class Brassage : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=5;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_brassage";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			Brassage(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("amp", 0.5f), EffectArgument("delay", 1.5f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 15.0f)})
			{sendInstance(); initGUI(X, Y);}
			~Brassage() {quitGUI();}
	};
	
	class BrassageOSC : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=5;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_brassage_sin";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			BrassageOSC(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("amp", 0.5f), EffectArgument("delay", 1.5f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 15.0f)})
			{sendInstance(); initGUI(X, Y);}
			~BrassageOSC() {quitGUI();}
	};
	
	class BrassagePlus : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=5;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_brassage_plus";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			BrassagePlus(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("amp", 0.5f), EffectArgument("delay", 1.5f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 15.0f)})
			{sendInstance(); initGUI(X, Y);}
			~BrassagePlus() {quitGUI();}
	};
	
	class RMChorus : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=4;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_rmchorus";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			RMChorus(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 20.0f), EffectArgument("delay", 0.15f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 100.0f), ArgVis(VT_SLIDER, 0.0f, 2.0f)})
			{sendInstance(); initGUI(X, Y);}
			~RMChorus() {quitGUI();}
	};
	
	class RMChorus2 : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=3;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_rmchorus2";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			RMChorus2(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("delay", 0.15f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 2.0f)})
			{sendInstance(); initGUI(X, Y);}
			~RMChorus2() {quitGUI();}
	};
	
	class RMDelay : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=3;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_rmdelay";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			RMDelay(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("delay", 0.15f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 2.0f)})
			{sendInstance(); initGUI(X, Y);}
			~RMDelay() {quitGUI();}
	};
	
	class RMDelayRec : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=3;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_rmdelayrec";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			RMDelayRec(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("delay", 0.15f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 2.0f)})
			{sendInstance(); initGUI(X, Y, 17, 17);}
			~RMDelayRec() {quitGUI();}
	};
	
	class WSDistortion : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=3;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_wsdistortion";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			WSDistortion(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("gain", 2.0f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 10.0f)})
			{sendInstance(); initGUI(X, Y, 17, 17);}
			~WSDistortion() {quitGUI();}
	};
	
	class MobilePhoneLag3 : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=4;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_mobile_phone_lag3";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			MobilePhoneLag3(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("width", 0.5f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f)})
			{sendInstance(); initGUI(X, Y, 20, 20);}
			~MobilePhoneLag3() {quitGUI();}
	};
	
	class FreqShift : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=3;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_freqshift";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			FreqShift(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 0.0f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, -100.0f, 100.0f)})
			{sendInstance(); initGUI(X, Y);}
			~FreqShift() {quitGUI();}
	};
	
	class BLowPass : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=4;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_BLowPass";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			BLowPass(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 100.0f), EffectArgument("rq", 1.0f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
			{sendInstance(); initGUI(X, Y);}
			~BLowPass() {quitGUI();}
	};
	
	class BHiPass : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=4;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_BHiPass";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			BHiPass(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5000.0f), EffectArgument("rq", 1.0f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
			{sendInstance(); initGUI(X, Y);}
			~BHiPass() {quitGUI();}
	};
	
	class BBandPass : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=4;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_BBandPass";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			BBandPass(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 1000.0f), EffectArgument("bw", 1.0f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
			{sendInstance(); initGUI(X, Y);}
			~BBandPass() {quitGUI();}
	};
	
	class Amplitude : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=4;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_amplitude";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			Amplitude(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("attackTime", 0.01f), EffectArgument("releaseTime", 0.01f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_AMP_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
			{sendInstance(); initGUI(X, Y);}
			~Amplitude() {quitGUI();}
	};
	
	class ShepardCycleTone : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=4;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_shepard_cycle_tone";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			ShepardCycleTone(int X, int Y): 
			args({EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq_bus", OSCConn::getFreeBus()), EffectArgument("amp_bus", OSCConn::getFreeBus()), EffectArgument("amp", 0.5f)}),
			argsVis({ArgVis(VT_OUTBUS), ArgVis(VT_FREQ_INBUS), ArgVis(VT_AMP_INBUS), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
			{sendInstance(); initGUI(X, Y, 30, 30);}
			~ShepardCycleTone() {quitGUI();}
	};
	
	class Pitch : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=2;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_pitch";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			Pitch(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus())}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_FREQ_OUTBUS)})
			{sendInstance(); initGUI(X, Y);}
			~Pitch() {quitGUI();}
	};
	
	class TartiniPitch : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=3;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_tartini_pitch";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			TartiniPitch(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("cutoff", 0.45f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_FREQ_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
			{sendInstance(); initGUI(X, Y, 17, 17);}
			~TartiniPitch() {quitGUI();}
	};
	
	class Goetzel : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=5;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_goetzel";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			Goetzel(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("freq_outbus", OSCConn::getFreeBus()), EffectArgument("amp_outbus", OSCConn::getFreeBus()), EffectArgument("freq", 440.0f), EffectArgument("overlap", 1.0f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_FREQ_OUTBUS), ArgVis(VT_AMP_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 8000.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
			{sendInstance(); initGUI(X, Y, EffectAutoGUI::left_padding, 30);}
			~Goetzel() {quitGUI();}
	};
	
	class SampleDecrease : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=3;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_sample_decrese";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			SampleDecrease(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("samplerate", 20000.0f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 48000.0f)})
			{sendInstance(); initGUI(X, Y, 25, 25);}
			~SampleDecrease() {quitGUI();}
	};
	
	class BitCrush : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=3;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_bitcrush";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			BitCrush(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("bitSize", 16.0f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_GRADUALSLIDER, 1, 32)})
			{sendInstance(); initGUI(X, Y);}
			~BitCrush() {quitGUI();}
	};
	
	class Mix : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=3;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_mix";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			Mix(int X, int Y): 
			args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus())}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS)})
			{sendInstance(); initGUI(X, Y);}
			~Mix() {quitGUI();}
	};
	
	class Mix3 : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=4;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_mix3";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			Mix3(int X, int Y): 
			args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("inbus3", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus())}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS)})
			{sendInstance(); initGUI(X, Y);}
			~Mix3() {quitGUI();}
	};
	
	class Gramophone : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=8;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_gramophone";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			Gramophone(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("noise_amp", 0.2f), EffectArgument("rq", 1.0f),
			EffectArgument("freq", 1000.0f), EffectArgument("imp_freq", 5.0f), EffectArgument("blip_freq", 3.0f), EffectArgument("gain", 2.0f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.1f, 10.0f),
			ArgVis(VT_SLIDER, 1.0f, 15000.0f), ArgVis(VT_SLIDER, 0.0f, 30.0f), ArgVis(VT_SLIDER, 0.0f, 20.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
			{sendInstance(); initGUI(X, Y);}
			~Gramophone() {quitGUI();}
	};
	
	/*class TartiniPitch : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=8;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_gramophone";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			Gramophone(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("noise_amp", 0.2f), EffectArgument("rq", 1.0f),
			EffectArgument("freq", 1000.0f), EffectArgument("imp_freq", 5.0f), EffectArgument("blip_freq", 3.0f), EffectArgument("gain", 2.0f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.1f, 10.0f),
			ArgVis(VT_SLIDER, 1.0f, 15000.0f), ArgVis(VT_SLIDER, 0.0f, 30.0f), ArgVis(VT_SLIDER, 0.0f, 20.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
			{sendInstance(); initGUI(X, Y);}
			~Gramophone() {quitGUI();}
	};*/
	
	
	class Harmonizer4 : public EffectAutoGUI
	{
		private:
		
			static const int argsCount=20;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
			
		public:
			static constexpr const char* name="eff_harmonizer_4";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			Harmonizer4(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), 
			EffectArgument("amp_attack", 0.02f), EffectArgument("amp_release", 0.5f),
			EffectArgument("semitones1", 0.0f), EffectArgument("amp1", 0.0f), EffectArgument("amp_threshold1", 0.02f), EffectArgument("ampmax1", 0.06f),
			EffectArgument("semitones2", 0.0f), EffectArgument("amp2", 0.0f), EffectArgument("amp_threshold2", 0.02f), EffectArgument("ampmax2", 0.06f),
			EffectArgument("semitones3", 0.0f), EffectArgument("amp3", 0.0f), EffectArgument("amp_threshold3", 0.02f), EffectArgument("ampmax3", 0.06f),
			EffectArgument("semitones4", 0.0f), EffectArgument("amp4", 0.0f), EffectArgument("amp_threshold4", 0.02f), EffectArgument("ampmax4", 0.06f)
			}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS),
			ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
			ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
			ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
			ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
			ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15)
			})
			{sendInstance(); initGUI(X, Y);}
			~Harmonizer4() {quitGUI();}
	};
	
	
	class Playbuf : public EffectGUI
	{
		private:
			int bufnum=-1;
			static const int argsCount=2;
			
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
				
				visualPositions[0].first=EffectAutoGUI::slider_period + w/2;
				visualPositions[1].first=EffectAutoGUI::slider_period + w + EffectAutoGUI::slider_period;
				
				width=visualPositions[1].first + Bus::size + EffectAutoGUI::slider_period;
				height=visualPositions[1].second + Bus::size + EffectAutoGUI::bottom_padding+h-10;
				updateDrawablePositions();
			}
			
			
		public:
			static constexpr const char* name="eff_playbuf";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			int_pair* getVisualPositions() {return visualPositions;}
			
			Playbuf(int X, int Y): args({EffectArgument("bufnum", 0), EffectArgument("outbus", OSCConn::getFreeBus())}),
			argsVis({ArgVis(VT_TEXT, std::string("")), ArgVis(VT_OUTBUS)}),
			visualPositions({int_pair(0, EffectAutoGUI::top_padding), int_pair(0, EffectAutoGUI::top_padding)})
			{
				getOpenFile(playbufFileName, MAX_PATH);
				constructor(X, Y);
			}
			
			Playbuf(const char* data): args({EffectArgument("bufnum", 0), EffectArgument("outbus", OSCConn::getFreeBus())}),
			argsVis({ArgVis(VT_TEXT, std::string("")), ArgVis(VT_OUTBUS)}),
			visualPositions({int_pair(0, EffectAutoGUI::top_padding), int_pair(0, EffectAutoGUI::top_padding)})
			{
				std::stringstream ss;
				ss<<data;
				int X, Y;
				ss>>X>>Y;
				
				ss.ignore(1, ' ');
				ss.getline(playbufFileName, MAX_PATH);
				
				constructor(X, Y);
			}
			
			
			void saveData(FILE* file) 
			{
				fprintf(file, "%d %d %s ", posX, posY, playbufFileName);
			}
			~Playbuf() {quitGUI(); OSCConn::deleteBuffer(bufnum);}
	};
	
	class Input : public EffectAutoGUI
	{
		private:
			static const int argsCount=1;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
		public:
			static constexpr const char* name="eff_input";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			Input(int X, int Y): args({EffectArgument("outbus", OSCConn::getFreeBus())}),
			argsVis({ArgVis(VT_OUTBUS)})
			{sendInstance(); initGUI(X, Y);}
			~Input() {quitGUI();}
	};
	
	class Output : public EffectAutoGUI
	{
		private:
			static const int argsCount=2;
			EffectArgument args[argsCount];
			ArgVis argsVis[argsCount];
		public:
			static constexpr const char* name="eff_output";
			const char* getName() {return name;}
			EffectArgument* getArgs() {return args;}
			const int getArgsCount() {return argsCount;}
			ArgVis* getArgumentVisuals() {return argsVis;}
			
			Output(int X, int Y): args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus())}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS)})
			{sendInstance(); initGUI(X, Y);}
			~Output() {quitGUI();}
	};
	
	void registerEffects();
	
	Effect* getEffect(const char* name, int X=0, int Y=0);
	
#endif
