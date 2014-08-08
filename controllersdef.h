#ifndef CONTROLLERSDEF_H
#define CONTROLLERSDEF_H
#include "controllers.h"


class MousePosController : public Controller
{
	public:
	
	static constexpr const char* name="ctr_mousepos";
	static constexpr int busCount=2;
	const char* busNames[busCount]={"posX", "posY"};
	
	const char* getName() {return name;}
	int getBusCount() {return busCount;}
	const char* const* getBusNames() {return busNames;}
	MousePosController(int X, int Y)
	{
		initGUI(X, Y);
	}
	
	float getValue(int id) 
	{
		int pos[2];
		SDL_GetMouseState(&pos[0], &pos[1]);
		return pos[id];
	}
};

void registerControllers();
	
Controller* getController(const char* name, int X=0, int Y=0);

#endif