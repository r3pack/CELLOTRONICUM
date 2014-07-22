SynthDef.new(\eff_output,{
	arg inbus1, inbus2;
	var in1 = In.ar(inbus1);
	var in2 = In.ar(inbus2);
	Out.ar(0,in1);
	Out.ar(1,in2);
}).add;

SynthDef.new(\eff_input,{
	arg outbus;
	var in = In.ar(8);
	Out.ar(outbus,in);
}).add;

SynthDef.new(\eff_playbuf, {
	arg outbus=0, bufnum=0;
	Out.ar( outbus, PlayBuf.ar(1, bufnum, BufRateScale.kr(bufnum)));
}).add;

SynthDef.new(\eff_amplitude, {
	arg inbus=8, outbus, attackTime=0.01, releseTime=0.01;
	var in = In.ar(inbus);
	Out.kr(outbus,Amplitude.kr(in,attackTime, releseTime));
}).add;

SyntDef.new(\eff_param_to_bus), {
	arg param, bus;
	Out.kr(bus, param);
}).add;

SynthDef.new(\eff_simple_shepard_tone, {
	arg outbus=0, freq=440, amp=0.5;
	var res=0;
	(6*2+1).do({
		arg f;
		res = res + SinOsc.ar(freq*(2**f),0,amp/13);
	});
	Out.ar(outbus, res);
}).add;

// PITCH DETECTION.
SynthDef.new(\eff_pitch, {
	arg outbus=0, inbus=8;
	var in = In.ar(inbus);
	var freq, hasFreq;
	# freq, hasFreq = Pitch.kr(in, ampThreshold: 0.02, median: 7);
	//Out.kr(outbus, if((hasFreq==1),{freq},{440}));
//	Out.kr(outbus, freq);
	Out.kr(outbus, hasFreq*freq);
}).add;
//TODO: Wystawić parametry do pitch'a.

SynthDef.new(\eff_tartini_pitch, {
	arg outbus=0, inbus=8, cutoff=0.45;
	var in = In.ar(inbus);
	var freq, hasFreq;
	# freq, hasFreq = Tartini.kr(in);
	hasFreq.poll;
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

//INBUS as amp modulator :)
SynthDef.new(\eff_shepard_mosquito, {
	//arg outbus=0, freq=440, amp=0.5;
	arg outbus=0, amp_bus, freq_bus, amp=0.5;
	var freq = In.kr(freq_bus);
	var am = In.kr(amp_bus);
	var res=0;
	(6*2+1).do({
		arg f;
		res = res + SinOsc.ar(freq*(2**f),0,amp*am);
	});
	Out.ar(outbus, res);
}).add;

SynthDef.new(\eff_shepard_tone, {
	arg outbus=0, amp_bus, freq_bus, amp=0.5;
	var freq = In.kr(freq_bus);
	var am = In.kr(amp_bus);
	var res=0;
	(6*2+1).do({
		arg f;
		res = res + SinOsc.ar(freq*(2**f),0,amp*am);
	});
	Out.ar(outbus, res);
}).add;

SynthDef.new(\eff_shepard_cycle_tone, {
	arg outbus=0, amp_bus, freq_bus, amp=0.5;
	var freq = In.kr(freq_bus);
	var am = In.kr(amp_bus);
	var res=0;
	[27.5,55,110,220,440,880,1760, 1760*2, 1760*4, 1760*8].do({
		arg f;
		res = res + SinOsc.ar(f*(2**(frac(log2(freq)-log2(f)))),0,amp*am);
	});
	Out.ar(outbus, res);
}).add;

/* RECORDING
b = Buffer.read(s, ~p +/+ "zBrody1.wav");
b.bufnum.postln;

s.prepareForRecord(~p +/+ "shephard_tone-4.aiff");
s.record;

x = Synth.new(\eff_shepard_cycle_tone, [ \outbus, 0, \inbus, 17, \amp, 0.4, \freq_bus, 16]);
y = Synth.new(\eff_pitch, [\inbus, 17, \outbus, 16]);
z = Synth.new(\eff_playbuf, [\outbus, 17, \bufnum, 1]);
s.stopRecording;

//TEST 1
SynthDef.new(\test_sin,{
	arg outbus=0, out_freq;
	var x = XLine.kr(10, 1760*8,30);
	Out.ar(outbus, SinOsc.ar(x));
	Out.kr(out_freq,x);
}).add;
x = Synth.new(\eff_shepard_cycle_tone, [ \outbus, 0, \inbus, 17, \amp, 0.4, \freq_bus, 16]);
z = Synth.new(\test_sin, [\outbus, 17, \out_freq, 16]);

//TEST 2
x = Synth.new(\eff_shepard_cycle_tone, [ \outbus, 0, \inbus, 8, \amp, 0.4, \freq_bus, 16]);
y = Synth.new(\eff_pitch, [\inbus, 8, \outbus, 16]);

//Notatka: Pitch detector ma jakies problemy z sinusami o okreslonej freq.

//TEST 3
x = Synth.new(\eff_shepard_tone, [ \outbus, 0, \amp, 0.4, \freq_bus, 8]);
x.set(\freq,150);
*/

// Effect based on example in documentation :)
SynthDef.new(\eff_pila_po_przejsciach, {
	arg outbus=0, freq_bus, amp_bus;
	var amp = In.kr(amp_bus); //Amplitude.kr(In.ar(inbus), 0.05, 0.05);
	var freq = In.kr(freq_bus);
	var out = Mix.new(VarSaw.ar(freq * [0.5,1,2], 0, LFNoise1.kr(0.3,0.1,0.1), amp));
    6.do({
        out = AllpassN.ar(out, 0.040, [0.040.rand,0.040.rand], 2)
    });
    Out.ar(outbus,out)
}).add;

/* RECORDING
b = Buffer.read(s, ~p +/+ "zBrody1.wav");
b.bufnum.postln;

s.prepareForRecord(~p +/+ "pitch_follow-4.aiff");
s.record;

x = Synth.new(\eff_pitch_follow, [ \outbus, 0, \inbus, 17, \freq_bus, 16]);
y = Synth.new(\eff_pitch, [\inbus, 17, \outbus, 16]);
z = Synth.new(\eff_playbuf, [\outbus, 17, \bufnum, 1]);
s.stopRecording;
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

/* RECORDING - nieskończone!
b = Buffer.read(s, ~p +/+ "zBrody1.wav");
b.bufnum.postln;

s.prepareForRecord(~p +/+ "goetzel+.aiff");
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

s.stopRecording;

74.midicps

*/