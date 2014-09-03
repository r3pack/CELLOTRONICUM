//SHEPHARD CYCLE TONE
// RECORDING
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

//PIŁA PO PRZEJŚCIACH
// RECORDING
b = Buffer.read(s, ~p +/+ "D-DUR.aiff");
b = Buffer.read(s, ~p +/+ "zBrody1.wav");
b.bufnum.postln;

s.prepareForRecord(~p +/+ "pitch_follow-4.aiff");
s.record;

x = Synth.new(\eff_pila_po_przejsciach, [ \outbus, 0, \inbus, 17, \freq_bus, 16]);
y = Synth.new(\eff_pitch, [\inbus, 17, \outbus, 16]);
z = Synth.new(\eff_playbuf, [\outbus, 17, \bufnum, 1]);
s.stopRecording;

// AY & YM
// RECORDING
s.prepareForRecord(~p +/+ "ym-gain25+tartinipitch.aiff");
s.record;

x = Synth.new(\eff_ay, [\freq_bus, 16, \amp_bus, 18, \outbus, 0]);
y = Synth.new(\eff_tartini_pitch, [\inbus, 17, \outbus, 16]);
a = Synth.new(\eff_amplitude, [\inbus, 17, \outbus, 18]);
z = Synth.new(\eff_playbuf, [\outbus, 17, \bufnum, 0]);

x = Synth.new(\eff_ym, [\freq_bus, 16, \amp_bus, 18, \outbus, 0]);
a = Synth.new(\eff_amplitude, [\inbus, 17, \outbus, 18]);
y = Synth.new(\eff_tartini_pitch, [\inbus, 17, \outbus, 16]);
z = Synth.new(\eff_playbuf, [\outbus, 17, \bufnum, 0]);

s.stopRecording;

// TEST
SynthDef.new(\id, {
	arg inbus, outbus;
	var in = In.ar(inbus,1);
	Out.ar(outbus, in);
}).add;


x = Synth.new(\eff_octave_up, [\inbus, 17, \freq_bus, 16, \outbus, 0]);
y = Synth.new(\eff_pitch, [\inbus, 17, \outbus, 0]);
z = Synth.new(\eff_playbuf, [\outbus, 0, \bufnum, 1]);

z = Synth.new(\eff_playbuf, [\outbus, 0, \bufnum, 0]);

//* TEST
x = Synth.new(\eff_shepard_tone_from_input, [\outbus, 0, \inbus, 17]);
z = Synth.new(\eff_playbuf, [\outbus, 17, \bufnum, 3]);

s.prepareForRecord(~p +/+ "shaphard-cycle-test.aiff");
s.record;
x = Synth.new(\eff_shepard_cycle_tone_from_input, [\outbus, 0, \inbus, 17]);
z = Synth.new(\eff_playbuf, [\outbus, 17, \bufnum, 3]);
z = Synth.new(\eff_playbuf, [\outbus, 1, \bufnum, 1]);
s.stopRecording;


//NIE DZIAAAAŁAAA!
SynthDef.new(\eff_xxx, {
	arg outbus;
	Out.kr(outbus, MouseX.kr(1,64));
});

x = Synth.new(\eff_octave_down, [\inbus, 0, \freq_bus, 16, \outbus, 0, \freq_mul_bus, 17]);
y = Synth.new(\eff_pitch, [\inbus, 0, \outbus, 16]);
z = Synth.new(\eff_xxx, [\outbus, 17]);


// CONCAT2
x = Synth.new(\eff_concat, [\outbus, 0, \control_bus, 17, \source_bus, 18]);
y = Synth.new(\eff_playbuf, [\outbus, 18, \bufnum, 1]); //control
z = Synth.new(\eff_playbuf, [\outbus, 17, \bufnum, 2]); //source

x = Synth.new(\eff_concat_sinus, [\outbus, 0, \freq, 220, \source_bus, 18]);
y = Synth.new(\eff_playbuf, [\outbus, 18, \bufnum, 0]); //control

// 0-sarabanda
// 1-zbrody 1
// 2 - d