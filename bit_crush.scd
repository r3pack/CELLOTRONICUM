
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


{|in, rate= 0.5, bits= 4| Latch.ar(in, Impulse.ar(SampleRate.ir*0.5*rate)).round(0.5**bits)}.play;
*/