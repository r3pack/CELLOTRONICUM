#ifndef EFFECTSDEF_H
#define EFFECTSDEF_H
#include "effects.h"
#include "effectgui.h"
#include "graphics.h"
	
	
	class Distecho : public EffectAutoGUI
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
			
			Distecho(int X, int Y): 
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("decay", 2.0f), EffectArgument("amp", 1.0f), EffectArgument("delay", 0.15f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
			{sendInstance(); initGUI(X, Y);}
			~Distecho() {quitGUI();}
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
				height=visualPositions[1].second + Bus::size + EffectAutoGUI::bottom_padding;
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
