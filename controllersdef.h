#ifndef CONTROLLERSDEF_H
#define CONTROLLERSDEF_H
#include "controllers.h"


class MousePosController : public Controller
{
	public:
	
	static constexpr const char* name="ctr_mouseposx";
	const char* getName() {return name;}
	MousePosController(int X, int Y)
	{
		initGUI(X, Y);
	}
	
	float getValue(int id) {return 0.0f;}
};

void registerControllers();
	
Controller* getController(const char* name, int X=0, int Y=0);

#endif