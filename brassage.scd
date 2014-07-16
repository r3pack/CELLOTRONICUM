//BRASSAGE - Square wave (bardziej metaliczny)
SynthDef.new(\eff_brassage_plus, {
	arg inbus=8, outbus=0, freq=0, amp=0.5, delay=0.5;
	var sq = Pulse.ar(freq);
	var in = In.ar(inbus,1);
	var delayed = DelayC.ar(in,delay,delay);
	var signal = in*sq+delayed*sq;
	//var signal = in*sq-delayed*sq;
	Out.ar(outbus,signal);
}).add;

//BRASSAGE - Square wave (poprawiony wzór)
SynthDef.new(\eff_brassage, {
	arg inbus=8, outbus=0, freq=5, amp=0.5, delay=1.5;
	var sq = Pulse.ar(freq);
	var in = In.ar(inbus,1);
	var delayed = DelayC.ar(in,delay,delay);
	//var signal = in*sq+delayed*sq;
	var signal = in*sq-delayed*(sq-1);
	Out.ar(outbus,signal);
}).add;

/*/TESTS
x = Synth.new(\eff_brassage_minus, [\inbus, 8, \outbus, 0, \freq, 5, \amp, 1.0, \delay, 1.5]);
x.set(\delay,0.04);
x.set(\freq,200);
*/
//BRASSAGE - Sine wave
SynthDef.new(\eff_brassage_sin, {
	arg inbus=8, outbus=0, freq=0, amp=0.5, delay=0.5;
	var sin = SinOsc.ar(freq);
	var in = In.ar(inbus,1);
	var delayed = DelayC.ar(in,delay,delay);
	var signal = in*sin-delayed*(sin-1);
	Out.ar(outbus,signal);
}).add;

/*/TESTS
x = Synth.new(\eff_brassage_sin, [\inbus, 8, \outbus, 0, \freq, 5, \amp, 1.0, \delay, 1.5]);
x.set(\delay,0.04);
x.set(\freq,200);
*/

