#ifndef CONTROLLERSDEF_H
#define CONTROLLERSDEF_H
#include "controllers.h"

///Definicje kontrolerów
///Zeby kontroler działał wystarczy zrobić 3 rzeczy:
///1. Napisać klase z definicją kontrolera - patrz inne definicje kontrolerów
///2. dodać linijkę 'registerController(<tu nazwa kontrolera>::name);' do funkcji registerControllers()
///3. dodać linijkę 'CONTROLLER_BY_NAME(<tu nazwa kontrolera>);' do funkcji getController()


class MousePosController : public Controller
{
	public:
	
	static constexpr const char* name="MousePos";
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
		int x, y;
		SDL_GetMouseState(&x, &y);
		int width, height;
		SDL_GetWindowSize(window, &width, &height);
		float value[2]={float(x)/float(width-1), 1.0f-float(y)/float(height-1)};
		return value[id];
	}
};

void registerControllers();
	
Controller* getController(const char* name, int X=0, int Y=0);

#endif