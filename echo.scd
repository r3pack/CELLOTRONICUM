//DIST ECHO
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