#ifndef EFFECTS_H
#define EFFECTS_H
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <stdarg.h>
#include "osc.h"
#include "graphics.h"

	enum VarType{
		TYPE_UNKNOWN,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_STRING,
		TYPE_BLOB,
		TYPES_SIZE
	};
	
	class EffectArgument{
		friend class Effect;
		private:
		
			VarType type;
			const char* name;
			void* value;
			
			void set(int var);
			
			void set(float var);
			
			void set(std::string var);
			
			void addArgumentToMessage(Message* msg);
			
			void sendArgument(int id);	
			
		public:
		
			const char* getName() {return name;}
			
			float getFloatValue() {if(type==TYPE_FLOAT) return *(float*)value; else return 0.0f;}
		
			EffectArgument(const char* n, int var): name(n) {set(var);}
			EffectArgument(const char* n, float var): name(n) {set(var);}
			EffectArgument(const char* n, std::string var): name(n) {set(var);}
			
			~EffectArgument();
	};
	
	class Effect{
	
		private:
			static int lastId;		
		protected:
			int id;
			bool paused;
		public:
			bool isPaused() {return paused;}
			void pauseInstance();
			void unpauseInstance();
			void sendInstance(bool paused=false);
			void deleteInstance();
			void moveBefore(Effect* effect);
		
			Effect();
			
			~Effect();
			
			virtual const char* getName() = 0;
			virtual EffectArgument* getAgrs() = 0;
			virtual const int getAgrsCount() = 0;
			
			virtual void draw(){}
			virtual void receiveClick(int X, int Y, MouseEvent me){}
			virtual void receiveSecondClick(int X, int Y, MouseEvent me){}
			virtual void receiveThridClick(int X, int Y, MouseEvent me){}
			
			void setArgument(int argId, int value);
			void setArgument(int argId, float value);
			void setArgument(int argId, std::string value);
			
			void sendArgument(int argId);
			
			void setAndSendArgument(int argId, int value);
			void setAndSendArgument(int argId, float value);
			void setAndSendArgument(int argId, std::string value);
	};
	
	bool checkEffectsList();
	
	std::map <int, Effect*>* getEffectInstanceList();
	
	void registerEffect(const char* name);

#endif