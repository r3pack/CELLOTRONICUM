SynthDef.new(\eff_afm_extended, {
	arg inbus=8, outbus=0, freq_bus, mod_index=1.0, c=1, m=1;
	var in = In.ar(inbus,1);
	var freq = In.kr(freq_bus);
	var delay;
	freq.poll();
	delay =(mod_index/(freq*3.14159))* (SinOsc.kr((freq*c)/m)+1) * 0.5;
	Out.ar(outbus, DelayN.ar(in, 3, delay));
}).add;

SynthDef.new(\eff_afm, {
	arg inbus=8, outbus=0, mod_index=1.0, c=1, m=1;
	var in = In.ar(inbus,1);
	var delay, freq, hasFreq, pitch;
	//# freq, hasFreq = Tartini.kr(in,0.93, 4096);
	# freq, hasFreq = Qitch.kr(in,~qitch_buffer.bufnum,0.01,1);
	freq.poll();
	//pitch = BLowPass.ar(K2A.ar(freq),20,1);
	delay =(mod_index/(freq*3.14159))* (SinOsc.kr((freq*c)/m)+1) * 0.5;
	Out.ar(outbus, DelayL.ar(in, 3, delay));
}).add;