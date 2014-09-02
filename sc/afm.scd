SynthDef.new(\eff_afm1_extended, {
	arg inbus=8, outbus=0, freq_bus, mod_index=1.0, c=1, m=1;
	var in = In.ar(inbus,1);
	var freq = In.kr(freq_bus);
	var delay;
	freq.poll();
	delay =(mod_index/(freq*3.14159))* (SinOsc.kr((freq*c)/m)+1) * 0.5;
	Out.ar(outbus, DelayN.ar(in, 3, delay));
}).add;

SynthDef.new(\eff_afm1, {
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

SynthDef.new(\eff_afm1env, {
	arg inbus=8, outbus=0, amp_attackTime=0.01, amp_releaseTime=0.01, mod_index_mul=1.0, c=1, m=1;
	var in = In.ar(inbus,1);
	var delay, freq, hasFreq, pitch;
	var amp = Amplitude.kr(in,amp_attackTime,amp_releaseTime);
	# freq, hasFreq = Qitch.kr(in,~qitch_buffer.bufnum,0.01,1);
	delay =((amp*mod_index_mul)/(freq*3.14159))* (SinOsc.kr((freq*c)/m)+1) * 0.5;
	Out.ar(outbus, DelayN.ar(in, 3, delay));
}).add;

SynthDef.new(\eff_afm2, {
	arg inbus=8, outbus=0, mod_index=1.0, c=1, m=1;
	var in = In.ar(inbus,1);
	var eff, freq, hasFreq, pitch;
	//# freq, hasFreq = Tartini.kr(in,0.93, 4096);
	# freq, hasFreq = Qitch.kr(in,~qitch_buffer.bufnum,0.01,1);
	freq.poll();
	//pitch = BLowPass.ar(K2A.ar(freq),20,1);
	eff = cos((mod_index/(2*3.14159))* (SinOsc.kr((freq*c)/m)));
	Out.ar(outbus, in*eff);
}).add;

SynthDef.new(\eff_afm2env, {
	arg inbus=8, outbus=0, amp_attackTime=0.01, amp_releaseTime=0.01, mod_index_mul=1.0, c=1, m=1;
	var in = In.ar(inbus,1);
	var eff, freq, hasFreq, pitch;
	var amp = Amplitude.kr(in,amp_attackTime,amp_releaseTime);
	//# freq, hasFreq = Tartini.kr(in,0.93, 4096);
	# freq, hasFreq = Qitch.kr(in,~qitch_buffer.bufnum,0.01,1);
	freq.poll();
	//pitch = BLowPass.ar(K2A.ar(freq),20,1);
	eff = cos((amp*mod_index_mul/(2*3.14159))* (SinOsc.kr((freq*c)/m)));
	Out.ar(outbus, in*eff);
}).add;
