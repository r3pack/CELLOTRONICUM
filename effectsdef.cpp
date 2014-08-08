#include "effectsdef.h"

void registerEffects()
{
	registerEffect(Distecho::name, "Effects");
	registerEffect(Playbuf::name, "Effects");
	registerEffect(Output::name, "IO_Effects");
	registerEffect(Input::name, "IO_Effects");
};

Effect* getEffect(const char* name, int X, int Y)
{
	if(strcmp(name, Distecho::name)==0) return new Distecho(X, Y);
	else
	if(strcmp(name, Playbuf::name)==0) return new Playbuf(X, Y);
	else
	if(strcmp(name, Output::name)==0) return new Output(X, Y);
	else
	if(strcmp(name, Input::name)==0) return new Input(X, Y);
}