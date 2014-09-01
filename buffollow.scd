SynthDef(\eff_buffollow,{
	arg inbus, outbus, cutoff_freq=20, bufnum;
	var in = In.ar(inbus, 1);
	var out, play, freq, hasFreq, play_freq, play_hasFreq, res_freq, res_hasFreq, shift, has_output;
	# freq, hasFreq = Qitch.kr(in,~qitch_buffer.bufnum);
	freq = LPF.kr(freq, cutoff_freq);
	play = PlayBuf.ar(1, bufnum, BufRateScale.kr(bufnum), loop: 1);
	# play_freq, play_hasFreq = Qitch.kr(play, ~qitch_buffer.bufnum);
	play_freq = LPF.kr(play_freq, cutoff_freq);
	shift = Clip.kr(freq/play_freq, 0, 4);
	has_output = LPF.kr(min(play_hasFreq,hasFreq),cutoff_freq);
	out = PitchShift.ar(play,0.2,shift);
	# res_freq, res_hasFreq = Qitch.kr(out,~qitch_buffer.bufnum);
	Out.ar(outbus, out*has_output);
}).add;

SynthDef(\eff_buffollow_freq,{
	arg freq_bus, amp_bus, outbus, cutoff_freq=20, bufnum;
	var freq = In.kr(freq_bus, 1);
	var amp = In.kr(amp_bus, 1);
	var out, play, play_freq, play_hasFreq, res_freq, res_hasFreq, shift, has_output;
	play = PlayBuf.ar(1, bufnum, BufRateScale.kr(bufnum), loop: 1);
	# play_freq, play_hasFreq = Qitch.kr(play, ~qitch_buffer.bufnum);
	play_freq = LPF.kr(play_freq, cutoff_freq);
	shift = Clip.kr(freq/play_freq, 0, 4);
	has_output = LPF.kr(min(play_hasFreq,amp), cutoff_freq);
	out = PitchShift.ar(play,0.2,shift);
	# res_freq, res_hasFreq = Qitch.kr(out,~qitch_buffer.bufnum);
	Out.ar(outbus, out*has_output);
}).add;