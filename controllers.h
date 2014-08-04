#ifndef CONTROLLERS_H
#define CONTROLLERS_H
class Controller{
	
	virtual float getValue() = 0;
	virtual void draw() {};
	virtual const char* getName() = 0;
};

#endif