//TESTY: 9-11-2014

//SHEPHARD - GENEROWANE SINUSY
x = Synth.new(\eff_shepard_tone, [ \outbus, 0, \inbus, 8, \amp, 0.4, \freq_bus, 16, \amp_bus, 17]);
y = Synth.new(\eff_amplitude, [\inbus, 8, \outbus, 17]);
z = Synth.new(\eff_tartini_pitch, [\inbus, 8, \outbus, 16]);

//SHEPHARD - GENEROWANE SINUSY + ZAWIJANIE

x = Synth.new(\eff_shepard_cycle_tone, [ \outbus, 0, \inbus, 8, \amp, 1.0, \freq_bus, 16, \amp_bus, 17]);
y = Synth.new(\eff_amplitude, [\inbus, 8, \outbus, 17]);
z = Synth.new(\eff_tartini_pitch, [\inbus, 8, \outbus, 16]);

//OKTAWA WYŻEJ

x = Synth.new(\eff_octave_up, [\inbus, 8, \outbus, 0, \freq_bus, 16]);
y = Synth.new(\eff_tartini_pitch, [\inbus, 8, \outbus, 16]);

//OKTAWA NIŻEJ

x = Synth.new(\eff_octave_down, [\inbus, 8, \outbus, 0, \freq_bus, 16]);
y = Synth.new(\eff_tartini_pitch, [\inbus, 8, \outbus, 16]);

// OKTAWER


// SHEPHARD FROM INPUT



//CHIPY
x = Synth.new(\eff_ay, [\freq_bus, 16, \amp_bus, 18, \outbus, 0]);
y = Synth.new(\eff_tartini_pitch, [\inbus, 8, \outbus, 16]);
a = Synth.new(\eff_amplitude, [\inbus, 8, \outbus, 18]);