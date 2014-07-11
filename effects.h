#ifndef EFFECTS_H
#define EFFECTS_H
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <array>
#include "osc.h"

	enum VarType{
		TYPE_UNKNOWN,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_STRING,
		TYPE_BLOB,
		TYPES_SIZE
	};
	
	class EffectArgument{
		VarType type;
		const char* name;
		void* value;
		
		public:
		
		template <class T> 
		EffectArgument(const char* n, T var) {name=n; set(var);}
		
		void set(int var);
		
		void set(float var);
		
		void set(std::string var);
		
		void getArgumentStr(std::ostringstream& ss);
		
		void sendArgument(const char* effect);
		
		~EffectArgument();
	};
	
	class Effect{
	
		private:
			int id;
			static int lastId;
		public:
			Effect() {id=lastId++;}
		
			virtual const char* getName() = 0;
			virtual EffectArgument* getAgrs() = 0;
			virtual const int getAgrsCount() = 0;
			
			template <class T> void setArgument(int id, T value);
			
			void sendArgument(int id);
			
			template <class T> void setAndSendArgument(int id, T value);
			
			void sendInstance();
			
			void registerEffect();
	};
	
	bool checkEffectsList();

#endif