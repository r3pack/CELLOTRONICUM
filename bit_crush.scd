
SynthDef.new(\eff_sample_decrese, {
	arg inbus=8, outbus=0, samplerate = 4410;
	var input = In.ar(inbus,1);
	Out.ar(outbus, Latch.ar(input, Impulse.ar(samplerate)););
}).add;

SynthDef.new(\eff_bitcrush, {
	arg inbus=8, outbus=0, samplerate = SampleRate.ir, bitSize = 20;
	var input = In.ar(inbus,1);
	var bitRedux = input.round(0.5 ** bitSize);
	Out.ar(outbus,bitRedux);
}).add;

/* TESTS
b = Buffer.read(s, ~p +/+ "zBrody1.wav");
b.bufnum.postln;

// 0 - zBrody1

y = Synth.new(\eff_sample_decrese, [\inbus, 16, \outbus, 0]);
x = Synth.new(\eff_playbuf, [\outbus, 16, \bufnum, 1]);

y = Synth.new(\eff_bitcrush, [\inbus, 16, \outbus, 0]);
x = Synth.new(\eff_playbuf, [\outbus, 16, \bufnum, 1]);

y.set(\samplerate, 1000);
y.set(\bitSize, 5);

*/
SynthDef.new(\eff_mix_with_square, {
	arg inbus=8, outbus=0, freq=5, width=0.5;
	var in = In.ar(inbus,1);
	var res = in*((1+Pulse.ar(freq, width))/2); //Dust sprawdzał się podobnie.
	Out.ar(outbus, res);
}).add;

SynthDef.new(\eff_mobile_phone_lag, {
	arg inbus=8, outbus=0, freq=5, width=0.5;
	var in = In.ar(inbus,1);
	var res = in*((1+Pulse.ar(freq+GrayNoise.kr(freq), width+GrayNoise.kr(1-width)))/2);
	Out.ar(outbus, res);
}).add;


SynthDef.new(\eff_mobile_phone_lag2, {
	arg inbus=8, outbus=0, freq=5, width=0.5;
	var in = In.ar(inbus,1);
	var hfreq = freq/2;
	var hwid  = width/2;
	var pulse = max(((1+Pulse.ar(freq+GrayNoise.kr(freq), width+GrayNoise.kr(1-width)))/2)
		,((1+Pulse.ar(hfreq+GrayNoise.kr(hfreq), hwid+GrayNoise.kr(1-hwid)))/2));
	var res = in*pulse;
	Out.ar(outbus, res);
}).add;

/* TESTS
b = Buffer.read(s, ~p +/+ "zBrody1.wav");
b.bufnum.postln;
// 0 - zBrody1

s.prepareForRecord(~p +/+ "mix_mobile_phone_lag2-freq3_width07.aiff");
s.record;

y = Synth.new(\eff_mix_with_square, [\inbus, 16, \outbus, 0]);
x = Synth.new(\eff_playbuf, [\outbus, 16, \bufnum, 0]);

y = Synth.new(\eff_mix_with_square, [\inbus, 16, \outbus, 0, \freq, 8, \width, 0.2]);
x = Synth.new(\eff_playbuf, [\outbus, 16, \bufnum, 0]);

y = Synth.new(\eff_mobile_phone_lag2, [\inbus, 16, \outbus, 0, \freq, 5, \width, 0.5]);
x = Synth.new(\eff_playbuf, [\outbus, 16, \bufnum, 0]);

y = Synth.new(\eff_mobile_phone_lag2, [\inbus, 16, \outbus, 0, \freq, 3, \width, 0.7]);
x = Synth.new(\eff_playbuf, [\outbus, 16, \bufnum, 0]);

s.stopRecording;
*/