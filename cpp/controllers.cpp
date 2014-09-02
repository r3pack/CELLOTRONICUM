#include "controllers.h"
#include "effectsdef.h"

std::map <ControllBus*, Controller*> controllerByBus;

std::map <int, Controller*> controllerInstanceList;

std::map <int, Controller*>* getControllerInstanceList()
{
	return &controllerInstanceList;
}

std::set<const char*, cmpCStr2> controllerList;

std::set<const char*, cmpCStr2>* getControllerList()
{
	return &controllerList;
}

void registerController(const char* name)
{
	controllerList.insert(name);
}

int Controller::lastId=0;

void Controller::saveData(FILE* file) 
{
	fprintf(file, "%d %d ", posX, posY);
	
	for(auto it=controlledValueGifters.begin();it!=controlledValueGifters.end();++it)
	{
		fprintf(file, "%d %d %d ", it->first, it->second->effect->getId(), it->second->argument);
	}
}

void Controller::loadData(char* str) 
{
	std::stringstream ss;
	ss<<str;
	
	int X, Y;
	
	ss>>X>>Y;
	
	setPos(X, Y);
	
	int busId, effectId, argument;
	
	while(ss>>busId>>effectId>>argument)
	{					
		EffectGUI* effect=(EffectGUI*)(getEffectInstanceList()->find(effectId)->second);
		Slider* slider=(Slider*)(effect->drawables[argument].drawable);
		
		controlledValueGifters.push_back(std::pair<int, Slider*>(busId, slider));
		slider->controlledBy=this;
	}
}