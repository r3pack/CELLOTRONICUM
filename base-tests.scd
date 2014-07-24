//TESTS

SynthDef.new(\eff_simple_sin, {
	arg outbus=0, freq_bus=8;
	var in = In.kr(freq_bus);
	Out.ar(outbus,SinOsc.ar(in));
}).add;

x = Synth.new(\eff_simple_sin, [\freq_bus, 16]);
y = Synth.new(\eff_pitch, [\inbus, 8, \outbus, 16]);

x = Synth.new(\eff_simple_sin, [\freq_bus, 16]);
y = Synth.new(\eff_tartini_pitch, [\inbus, 8, \outbus, 16]);

// RECORDING
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

// TODO: Equalizer.
/*
http://comments.gmane.org/gmane.comp.audio.supercollider.user/91961

Sprawdzić:
DriveNoise
SinTone

Generatory:
Metro ?
/*
SynthDef.new(\eff_ ,{
	arg outbus, freq_bus, amp_bus, ;
	var freq = In.kr(freq_bus);
	var amp = In.kr(amp_bus);
	var res = .ar(freq,  , amp);
	Out.ar(outbus,res);
}).add;*/


SynthDef.new(\eff_ ,{
	arg inbus, outbus, ;
	var in = In.ar(inbus);
	var res = .ar(in,  );
	Out.ar(outbus,res);
}).add;

*/
