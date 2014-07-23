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

SynthDef.new(\eff_simple_shepard_tone, {
	arg outbus=0, freq=440, amp=0.5;
	var res=0;
	(6*2+1).do({
		arg f;
		res = res + SinOsc.ar(freq*(2**f),0,amp/13);
	});
	Out.ar(outbus, res);
}).add;

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

x = Synth.new(\eff_pila_po_przejsciach, [ \outbus, 0, \inbus, 17, \freq_bus, 16]);
y = Synth.new(\eff_pitch, [\inbus, 17, \outbus, 16]);
z = Synth.new(\eff_playbuf, [\outbus, 17, \bufnum, 1]);
s.stopRecording;
*/

SynthDef.new(\eff_ay,{
	arg freq_bus, outbus, amp_bus, f2=0.5, f3=2, gain = 25; //współcznynniki f2 i f3 odpowiadają za interwały od tonu bazowego.
	var a = gain*In.kr(amp_bus);
	var amp = a/(a.abs+1);
	var freq = In.kr(freq_bus);
	var vola=floor(amp*15), volb=floor(amp*15), volc=floor(amp*15);
	var ta= AY.freqtotone(freq),tb= AY.freqtotone(freq*f2),tc= AY.freqtotone(freq*f3);
	Out.ar(outbus, AY.ar(ta,tb,tc,1,7,vola, volb, volc));
}).add;

SynthDef.new(\eff_ym,{
	arg freq_bus, outbus, amp_bus, f2=(9.0/8.0), f3=(8.0/9.0), gain = 25; //współcznynniki f2 i f3 odpowiadają za interwały od tonu bazowego.
	var a = gain*In.kr(amp_bus);
	var amp = a/(a.abs+1);
	var freq = In.kr(freq_bus)/8;
	var vola=(amp*31), volb=0, volc=0;
	var ta= AY.freqtotone(freq),tb= AY.freqtotone(freq*f2),tc= AY.freqtotone(freq*f3);
	Out.ar(outbus, AY.ar(ta,tb,tc,1,0,vola, volb, volc, chiptype:1));
}).add;

SynthDef.new(\eff_ay_complicated,{
	arg freq1_bus, freq2_bus, freq3_bus, outbus, amp1_bus, amp2_bus, amp3_bus,
	    noise=1, noise_control=8, env_freq=4, env_style=1;
	var a1 = In.kr(amp1_bus), a2 = In.kr(amp2_bus), a3 = In.kr(amp3_bus);
	var f1=In.kr(freq1_bus), f2=In.kr(freq2_bus), f3=In.kr(freq3_bus);
	var vola=floor(a1*15), volb=floor(a2*15), volc=floor(a3*15);
	var ta= AY.freqtotone(f1),tb= AY.freqtotone(f2),tc= AY.freqtotone(f3);
	Out.ar(outbus, AY.ar(ta,tb,tc,noise,noise_control,vola, volb, volc, env_freq, env_style));
}).add;

SynthDef.new(\eff_ym_complicated,{
	arg freq1_bus, freq2_bus, freq3_bus, outbus, amp1_bus, amp2_bus, amp3_bus,
	    noise=1, noise_control=8, env_freq=4, env_style=1;
	var a1 = In.kr(amp1_bus), a2 = In.kr(amp2_bus), a3 = In.kr(amp3_bus);
	var f1=In.kr(freq1_bus), f2=In.kr(freq2_bus), f3=In.kr(freq3_bus);
	var vola=floor(a1*31), volb=floor(a2*31), volc=floor(a3*31);
	var ta= AY.freqtotone(f1),tb= AY.freqtotone(f2),tc= AY.freqtotone(f3);
	Out.ar(outbus, AY.ar(ta,tb,tc,noise,noise_control,vola, volb, volc, env_freq, env_style,1));
}).add;

/*
s.prepareForRecord(~p +/+ "ym-gain25+tartinipitch.aiff");
s.record;

x = Synth.new(\eff_ay, [\freq_bus, 16, \amp_bus, 18, \outbus, 0]);
y = Synth.new(\eff_pitch, [\inbus, 17, \outbus, 16]);
a = Synth.new(\eff_amplitude, [\inbus, 17, \outbus, 18]);
z = Synth.new(\eff_playbuf, [\outbus, 17, \bufnum, 0]);

x = Synth.new(\eff_ym, [\freq_bus, 16, \amp_bus, 18, \outbus, 0]);
a = Synth.new(\eff_amplitude, [\inbus, 17, \outbus, 18]);
y = Synth.new(\eff_tartini_pitch, [\inbus, 17, \outbus, 16]);
z = Synth.new(\eff_playbuf, [\outbus, 17, \bufnum, 0]);

s.stopRecording;
*/