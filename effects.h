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
#include "drawables.h"

	struct cmpCStr
	{
	   bool operator()(char const *a, char const *b)
	   {
		  return std::strcmp(a, b) < 0;
	   }
	};

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
			
			virtual void saveData(FILE* file) {}
			virtual void loadData(char* data) {}
		
			Effect();
			
			virtual ~Effect();
			
			int getId() {return id;}
			
			virtual const char* getName() = 0;
			virtual const char* getGroup() {return "";};
			virtual EffectArgument* getArgs() = 0;
			virtual const int getArgsCount() = 0;
			
			virtual void draw(){}
			virtual bool receiveClick(int X, int Y, MouseEvent me){}
			virtual bool receiveSecondClick(int X, int Y, MouseEvent me){}
			virtual bool receiveThridClick(int X, int Y, MouseEvent me){}
			virtual bool receiveKeyboardEvent(SDL_Scancode scancode){}
			
			void setArgument(int argId, int value);
			void setArgument(int argId, float value);
			void setArgument(int argId, std::string value);
			
			void sendArgument(int argId);
			
			void setAndSendArgument(int argId, int value);
			void setAndSendArgument(int argId, float value);
			void setAndSendArgument(int argId, std::string value);
			
			static void saveToFile(const char* filename);
			
			static void loadFromFile(const char* filename);
			
			static void clearAll();
	};
	
	struct EffectCreatorMenuEntry
	{
		std::map <const char*, EffectCreatorMenuEntry*, cmpCStr>* submenuEntries=NULL;
		const char* name;
		SDL_Texture* nameTex;
		SDL_Texture* nameTexRed;
		EffectCreatorMenuEntry* parent=NULL;
		int width=0;
		
		void calculateWidth()
		{
			if(submenuEntries==NULL) return;
			for(auto it=submenuEntries->begin();it!=submenuEntries->end();++it)
			{
				int w;
				SDL_QueryTexture((*it).second->nameTex, NULL, NULL, &w, NULL);
				width=std::max(width, w);
			}
			
			for(auto it=submenuEntries->begin();it!=submenuEntries->end();++it)
			{
				(*it).second->calculateWidth();
			}
		}
		
		EffectCreatorMenuEntry(const char* n, EffectCreatorMenuEntry* p, bool isElement)
		{
			name=n;
			parent=p;
			if(!isElement) submenuEntries=new std::map <const char*, EffectCreatorMenuEntry*, cmpCStr>;
			nameTex=generateText(name);
			nameTexRed=generateText(name, COLOR_SELECTED_TEXT);
		}
		
	};
	
	class EffectCreator{
		private:
			EffectCreatorMenuEntry* chosenEffect;
		
		public:	
			static const int menu_period=30;
			
			void moveUp();
			
			void moveDown();
			
			void enter();
			
			void back();
			
			void receiveKeyboardEvent(SDL_Scancode scancode);
			
			void init();
			
			void draw(int X, int Y);
	};
	
	bool checkEffectsList();
	
	std::map <int, Effect*>* getEffectInstanceList();
	
	void registerEffect(const char* name, const char* group, const char* subgroup=NULL);

#endif