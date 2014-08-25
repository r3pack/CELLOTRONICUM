#include "controllersdef.h"

void registerControllers()
{
	registerController(MousePosController::name);
}

Controller* getController(const char* name, int X, int Y)
{
	if(strcmp(name, MousePosController::name)==0) return new MousePosController(X, Y);
	else return NULL;
}