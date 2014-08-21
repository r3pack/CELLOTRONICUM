#include "effectsdef.h"

void registerEffects()
{
	registerEffect(DistEcho::name, "Echo");
	registerEffect(ShiftEcho::name, "Echo");
	registerEffect(Gramophone::name, "Echo");
	registerEffect(FreqShift::name, "Echo");
	
	registerEffect(Brassage::name, "Brassage");
	registerEffect(BrassageOSC::name, "Brassage");
	registerEffect(BrassagePlus::name, "Brassage");
	registerEffect(RMChorus::name, "Brassage");
	registerEffect(RMChorus2::name, "Brassage");
	registerEffect(RMDelay::name, "Brassage");
	registerEffect(RMDelayRec::name, "Brassage");
	registerEffect(WSDistortion::name, "Brassage");
	
	registerEffect(SampleDecrease::name, "BitCrush");
	registerEffect(BitCrush::name, "BitCrush");
	registerEffect(MobilePhoneLag3::name, "BitCrush");
	
	
	registerEffect(BLowPass::name, "Filters");
	registerEffect(BHiPass::name, "Filters");
	registerEffect(BBandPass::name, "Filters");
	

	registerEffect(Amplitude::name, "Analysis");
	
	registerEffect(Pitch::name, "Analysis");
	registerEffect(TartiniPitch::name, "Analysis");
	registerEffect(Goetzel::name, "Analysis");
	
	
	registerEffect(Harmonizer4::name, "Generators");
	registerEffect(ShepardCycleTone::name, "Generators");
	
	registerEffect(Playbuf::name, "IO_Effects");
	registerEffect(Output::name, "IO_Effects");
	registerEffect(Mix::name, "IO_Effects");
	registerEffect(Mix3::name, "IO_Effects");
	registerEffect(Input::name, "IO_Effects");
};

Effect* getEffect(const char* name, int X, int Y)
{
	if(strcmp(name, DistEcho::name)==0) return new DistEcho(X, Y);
	else
	if(strcmp(name, ShiftEcho::name)==0) return new ShiftEcho(X, Y);
	else
	if(strcmp(name, Brassage::name)==0) return new Brassage(X, Y);
	else
	if(strcmp(name, BrassageOSC::name)==0) return new BrassageOSC(X, Y);
	else
	if(strcmp(name, BrassagePlus::name)==0) return new BrassagePlus(X, Y);
	else
	if(strcmp(name, RMChorus::name)==0) return new RMChorus(X, Y);
	else
	if(strcmp(name, RMChorus2::name)==0) return new RMChorus2(X, Y);
	else
	if(strcmp(name, RMDelay::name)==0) return new RMDelay(X, Y);
	else
	if(strcmp(name, RMDelayRec::name)==0) return new RMDelayRec(X, Y);
	else
	if(strcmp(name, WSDistortion::name)==0) return new WSDistortion(X, Y);
	else
	if(strcmp(name, MobilePhoneLag3::name)==0) return new MobilePhoneLag3(X, Y);
	else
	if(strcmp(name, FreqShift::name)==0) return new FreqShift(X, Y);
	else
	if(strcmp(name, BLowPass::name)==0) return new BLowPass(X, Y);
	else
	if(strcmp(name, BHiPass::name)==0) return new BHiPass(X, Y);
	else
	if(strcmp(name, BBandPass::name)==0) return new BBandPass(X, Y);
	else
	if(strcmp(name, Amplitude::name)==0) return new Amplitude(X, Y);
	else
	if(strcmp(name, ShepardCycleTone::name)==0) return new ShepardCycleTone(X, Y);
	else
	if(strcmp(name, Pitch::name)==0) return new Pitch(X, Y);
	else
	if(strcmp(name, TartiniPitch::name)==0) return new TartiniPitch(X, Y);
	else
	if(strcmp(name, Goetzel::name)==0) return new Goetzel(X, Y);
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
	else
	if(strcmp(name, Gramophone::name)==0) return new Gramophone(X, Y);
	else
	if(strcmp(name, SampleDecrease::name)==0) return new SampleDecrease(X, Y);
	else
	if(strcmp(name, BitCrush::name)==0) return new BitCrush(X, Y);
}