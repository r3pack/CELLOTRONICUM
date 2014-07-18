SynthDef.new(\eff_playbuf, {
	arg outbus=0, bufnum=0;
	Out.ar( outbus, PlayBuf.ar(1, bufnum, BufRateScale.kr(bufnum)));
}).add;

SynthDef.new(\eff_shepard_tone, {
	arg outbus=0, freq=440, amp=0.5;
	var res=0;
	(6*2+1).do({
		arg f;
		res = res + SinOsc.ar(freq*(2**f),0,amp/13);
	});
	Out.ar(outbus, res);
}).add;

/* Zrobić do końca wejcie z pitcha.
SynthDef.new(\eff_pitch, {
	arg outbus=0, inbus=8;
	Out.kr(outbus, Pitch.kr(inbus,1));
}).add;

//PROBLEM: nie da się zrobić tak, żeby była
SynthDef.new(\eff_shepard_tone, {
	//arg outbus=0, freq=440, amp=0.5;
	arg outbus=0, freq_bus, amp=0.5;
	//var freq = Pitch.kr(freq_bus);
	var res=0;
	(6*2+1).do({
		arg f;
		res = res + SinOsc.ar(Pitch.kr(freq_bus)*(2**f),0,amp/13);
	});
	Out.ar(outbus, res);
}).add;
*/
/*/TESTS
y = Synth.new(\eff_pitch, [\inbus, 8, \outbus, 16]);
x = Synth.new(\eff_shepard_tone, [ \outbus, 0, \amp, 0.4, \freq_bus, 8]);
x.set(\freq,150);
x = Synth.new(\eff_shepard_tone, [\inbus, 8, \outbus, 0, \amp, 0.4, \freq, 220/3]);
x = Synth.new(\eff_shepard_tone, [\inbus, 8, \outbus, 0, \amp, 0.4, \freq, 220/5]);
*/