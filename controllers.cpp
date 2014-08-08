#include "controllers.h"

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