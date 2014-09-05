SynthDef.new(\eff_output,{
	arg inbus1, inbus2;
	var in1 = In.ar(inbus1);
	var in2 = In.ar(inbus2);
	Out.ar(0,in1);
	Out.ar(1,in2);
}).add;

SynthDef.new(\eff_output_extended,{
	arg inbus1, inbus2, inbus3, inbus4, inbus5, inbus6, inbus7, inbus8;
	var in1 = In.ar(inbus1);
	var in2 = In.ar(inbus2);
	var in3 = In.ar(inbus3);
	var in4 = In.ar(inbus4);
	var in5 = In.ar(inbus5);
	var in6 = In.ar(inbus6);
	var in7 = In.ar(inbus7);
	var in8 = In.ar(inbus8);
	Out.ar(0,in1);
	Out.ar(1,in2);
	Out.ar(2,in3);
	Out.ar(3,in4);
	Out.ar(4,in5);
	Out.ar(5,in6);
	Out.ar(6,in7);
	Out.ar(7,in8);
}).add;

SynthDef.new(\eff_input,{
	arg outbus, input_nr=0;
	var in = SoundIn.ar(input_nr=0);//In.ar(8);
	Out.ar(outbus,in);
}).add;

SynthDef.new(\eff_input_extended,{
	arg outbus1, outbus2, outbus3, outbus4, outbus5, outbus6, outbus7, outbus8;
	var in1 = SoundIn.ar(0);
	var in2 = SoundIn.ar(1);
	var in3 = SoundIn.ar(2);
	var in4 = SoundIn.ar(3);
	var in5 = SoundIn.ar(4);
	var in6 = SoundIn.ar(5);
	var in7 = SoundIn.ar(6);
	var in8 = SoundIn.ar(7);
	Out.ar(outbus1,in1);
	Out.ar(outbus2,in2);
	Out.ar(outbus3,in3);
	Out.ar(outbus4,in4);
	Out.ar(outbus5,in5);
	Out.ar(outbus6,in6);
	Out.ar(outbus7,in7);
	Out.ar(outbus8,in8);
}).add;

SynthDef.new(\eff_playbuf, {
	arg outbus=0, bufnum=0, trigger=1, loop=0;
	Out.ar( outbus, PlayBuf.ar(1, bufnum, BufRateScale.kr(bufnum),trigger,loop:loop));
}).add;

SynthDef.new(\eff_recordbuf, {
	arg inbus=0, bufnum=0, trigger=1, loop=0;
	RecordBuf.ar(inbus, bufnum, BufRateScale.kr(bufnum), trigger, loop:loop,  doneAction:2);
}).add;

SynthDef.new(\eff_playbuf2, {
	arg outbus=0, bufnum=0, trigger=1, loop=0;
	Out.ar( outbus, PlayBuf.ar(2, bufnum, BufRateScale.kr(bufnum),trigger,loop:loop));
}).add;

SynthDef.new(\eff_sinus, {
	arg freq=440, amp=1, outbus;
	Out.ar(outbus, SinOsc.ar(freq,0,amp));
}).add;

SynthDef.new(\eff_goetzel_sinus,{
	arg inbus=8, freq=440, outbus;
	var in = In.ar(inbus);
	var bufsize = 2048, overlap=1;
	var real, imag, magnitude;
	# real, imag = Goertzel.kr(in,bufsize,freq,overlap);
	magnitude = (real.squared + imag.squared).sqrt*(bufsize/2).reciprocal;
	Out.ar(outbus, SinOsc.ar(freq,0, magnitude));
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

SynthDef.new(\eff_shepard_mosquito, {
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
	[55,110,220,440,880,1760, 1760*2].do({
		arg f;
		res = res + SinOsc.ar(f*(2**(frac(log2(freq)-log2(f)))),0,amp*am);
	});
	Out.ar(outbus, res); // TODO: Lowpass na wyjsciu
}).add;

//SHEPHARD TONE FROM INPUT

/*SynthDef.new(\eff_octave_up, { //WYSYPUJE SIĘ!
	arg inbus=8, outbus=0, freq_bus;
	var in = In.kr(inbus,1);
	var freq = In.kr(freq_bus,1);
	var del1 = 2048000/44100;
	var del2 = (500/freq)+del1;
//	var res = CombC.ar(in,del1,del1,0) + CombC.ar(in,del2,del2);
	var res = in + CombC.ar(in,del2,del2);
	Out.ar(outbus, res);
}).add;

y = Synth.new(\eff_tartini_pitch, [\inbus, 8, \outbus, 16]);
x = Synth.new(\eff_octave_up, [\inbus, 8, \outbus, 0, \freq_bus, 16]);

*/
//WAŻNE: PD - czas w ms, tutaj w sekundach!!!

SynthDef.new(\eff_octave_up, {
	arg inbus=8, outbus=0, freq_bus, mul=0.7;
	var in = In.ar(inbus,1);
	var freq = In.kr(freq_bus,1);
	var del2, res;
	del2 = (0.5/freq);
	res = (in + DelayC.ar(in,10,del2)) * mul;
	Out.ar(outbus, res);
}).add;

SynthDef.new(\eff_octave_down, {
	arg inbus=8, outbus=0, freq_bus, mul=0.7, freq_mul=0.5;
	var in = In.ar(inbus,1);
	var freq = In.kr(freq_bus,1);
	var res = (in*SinOsc.ar(freq*freq_mul))*mul;
	Out.ar(outbus, res);
}).add;

SynthDef.new(\eff_formant_filter, {
	arg inbus=8, outbus=0, mul=0.7, freq_mul=0.5;
	var in = In.ar(inbus,1);
	var freq, hasFreq;
	# freq, hasFreq = Qitch.kr(in,~qitch_buffer.bufnum,0.01,1,minfreq:0, maxfreq:2500);
	Out.ar(outbus, (in*SinOsc.ar(freq*freq_mul))*mul);
}).add;

//Działa - dorobić zawijanie.
SynthDef.new(\eff_shepard_tone_from_input, {
	arg inbus=8, outbus=0; //, amp=0.5;
	var in = In.ar(inbus,1);
	var freq, hasFreq, res, poprz;
	var plus = [0,0,0,0,0,0,0];
	var minus = [0,0,0,0,0,0,0];
	var ile = 7;
	var mi = (9.0702947845805e-005*10000);
	var frq,hf, ostatnia_deska_ratunku;
	# freq, hasFreq = Tartini.kr(in);
	freq.poll;
	frq=freq;
	poprz = in;
	for(0,6,{ |i|
		hf= 1/(2*frq);
		plus[i] = poprz + DelayN.ar(poprz,1,hf); //Select.ar( hf>mi ,[DC.ar(0), poprz + DelayN.ar(poprz,1,hf)]);
		frq=frq*2;
		poprz = plus[i];
	});
	frq=freq;
	poprz=in;
	for(0,6,{ |i|
		minus[i] = poprz*SinOsc.ar(freq/2);
		poprz = minus[i];
		frq=2*frq;
	});
	res=in;
	plus.do({ |e| res=res+e});
	//res = plus[0];
	minus.do({ |e| res=res+e});
	res = res/11;
	Out.ar(outbus, res);
}).add;

SynthDef.new(\eff_shepard_cycle_tone_from_input, {
	arg inbus=8, outbus=0, octaves=3; //, amp=0.5;
	var in = In.ar(inbus,1);
	var freq, hasFreq, res, poprz;
	var which;
	var all = [0,0,0, 0,0,0, 0,0,0, in, 0,0,0, 0,0,0, 0,0,0];
	var mi = (9.0702947845805e-005*10000);
	var frq,hf;
	# freq, hasFreq = Tartini.kr(in);
	freq.poll;
	which = min(max(0,floor(18-log2(freq))),18);
	frq=freq;
	poprz = in;
	for(10,18,{ |i|
		hf= 1/(2*frq);
		all[i] = poprz + DelayN.ar(poprz,1,hf);
		frq=frq*2;
		poprz = all[i];
	});
	frq=freq;
	poprz=in;
	for(8,0,{ |i|
		all[i] = poprz*SinOsc.ar(freq/2);
		poprz = all[i];
		frq=2*frq;
	});
	res = SelectXFocus(which,all,octaves);
	Out.ar(outbus, res);
}).add;

SynthDef.new(\eff_fbam, {
	arg freq=440, outbus=0, feedback=0.2, amp=1;
	var osc = SinOsc.ar(freq);
	var fb = LocalIn.ar(1);
	var output = LeakDC.ar(feedback*fb + osc);
	LocalOut.ar(Delay1.ar(output));
	Out.ar(outbus,output*amp);
}).add;

SynthDef.new(\eff_fbam_env, {
	arg inbus, freq=440, outbus=0, feedback=0.2, amp=1, amp_attackTime=0.01, amp_releaseTime=0.01;
	var in = In.ar(inbus,1);
	var ampitude = Amplitude.ar(in, amp_attackTime, amp_releaseTime);
	var osc = SinOsc.ar(freq);
	var fb = LocalIn.ar(1);
	var output = LeakDC.ar(feedback*fb*ampitude + osc);
	LocalOut.ar(Delay1.ar(output));
	Out.ar(outbus,output*amp);
}).add;

SynthDef.new(\eff_fbam_env1, {
	arg inbus, freq_bus, outbus=0, feedback=0.2, amp=1, amp_attackTime=0.01, amp_releaseTime=0.01;
	var in = In.ar(inbus,1);
	var freq = In.kr(freq_bus,1);
	var ampitude = Amplitude.ar(in, amp_attackTime, amp_releaseTime);
	var osc = SinOsc.ar(freq);
	var fb = LocalIn.ar(1);
	var output = LeakDC.ar(feedback*fb*ampitude + osc);
	LocalOut.ar(Delay1.ar(output));
	Out.ar(outbus,output*amp);
}).add;

SynthDef.new(\eff_fbam_fiddle, {
	arg inbus, outbus=0, feedback=0.2, amp=1, amp_attackTime=0.01, amp_releaseTime=0.01;
	var in = In.ar(inbus,1);
	var fb = LocalIn.ar(1);
	var ampitude = Amplitude.ar(in, amp_attackTime, amp_releaseTime);
	var freq, hasFreq, osc, output;
	# freq, hasFreq = Qitch.kr(in,~qitch_buffer.bufnum);
	osc = SinOsc.ar(freq);
	output = LeakDC.ar(feedback*fb*ampitude + osc);
	LocalOut.ar(Delay1.ar(output));
	Out.ar(outbus,output*amp);
}).add;

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

SynthDef.new(\eff_ay_simple,{
	arg freq_bus, outbus, amp_bus, gain = 25; //współcznynniki f2 i f3 odpowiadają za interwały od tonu bazowego.
	var a = gain*In.kr(amp_bus);
	var amp = a/(a.abs+1);
	var freq = In.kr(freq_bus);
	var vola=floor(amp*15);
	var ta= AY.freqtotone(freq);
	Out.ar(outbus, AY.ar(ta,ta,ta,1,7,vola, vola, vola));
}).add;


SynthDef.new(\eff_ay,{
	arg freq_bus, outbus, amp_bus, f2=0.5, f3=2, gain = 25; //współcznynniki f2 i f3 odpowiadają za interwały od tonu bazowego.
	var a = gain*In.kr(amp_bus);
	var amp = a/(a.abs+1);
	var freq = In.kr(freq_bus);
	var vola=floor(amp*15), volb=floor(amp*15), volc=floor(amp*15);
	var ta= AY.freqtotone(freq),tb= AY.freqtotone(freq*f2),tc= AY.freqtotone(freq*f3);
	Out.ar(outbus, AY.ar(ta,tb,tc,1,7,vola, volb, volc));
}).add;

SynthDef.new(\eff_ym_simple,{
	arg freq_bus, outbus, amp_bus, gain = 25; //współcznynniki f2 i f3 odpowiadają za interwały od tonu bazowego.
	var a = gain*In.kr(amp_bus);
	var amp = a/(a.abs+1);
	var freq = In.kr(freq_bus)/8;
	var vola=(amp*31);
	var ta= AY.freqtotone(freq);
	Out.ar(outbus, AY.ar(ta,ta,ta,1,0,vola, vola, vola, chiptype:1));
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

// STK generator pack
//TODO: Sprawdzić który parametr jest od czego i jakie ma zakresy - najlepiej już z GUI?
SynthDef.new(\eff_StkBandedWG,{
	arg outbus, freq_bus, amp_bus, instr=0, bowpressure=0, bowmotion=0, integration=0, modalresonance=64, bowvelocity=0, setstriking=0, trig=1;
	var freq = In.kr(freq_bus);
	var amp = In.kr(amp_bus);
	var res = StkBandedWG.ar(freq,instr,bowpressure,bowmotion,integration,modalresonance,bowvelocity,setstriking,trig,amp);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_StkBeeThree,{
	arg outbus, freq_bus, amp_bus, op4gain=10, op3gain=20, lfospeed=64, lfodepth=0, adsrtarget=64, trig=1;
	var freq = In.kr(freq_bus);
	var amp = In.kr(amp_bus);
	var res = StkBeeThree.ar(freq, op4gain, op3gain, lfospeed, lfodepth, adsrtarget, trig, amp);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_StkBlowHole,{
	arg outbus, freq_bus, amp_bus, reedstiffness=64, noisegain=20, tonehole=64, register=11, breathpressure=64;
	var freq = In.kr(freq_bus);
	var amp = In.kr(amp_bus);
	var res = StkBlowHole.ar(freq, reedstiffness, noisegain, tonehole, register, breathpressure,amp);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_StkBowed ,{
	arg outbus, freq_bus, amp_bus, bowpressure=64, bowposition=64, vibfreq=64, vibgain=64, loudness=64, gate=1, attackrate=1, decayrate=1;
	var freq = In.kr(freq_bus);
	var amp = In.kr(amp_bus);
	var res = StkBowed.ar(freq, bowpressure, bowposition, vibfreq, vibgain, loudness, gate, attackrate, decayrate,amp);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_StkClarinet,{
	arg outbus, freq_bus, amp_bus, reedstiffness=64, noisegain=4, vibfreq=64, vibgain=11, breathpressure=64, trig=1;
	var freq = In.kr(freq_bus);
	var amp = In.kr(amp_bus);
	var res = StkClarinet.ar(freq, reedstiffness, noisegain, vibfreq, vibgain, breathpressure, trig, amp);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_StkFlute,{
	arg outbus, freq_bus, amp_bus, jetDelay=49, noisegain=0.15, jetRatio=0.32;
	var freq = In.kr(freq_bus);
	var amp = In.kr(amp_bus);
	var res = StkFlute.ar(freq, jetDelay, noisegain, jetRatio, amp);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_StkMandolin,{
	arg outbus, freq_bus, amp_bus, bodysize=64, pickposition=64, stringdamping=69, stringdetune=10, aftertouch=64, trig=1;
	var freq = In.kr(freq_bus);
	var amp = In.kr(amp_bus);
	var res = StkMandolin.ar(freq, bodysize, pickposition, stringdamping, stringdetune, aftertouch, trig, amp);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_StkModalBar,{
	arg outbus, freq_bus, amp_bus, instrument=0, stickhardness=64, stickposition=64, vibratogain=20, vibratofreq=20, directstickmix=64, volume=64, trig=1;
	var freq = In.kr(freq_bus);
	var amp = In.kr(amp_bus);
	var res = StkModalBar.ar(freq, instrument, stickhardness, stickposition, vibratogain, vibratofreq, directstickmix, volume, trig, amp);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_StkMoog ,{
	arg outbus, freq_bus, amp_bus, filterQ=10, sweeprate=20, vibfreq=64, vibgain=0, gain=64, trig=1;
	var freq = In.kr(freq_bus);
	var amp = In.kr(amp_bus);
	var res = StkMoog.ar(freq, filterQ, sweeprate, vibfreq, vibgain, gain, trig, amp);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_StkPluck,{
	arg outbus, freq_bus, amp_bus, decay=0.99;
	var freq = In.kr(freq_bus);
	var amp = In.kr(amp_bus);
	var res = StkPluck.ar(freq, decay, amp);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_StkSaxofony,{
	arg outbus, freq_bus, amp_bus, reedstiffness=64, reedaperture=64, noisegain=20, blowposition=26, vibratofrequency=20, vibratogain=20, breathpressure=128, trig=1;
	var freq = In.kr(freq_bus);
	var amp = In.kr(amp_bus);
	var res = StkSaxofony.ar(freq, reedstiffness, reedaperture, noisegain, blowposition, vibratofrequency, vibratogain, breathpressure, trig, amp);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_StkShakers ,{
	arg outbus, amp_bus, instr=0, energy=64, decay=64, objects=64, resfreq=64;
	var amp = In.kr(amp_bus);
	var res = StkShakers.ar(instr, energy, decay, objects, resfreq, amp);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_StkVoicForm,{
	arg outbus, freq_bus, amp_bus, vuvmix=64, vowelphon=64, vibfreq=64, vibgain=20, loudness=64, trig=1;
	var freq = In.kr(freq_bus);
	var amp = In.kr(amp_bus);
	var res = StkVoicForm.ar(freq, vuvmix, vowelphon, vibfreq, vibgain, loudness, trig, amp);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_concat,{
	arg outbus, control_bus, source_bus, storesize=20, seektime=10, seekdur=10, matchlength=0.03, freezestore=0, zcr=1, lms=1, sc=1, st=1, mul=1;
	var control = In.ar(control_bus);
	var source = In.ar(source_bus);
    Out.ar(outbus,Concat2.ar(control,source,storesize,seektime,seekdur,matchlength,freezestore,zcr,lms,sc,st, mul:mul));
}).add;

SynthDef.new(\eff_concat_sinus,{
	arg outbus, freq=440, amp=1, source_bus, storesize=20, seektime=10, seekdur=10, matchlength=0.03, freezestore=0, zcr=0, lms=1, sc=1, st=1, mul=1;
	var control = SinOsc.ar(freq,0,amp);
	var source = In.ar(source_bus);
    Out.ar(outbus,Concat2.ar(control,source,storesize,seektime,seekdur,matchlength,freezestore,zcr,lms,sc,st, mul:mul));
}).add;

SynthDef.new(\eff_concat_sinus_from_bus,{
	arg outbus, freq_bus, amp_bus, source_bus, storesize=20, seektime=10, seekdur=10, matchlength=0.03, freezestore=0, zcr=0, lms=1, sc=1, st=1, mul=1;
	var freq = In.kr(freq_bus);
	var amp = In.kr(amp_bus);
	var control = SinOsc.ar(freq,0,amp);
	var source = In.ar(source_bus);
    Out.ar(outbus,Concat2.ar(control,source,storesize,seektime,seekdur,matchlength,freezestore,zcr,lms,sc,st, mul:mul));
}).add;