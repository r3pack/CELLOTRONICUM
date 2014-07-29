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
	[27.5,55,110,220,440,880,1760, 1760*2, 1760*4, 1760*8].do({
		arg f;
		res = res + SinOsc.ar(f*(2**(frac(log2(freq)-log2(f)))),0,amp*am);
	});
	Out.ar(outbus, res);
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

SynthDef.new(\eff_octave_up, { //TODO - freq_bus lub wstawić Tartini!
	arg inbus=8, outbus=0, freq, mul;
	var in = In.ar(inbus,1);
	var del2, res;
	del2 = (0.5/freq);
	res = (in + DelayC.ar(in,10,del2)) * mul;
	Out.ar(outbus, res);
}).add;

SynthDef.new(\eff_octave_down, { //TODO - freq_bus lub wstawić Tartini!
	arg inbus=8, outbus=0, freq, mul;
	var in = In.ar(inbus,1);
	var res = (in*SinOsc.ar(freq*0.5))*mul;
	Out.ar(outbus, res);
}).add;
/* WERSJA PRZEZ BUSY - nie działa!!!
SynthDef.new(\eff_shepard_tone_from_input, {
	arg inbus=8, outbus=0, amp=0.5;
	var ink = In.kr(inbus,1);
	var in = In.ar(inbus,1);
	var freq, hasFreq, res;
	var bp1=Bus.audio(s), bp2=Bus.audio(s), bp3=Bus.audio(s), bp4=Bus.audio(s), bp5=Bus.audio(s);
	var bm1=Bus.audio(s), bm2=Bus.audio(s), bm3=Bus.audio(s), bm4=Bus.audio(s);
	var p1, p2, p3, p4, p5, m1, m2, m3, m4;
	# freq, hasFreq = Tartini.kr(ink);
	p1 = Synth.new(\eff_octave_up, [\inbus, inbus, \outbus, bp1, \freq, freq]);
	p2 = Synth.new(\eff_octave_up, [\inbus, bp1, \outbus, bp2, \freq, freq*2]);
	p3 = Synth.new(\eff_octave_up, [\inbus, bp2, \outbus, bp3, \freq, freq*4]);
	p4 = Synth.new(\eff_octave_up, [\inbus, bp3, \outbus, bp4, \freq, freq*8]);
	p5 = Synth.new(\eff_octave_up, [\inbus, bp4, \outbus, bp5, \freq, freq*16]);
	m1 = Synth.new(\eff_octave_down, [\inbus, inbus, \outbus, bm1, \freq, freq]/2);
	m2 = Synth.new(\eff_octave_down, [\inbus, bm1, \outbus, bm2, \freq, freq]/4);
	m3 = Synth.new(\eff_octave_down, [\inbus, bm2, \outbus, bm3, \freq, freq]/8);
	m4 = Synth.new(\eff_octave_down, [\inbus, bm3, \outbus, bm4, \freq, freq]/16);
	res = in+In.ar(bp1,1)+In.kr(bp2,1)+In.kr(bp3,1)+In.kr(bp4,1)+In.kr(bp5,1) + In.kr(bm1,1) + In.kr(bm2,1) + In.kr(bm3,1) + In.kr(bm4,1);
	/*res=0;
	[27.5,55,110,220,440,880,1760, 1760*2, 1760*4, 1760*8].do({
		arg f;
		res = res ;
	});*/
	Out.ar(outbus, res);
}).add;
*/

//TODO: Testy
SynthDef.new(\eff_shepard_tone_from_input, {
	arg inbus=8, outbus=0; //, amp=0.5;
	var ink = In.kr(inbus,1);
	var in = In.ar(inbus,1);
	var freq, hasFreq, res;
	var p1, p2, p3, p4, p5, m1, m2, m3, m4;
	# freq, hasFreq = Tartini.kr(ink);
	p1 = in + DelayC.ar(in,10,0.5*freq);
	p2 = p1 + DelayC.ar(p1,10,0.5*freq*2);
	p3 = p2 + DelayC.ar(p2,10,0.5*freq*4);
	p4 = p3 + DelayC.ar(p3,10,0.5*freq*8);
	p5 = p4 + DelayC.ar(p4,10,0.5*freq*16);
	m1 = in*SinOsc.ar(freq/2);
	m2 = m1*SinOsc.ar(freq/4);
	m3 = m1*SinOsc.ar(freq/8);
	m4 = m1*SinOsc.ar(freq/16);
	res = p1+p2+p3+p4+p5+m1+m2+m3+m4;
	Out.ar(outbus, res);
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
