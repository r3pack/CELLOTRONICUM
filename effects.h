#ifndef EFFECTS_H
#define EFFECTS_H
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <stdarg.h>
#include <queue>
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
			
			void addArgumentToMessage(Message* msg);
			
			void sendArgument(int id);	
			
		public:
		
			void set(int var);
			
			void set(float var);
			
			void set(std::string var);
		
			const char* getName() {return name;}
			
			float getFloatValue() {if(type==TYPE_FLOAT) return *(float*)value; else return 0.0f;}
			
			int getIntValue() {if(type==TYPE_INT) return *(int*)value; else return 0;}
		
			EffectArgument(const char* n, int var): name(n) {set(var);}
			EffectArgument(const char* n, float var): name(n) {set(var);}
			EffectArgument(const char* n, std::string var): name(n) {set(var);}
			
			~EffectArgument();
	};
	
	struct EffectCmp
	{
		bool operator()(Effect* s1, Effect* s2) const
		{
			return s1<s2;
		}
	};
		
	class Effect{
	
		private:
			static int lastId;
		
		protected:
			static std::set <std::pair<int, int> > effectTree;
			int id;
			bool paused;
		public:
		
			static void updateTopologicalSequence();
		
			bool isPaused() {return paused;}
			void pauseInstance();
			void unpauseInstance();
			void sendInstance(bool paused=false);
			void deleteInstance();
			void moveBefore(Effect* effect);
			void moveAfter(Effect* effect);
			void moveToHead();
		
			Effect();
			
			~Effect();
			
			int getId() {return id;}
			
			virtual const char* getName() = 0;
			virtual EffectArgument* getAgrs() = 0;
			virtual const int getAgrsCount() = 0;
			
			virtual void draw(){}
			virtual bool receiveClick(int X, int Y, MouseEvent me){}
			virtual bool receiveSecondClick(int X, int Y, MouseEvent me){}
			virtual bool receiveThridClick(int X, int Y, MouseEvent me){}
			
			void setArgument(int argId, int value);
			void setArgument(int argId, float value);
			void setArgument(int argId, std::string value);
			
			void sendArgument(int argId);
			
			void setAndSendArgument(int argId, int value);
			void setAndSendArgument(int argId, float value);
			void setAndSendArgument(int argId, std::string value);
	};
	
	class EffectCreator{
		private:
			int chosenEffect=0;
			std::map<const char*, bool>::iterator it;
			
			std::vector <std::pair<SDL_Texture*, SDL_Texture*> > nameTexs;
			
			int height=0;
			int width=0;
		
		public:	
			int getHeight() {return height;}
			int getWidth() {return width;}
			
			void moveUp();
			
			void moveDown();
			
			void receiveKeyboardEvent(SDL_Scancode scancode);
			
			void init();
			
			void draw(int X, int Y);
	};
	
	bool checkEffectsList();
	
	std::map <int, Effect*>* getEffectInstanceList();
	
	void registerEffect(const char* name);

#endif