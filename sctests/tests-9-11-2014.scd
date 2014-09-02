//TESTY: 9-11-2014

//NAGRYWANIE
f = "filename.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

s.stopRecording;


//SHEPHARD - GENEROWANE SINUSY

f = "shephard-generowane sinusy.aiff";
s.prepareForRecord(~p +/+ f);
s.record;

x = Synth.new(\eff_shepard_tone, [ \outbus, 0, \inbus, 8, \amp, 0.4, \freq_bus, 16, \amp_bus, 17]);
y = Synth.new(\eff_amplitude, [\inbus, 8, \outbus, 17]);
z = Synth.new(\eff_tartini_pitch, [\inbus, 8, \outbus, 16]);

s.stopRecording;


//SHEPHARD - GENEROWANE SINUSY + ZAWIJANIE

f = "shephard-generowane sinusy-zawijanie.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

x = Synth.new(\eff_shepard_cycle_tone, [ \outbus, 0, \inbus, 8, \amp, 1.0, \freq_bus, 16, \amp_bus, 17]);
y = Synth.new(\eff_amplitude, [\inbus, 8, \outbus, 17]);
z = Synth.new(\eff_tartini_pitch, [\inbus, 8, \outbus, 16]);

s.stopRecording;


//OKTAWA WYŻEJ

f = "oktawa_wyzej.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

x = Synth.new(\eff_octave_up, [\inbus, 8, \outbus, 0, \freq_bus, 16]);
y = Synth.new(\eff_tartini_pitch, [\inbus, 8, \outbus, 16]);

s.stopRecording;


//OKTAWA NIŻEJ

f = "oktawa_nizej.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

x = Synth.new(\eff_octave_down, [\inbus, 8, \outbus, 0, \freq_bus, 16]);
y = Synth.new(\eff_tartini_pitch, [\inbus, 8, \outbus, 16]);

s.stopRecording;


// OKTAWER

f = "oktawer.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

x = Synth.new(\eff_shepard_tone_from_input, [\inbus, 8, \outbus, 0]);

s.stopRecording;



// SHEPHARD FROM INPUT - ZAWIJANIE

f = "shephard_from_input.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

x = Synth.new(\eff_shepard_cycle_tone_from_input, [\inbus, 8, \outbus, 0, \octaves, 5]);

s.stopRecording;

y.set(\octaves, 3);


//CHIP AY - simple

f = "ay-simple.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

x = Synth.new(\eff_ay_simple, [\freq_bus, 16, \amp_bus, 18, \outbus, 0]);
y = Synth.new(\eff_tartini_pitch, [\inbus, 8, \outbus, 16]);
a = Synth.new(\eff_amplitude, [\inbus, 8, \outbus, 18]);

s.stopRecording;

y.set(\gain, 25);


//CHIP AY

f = "ay.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

x = Synth.new(\eff_ay, [\freq_bus, 16, \amp_bus, 18, \outbus, 0]);
y = Synth.new(\eff_tartini_pitch, [\inbus, 8, \outbus, 16]);
a = Synth.new(\eff_amplitude, [\inbus, 8, \outbus, 18]);

s.stopRecording;

y.set(\gain, 25);


//CHIP YM - simple

f = "ym-simple.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

x = Synth.new(\eff_ym_simple, [\freq_bus, 16, \amp_bus, 18, \outbus, 0]);
y = Synth.new(\eff_tartini_pitch, [\inbus, 8, \outbus, 16]);
a = Synth.new(\eff_amplitude, [\inbus, 8, \outbus, 18]);

s.stopRecording;

y.set(\gain, 25);


// MOBILE PHONE LAG family ;-)

f = "mixwithsquare-freq5.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

y = Synth.new(\eff_mix_with_square, [\inbus, 8, \outbus, 0, \freq, 8, \width, 0.2]);

s.stopRecording;


f = "mobilephonelag-freq5.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

y = Synth.new(\eff_mobile_phone_lag, [\inbus, 8, \outbus, 0, \freq, 5, \width, 0.5]);

s.stopRecording;


f = "mobilephonelag-freq10.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

y = Synth.new(\eff_mobile_phone_lag, [\inbus, 8, \outbus, 0, \freq, 10, \width, 0.9]);

s.stopRecording;


f = "mobilephonelag2-freq5.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

y = Synth.new(\eff_mobile_phone_lag2, [\inbus, 8, \outbus, 0, \freq, 5, \width, 0.5]);

s.stopRecording;


f = "mobilephonelag2-freq10.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

y = Synth.new(\eff_mobile_phone_lag2, [\inbus, 8, \outbus, 0, \freq, 10, \width, 0.9]);

s.stopRecording;


f = "mobilephonelag3-freq5.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

y = Synth.new(\eff_mobile_phone_lag3, [\inbus, 8, \outbus, 0, \freq, 5, \width, 0.5]);

s.stopRecording;

//SAMPLE DECREASE

f = "sampledecrease-samplerate4410.aiff"
s.prepareForRecord(~p +/+ f);
s.record;


y = Synth.new(\eff_sample_decrese, [\inbus, 8, \outbus, 0, \samplerate, 4410]);

s.stopRecording;


y.set(\samplerate, 2205);
y.set(\samplerate, 1000);

//BIT CRUSH

f = "bitcrush.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

y = Synth.new(\eff_bitcrush, [\inbus, 8, \outbus, 0, \bitSize, 20]);

s.stopRecording;

y.set(\bitSize, 5);


//BRASSAGE - bledny wzór

f = "brassage_plus.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

x = Synth.new(\eff_brassage_plus, [\inbus, 8, \outbus, 0, \freq, 5, \amp, 1.0, \delay, 1.5]);

s.stopRecording;

x.set(\delay,0.04);
x.set(\freq,200);


// BRASSAGE - oszukany

f = "brassage.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

x = Synth.new(\eff_brassage, [\inbus, 8, \outbus, 0, \freq, 5, \amp, 1.0, \delay, 1.5]);

s.stopRecording;

x.set(\delay,0.04);
x.set(\freq,200);


// BRASSAGE - sinus

f = "brassage_sin.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

x = Synth.new(\eff_brassage_sin, [\inbus, 8, \outbus, 0, \freq, 5, \amp, 1.0, \delay, 1.5]);

s.stopRecording;

x.set(\delay,0.04);
x.set(\freq,200);

//RANDOM PITCH SHIFTER

f = "rand_pitchshift.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

x = Synth.new(\eff_rand_pitchshift, [\inbus, 8, \outbus, 0]);

s.stopRecording;

//RANDOM PITCH SHIFTER 2

f = "rand_pitchshift2.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

x = Synth.new(\eff_rand_pitchshift2, [\inbus, 8, \outbus, 0]);

s.stopRecording;

//GRAMOPHONE

f = "gramophone.aiff"
s.prepareForRecord(~p +/+ f);
s.record;

x = Synth.new(\eff_gramophone, [\inbus, 8, \outbus, 0, \noise_amp, 0.8, \rq, 1, \freq, 1000, \imp_freq, 5, \blip_freq, 3, \gain, 2]);

s.stopRecording;

x.set(\noise_amp, 0.5);
x.set(\imp_freq, 5);
x.set(\blip_freq, 3);
x.set(\gain, 2);
x.set(\freq,1200);