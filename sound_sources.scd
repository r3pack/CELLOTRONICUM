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
//

SynthDef.new(\eff_simple_sin, {
	arg outbus=0, freq_bus=8;
	var in = In.kr(freq_bus);
	Out.ar(outbus,SinOsc.ar(in));
}).add;

//TESTS
x = Synth.new(\eff_simple_sin, [\freq_bus, 16]);
y = Synth.new(\eff_pitch, [\inbus, 8, \outbus, 16]);


//INBUS as amp modulator :)
SynthDef.new(\eff_shepard_mosquito, {
	//arg outbus=0, freq=440, amp=0.5;
	arg outbus=0, inbus=8, freq_bus, amp=0.5;
	var freq = In.kr(freq_bus);
	var in = In.ar(inbus);
	var res=0;
	(6*2+1).do({
		arg f;
		res = res + SinOsc.ar(freq*(2**f),0,amp*in);
	});
	Out.ar(outbus, res);
}).add;

SynthDef.new(\eff_shepard_tone, {
	//arg outbus=0, freq=440, amp=0.5;
	arg outbus=0, inbus=8, freq_bus, amp=0.5;
	var freq = In.kr(freq_bus);
	var in = Amplitude.ar(In.ar(inbus));
	var res=0;
	(6*2+1).do({
		arg f;
		res = res + SinOsc.ar(freq*(2**f),0,amp*in);
	});
	Out.ar(outbus, res);
}).add;

SynthDef.new(\eff_shepard_cycle_tone, {
	//arg outbus=0, freq=440, amp=0.5;
	arg outbus=0, inbus=8, freq_bus, amp=0.5;
	var freq = In.kr(freq_bus);
	var in = Amplitude.ar(In.ar(inbus));
	var res=0;
	[27.5,55,110,220,440,880,1760, 1760*2, 1760*4, 1760*8].do({
		arg f;
		res = res + SinOsc.ar(f*(2**(frac(log2(freq)-log2(f)))),0,amp*in);
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

//* TODO: Fajny efekt - może by to wykorzystać?
// Effect based on example in documentation :)
SynthDef.new(\eff_pitch_follow, {
	arg inbus=8, outbus=0, freq_bus;
	var amp = Amplitude.kr(In.ar(inbus), 0.05, 0.05);
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


/*SynthDef("pitchFollow1",{
    var in, amp, freq, hasFreq, out;
    in = Mix.new(SoundIn.ar([0,1]));
    amp = Amplitude.kr(in, 0.05, 0.05);
    # freq, hasFreq = Pitch.kr(in, ampThreshold: 0.02, median: 7);
    //freq = Lag.kr(freq.cpsmidi.round(1).midicps, 0.05);
    out = Mix.new(VarSaw.ar(freq * [0.5,1,2], 0, LFNoise1.kr(0.3,0.1,0.1), amp));
    6.do({
        out = AllpassN.ar(out, 0.040, [0.040.rand,0.040.rand], 2)
    });
    Out.ar(0,out)
}).play(s);
*/