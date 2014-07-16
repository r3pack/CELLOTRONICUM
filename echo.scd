////DIST ECHO
SynthDef.new(\eff_distecho, {
	arg inbus=8, outbus=0, amp=0.5, delay=0.5, decay=0.5;
	var in = In.ar(inbus,1);
	var pom = in/(in.abs+1);
	var delayed = CombC.ar(pom,delay,delay,decay,1,in);
	Out.ar(outbus,delayed);
}).add;

/*/TESTS
x = Synth.new(\eff_distecho, [\inbus, 8, \outbus, 0, \amp, 1.0, \delay, 0.5, \decay, 2]);

x.set(\delay,0.04);
x.set(\freq,200);
*/

//SHIFT ECHO (działa)
SynthDef.new(\eff_shiftecho, {
	arg inbus=8, outbus=0, freq=1, phase=0, delay=0.5, decay=0.5;
	var in = In.ar(inbus,1);
	var pom = FreqShift.ar(in,freq,phase);
	var delayed = CombC.ar(pom,delay,delay,decay,1,in);
	Out.ar(outbus,delayed);
}).add;

/*/TESTS
x = Synth.new(\eff_shiftecho, [\inbus, 8, \outbus, 0, \delay, 0.5, \decay, 0.9, \freq, 10]);

SynthDef.all;
*/

//ECHO WITH CUSTOMIZED FEEDBACK?
SynthDef.new(\eff_genecho, {
	arg inbus=8, outbus=0, feedback_input=99, feedback_output=99, delay=0, decay=0; //.zobaczyć, czy ten feedback output jest potrzebny!
	var input = In.ar(inbus,1)+InFeedback.ar(feedback_input);
	OffsetOut.ar(feedback_output, DelayC.ar(decay*input, delay, delay - ControlRate.ir.reciprocal)); // subtract block size
	Out.ar(outbus,input);
}).add;

/*/TEST
x = Synth.new(\eff_genecho, [\inbus, 8, \outbus, 0, \delay, 0.5, \decay, 0.7]);
*/

SynthDef.new(\gramophone, {
	arg inbus=8, outbus=0, noise_amp = 0.2, rq=1, freq=1000, imp_freq=5, blip_freq=3, gain = 5;
	var input = gain* In.ar(inbus,1);
	var filtered = BBandPass.ar(WhiteNoise.ar(noise_amp/300),freq,rq);
	var sig = Impulse.kr(imp_freq,0,WhiteNoise.kr(noise_amp)) + Impulse.kr(imp_freq/2,0.1,WhiteNoise.kr(noise_amp)) + Impulse.kr(imp_freq/3,0.1,WhiteNoise.kr(noise_amp/2));
	var impulses = Blip.ar(blip_freq,300,sig*2);
	var res =input/(input.abs+1);
	Out.ar(outbus, input + impulses + filtered  + GrayNoise.ar(noise_amp/100) + WhiteNoise.ar(noise_amp/1000));
}).add;

/*x = Synth.new(\gramophone, [\inbus, 16, \outbus, 0, \noise_amp, 1.0]);
~e.["0"].moveBefore(x);*/
//TEST
/*x = Synth.new(\gramophone, [\inbus, 8, \outbus, 0, \noise_amp, 0.8]);
x.set(\noise_amp, 1.0);
x.set(\imp_freq, 5);
x.set(\blip_freq, 3);
x.set(\gain, 2);
x.set(\freq,1200);*/

/*~e.postln;
~e["2"].set(\outbus,8);

~b.postln;*/



//{Gendy1.ar(2,3,minfreq:20,maxfreq:MouseX.kr(100,1000),durscale:0.0,initCPs:40)}.play

