#include "effectsdef.h"

void registerEffects()
{
	registerEffect(Distecho::name, "Effects");
	registerEffect(RMChorus::name, "Effects");
	registerEffect(FreqShift::name, "Effects");
	registerEffect(Harmonizer4::name, "Effects");
	registerEffect(Playbuf::name, "IO_Effects");
	registerEffect(Output::name, "IO_Effects");
	registerEffect(Mix::name, "IO_Effects");
	registerEffect(Mix3::name, "IO_Effects");
	registerEffect(Input::name, "IO_Effects");
};

Effect* getEffect(const char* name, int X, int Y)
{
	if(strcmp(name, Distecho::name)==0) return new Distecho(X, Y);
	else
	if(strcmp(name, RMChorus::name)==0) return new RMChorus(X, Y);
	else
	if(strcmp(name, FreqShift::name)==0) return new FreqShift(X, Y);
	else
	if(strcmp(name, Mix::name)==0) return new Mix(X, Y);
	else
	if(strcmp(name, Mix3::name)==0) return new Mix3(X, Y);
	else
	if(strcmp(name, Playbuf::name)==0) return new Playbuf(X, Y);
	else
	if(strcmp(name, Output::name)==0) return new Output(X, Y);
	else
	if(strcmp(name, Input::name)==0) return new Input(X, Y);
	else
	if(strcmp(name, Harmonizer4::name)==0) return new Harmonizer4(X, Y);
	
}