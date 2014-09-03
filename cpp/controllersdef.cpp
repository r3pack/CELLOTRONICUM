#include "controllersdef.h"

void registerControllers()
{
	registerController(MousePosController::name);
}

#define CONTROLLER_BY_NAME(a) if(strcmp(name, a::name)==0) return new a(X, Y);

Controller* getController(const char* name, int X, int Y)
{
	CONTROLLER_BY_NAME(MousePosController);
	return NULL;
}

#undef CONTROLLER_BY_NAME