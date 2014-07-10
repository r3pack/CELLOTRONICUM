#ifndef EFFECTS_H
#define EFFECTS_H
#include <string>
#include <vector>

	enum VarType{
		TYPE_UNKNOWN,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_STRING,
		TYPE_BLOB,
		TYPES_SIZE
	};


	class Effect{
		public:
			virtual const char* getName() {return "unknown";}
	};
	
	class EffectInstance{
		private:
			Effect* effect;
			int id;
			static int lastId;
		public:
			EffectInstance(Effect* e) {id=lastId++; effect=e;}
			
			void createInstance()
			{
				/*const char* args=getArgumentsNames();
				for(int i=0, lastPos=0;1;++i)
				{
					if(args[i]==',' || args[i]!='\0')
					{
						
						
						if(args[i]!='\0') break;
					}
				}*/
				
				
				
			}
			
			
			void setVariable(std::string name, VarType type, void* value)
			{
			}
	};
	
	void registerEffect(Effect* eff);
	
	bool checkEffectsList();

#endif