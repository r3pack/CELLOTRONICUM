#include "effectsdef.h"
 
void registerEffects()
{
	registerEffect(Distecho::name);
	registerEffect(Playbuf::name);
	registerEffect(Output::name);
	registerEffect(Input::name);
};

Effect* getEffect(const char* name, int X, int Y)
{
	if(strcmp(name, Distecho::name)==0) return new Distecho(X, Y);
	else
	if(strcmp(name, Playbuf::name)==0) return new Playbuf(X, Y, OSCConn::loadBuffer("zBrody3.wav"));
	else
	if(strcmp(name, Output::name)==0) return new Output(X, Y);
	else
	if(strcmp(name, Input::name)==0) return new Input(X, Y);
}