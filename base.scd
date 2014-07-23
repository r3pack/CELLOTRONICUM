SynthDef.new(\eff_limiter, {
	arg inbus, outbus, level=1, dur=0.01;
	var in = In.ar(inbus);
	var res = Limiter.ar(in,level,dur);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_normalizer, {
	arg inbus, outbus, level=1, dur=0.01;
	var in = In.ar(inbus);
	var res = Normalizer.ar(in,level,dur);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_mix, {
	arg inbus1, inbus2, outbus;
	var i1 = In.ar(inbus1);
	var i2 = In.ar(inbus2);
	var res = Mix.new([i1, i2]);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_mix3, {
	arg inbus1, inbus2, inbus3, outbus;
	var i1 = In.ar(inbus1);
	var i2 = In.ar(inbus2);
	var i3 = In.ar(inbus3);
	var res = Mix.new([i1, i2, i3]);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_amplitude, {
	arg inbus=8, outbus, attackTime=0.01, releseTime=0.01;
	var in = In.ar(inbus);
	Out.kr(outbus,Amplitude.kr(in,attackTime, releseTime));
}).add;

SyntDef.new(\eff_param_to_bus, {
	arg param, bus;
	Out.kr(bus, param);
}).add;

// PITCH DETECTION.
SynthDef.new(\eff_pitch, {
	arg outbus=0, inbus=8;
	var in = In.ar(inbus);
	var freq, hasFreq;
	# freq, hasFreq = Pitch.kr(in, ampThreshold: 0.02, median: 7);
	Out.kr(outbus, hasFreq*freq);
}).add;
//TODO: Wystawić parametry do pitch'a.

SynthDef.new(\eff_tartini_pitch, {
	arg outbus=0, inbus=8, cutoff=0.45;
	var in = In.ar(inbus);
	var freq, hasFreq;
	# freq, hasFreq = Tartini.kr(in);
	Out.kr(outbus,if((hasFreq>cutoff),freq,0));
}).add;

/*/TESTS

SynthDef.new(\eff_simple_sin, {
	arg outbus=0, freq_bus=8;
	var in = In.kr(freq_bus);
	Out.ar(outbus,SinOsc.ar(in));
}).add;

x = Synth.new(\eff_simple_sin, [\freq_bus, 16]);
y = Synth.new(\eff_pitch, [\inbus, 8, \outbus, 16]);

x = Synth.new(\eff_simple_sin, [\freq_bus, 16]);
y = Synth.new(\eff_tartini_pitch, [\inbus, 8, \outbus, 16]);
*/

SynthDef.new(\eff_goetzel,{
	arg amp_outbus, freq_outbus, inbus=8, freq=440, overlap=1; //overlap <- (0,1]
	var in = In.ar(inbus);
	var bufsize = 2048;
	var real, imag, magnitude;
	# real, imag = Goertzel.kr(in,bufsize,freq,overlap);
	magnitude = (real.squared + imag.squared).sqrt*(bufsize/2).reciprocal;
	Out.kr(amp_outbus,magnitude);
	Out.kr(freq_outbus,freq);
}).add;

/* RECORDING
b = Buffer.read(s, ~p +/+ "zBrody1.wav");
b.bufnum.postln;

s.prepareForRecord(~p +/+ "goetzel+sinusy.aiff");
s.record;
SynthDef.new(\sin, {
	arg freq_bus, amp_bus, outbus;
	var freq = In.kr(freq_bus);
	var amp = In.kr(amp_bus);
	Out.ar(outbus, FSinOsc.ar(freq,0, amp));
}).add;

x = Synth.new(\sin, [ \outbus, 0, \freq_bus, 16, \amp_bus, 18]);
y = Synth.new(\eff_goetzel, [\inbus, 17, \freq, 60.midicps, \freq_outbus, 16, \amp_outbus, 18]);
c = Synth.new(\sin, [ \outbus, 0, \freq_bus, 19, \amp_bus, 20]);
d = Synth.new(\eff_goetzel, [\inbus, 17, \freq, 62.midicps, \freq_outbus, 19, \amp_outbus, 20]);
e = Synth.new(\sin, [ \outbus, 0, \freq_bus, 21, \amp_bus, 22]);
f = Synth.new(\eff_goetzel, [\inbus, 17, \freq, 64.midicps, \freq_outbus, 21, \amp_outbus, 22]);
g = Synth.new(\sin, [ \outbus, 0, \freq_bus, 23, \amp_bus, 24]);
h = Synth.new(\eff_goetzel, [\inbus, 17, \freq, 65.midicps, \freq_outbus, 23, \amp_outbus, 24]);
i = Synth.new(\sin, [ \outbus, 0, \freq_bus, 25, \amp_bus, 26]);
j = Synth.new(\eff_goetzel, [\inbus, 17, \freq, 67.midicps, \freq_outbus, 25, \amp_outbus, 26]);
k = Synth.new(\sin, [ \outbus, 0, \freq_bus, 27, \amp_bus, 28]);
l = Synth.new(\eff_goetzel, [\inbus, 17, \freq, 69.midicps, \freq_outbus, 27, \amp_outbus, 28]);
m = Synth.new(\sin, [ \outbus, 0, \freq_bus, 29, \amp_bus, 30]);
n = Synth.new(\eff_goetzel, [\inbus, 17, \freq, 71.midicps, \freq_outbus, 29, \amp_outbus, 30]);
//o = Synth.new(\eff_output, [\inbus1, 17, \inbus2, 17]);
z = Synth.new(\eff_playbuf, [\outbus, 17, \bufnum, 0]);
*/
// TODO: Equalizer.
/*
"http://comments.gmane.org/gmane.comp.audio.supercollider.user/91961
http://comments.gmane.org/gmane.comp.audio.supercollider.user/91961"
*/