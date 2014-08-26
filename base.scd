SynthDef.new(\eff_limiter, {
	arg inbus, outbus, level=1, dur=0.01;
	var in = In.ar(inbus);
	var res = Limiter.ar(in,level,dur);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_compander, {
	arg inbus, outbus, thresh=0.5, slopeBelow=1, slopeAbove=1, clampTime=0.01, relaxTime=0.1;
	var in = In.ar(inbus);
	var res = Compander.ar(in,in,thresh,slopeBelow,slopeAbove,clampTime,relaxTime);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_normalizer, {
	arg inbus, outbus, level=1, dur=0.01;
	var in = In.ar(inbus);
	var res = Normalizer.ar(in,level,dur);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_mul, {
	arg inbus, outbus, mul=1;
	var in = In.ar(inbus);
	var res = in * mul;
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_mix, {
	arg inbus1, inbus2, outbus, max_amp1 = 0.5;
	var i1 = In.ar(inbus1);
	var i2 = In.ar(inbus2);
	var res = Mix.new([i1*max_amp1, i2*(1-max_amp1)]);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_mix3, {
	arg inbus1, inbus2, inbus3, outbus, max_amp1 = 0.333, max_amp2 = 0.333;
	var i1 = In.ar(inbus1);
	var i2 = In.ar(inbus2);
	var i3 = In.ar(inbus3);
	var res = Mix.new([i1*max_amp1, i2*max_amp2, i3*(1-max_amp1-max_amp2)]);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_select2, {
	arg inbus1, inbus2, outbus, which=0;
	var i1 = In.ar(inbus1);
	var i2 = In.ar(inbus2);
	var res = Select.ar(which,[i1,i2]);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_select3, {
	arg inbus1, inbus2, inbus3, outbus, which=0;
	var i1 = In.ar(inbus1);
	var i2 = In.ar(inbus2);
	var i3 = In.ar(inbus3);
	var res = Select.ar(which,[i1,i2,i3]);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_select4, {
	arg inbus1, inbus2, inbus3, inbus4, outbus, which=0;
	var i1 = In.ar(inbus1);
	var i2 = In.ar(inbus2);
	var i3 = In.ar(inbus3);
	var i4 = In.ar(inbus4);
	var res = Select.ar(which,[i1,i2,i3,i4]);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_select5, {
	arg inbus1, inbus2, inbus3, inbus4, inbus5, outbus, which=0;
	var i1 = In.ar(inbus1);
	var i2 = In.ar(inbus2);
	var i3 = In.ar(inbus3);
	var i4 = In.ar(inbus4);
	var i5 = In.ar(inbus5);
	var res = Select.ar(which,[i1,i2,i3,i4,i5]);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_amplitude, {
	arg inbus=8, outbus, attackTime=0.01, releaseTime=0.01;
	var in = In.ar(inbus);
	Out.kr(outbus,Amplitude.kr(in,attackTime, releaseTime));
}).add;

SynthDef.new(\eff_param_to_bus, {
	arg param, bus;
	Out.kr(bus, param);
}).add;

// PITCH DETECTION.
SynthDef.new(\eff_pitch, {
	arg outbus=0, inbus=8;
	var in = In.ar(inbus);
	var freq, hasFreq;
	# freq, hasFreq = Pitch.kr(in, ampThreshold: 0.02, median: 7);
	Out.kr(outbus, hasFreq*freq);
}).add;
//TODO: Wystawić parametry do pitch'a.

SynthDef.new(\eff_tartini_pitch, {
	arg outbus=0, inbus=8, cutoff=0.45;
	var in = In.ar(inbus);
	var freq, hasFreq;
	# freq, hasFreq = Tartini.kr(in);
	Out.kr(outbus,if((hasFreq>cutoff),freq,0));
}).add;

SynthDef.new(\eff_qitch_pitch, {
	arg outbus=0, inbus=8, ampThreshold=0.01, minfreq=0, maxfreq=2500;
	var in = In.ar(inbus);
	var freq, hasFreq;
	# freq, hasFreq = Qitch.kr(in,~qitch_buffer.bufnum, ampThreshold,1,minfreq:minfreq, maxfreq:maxfreq);
	Out.kr(outbus,freq);
}).add;

SynthDef.new(\eff_goetzel,{
	arg amp_outbus, freq_outbus, inbus=8, freq=440, overlap=1; //overlap <- (0,1]
	var in = In.ar(inbus);
	var bufsize = 2048;
	var real, imag, magnitude;
	# real, imag = Goertzel.kr(in,bufsize,freq,overlap);
	magnitude = (real.squared + imag.squared).sqrt*(bufsize/2).reciprocal;
	Out.kr(amp_outbus,magnitude);
	Out.kr(freq_outbus,freq);
}).add;

//CLIPPERS
SynthDef.new(\eff_Clipper32, {
	arg inbus, outbus,  lo=(-0.8), hi=0.8;
	var in = In.ar(inbus);
	var res = Clipper32.ar(in,lo,hi);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_Clipper8, {
	arg inbus, outbus, lo=(-0.8), hi=0.8;
	var in = In.ar(inbus);
	var res = Clipper8.ar(in,lo,hi);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_Clipper4, {
	arg inbus, outbus, lo=(-0.8), hi=0.8;
	var in = In.ar(inbus);
	var res = Clipper4.ar(in,lo,hi);
	Out.ar(outbus,res);
}).add;

//SOFT CLIP

SynthDef.new(\eff_SoftClipAmp ,{
	arg inbus, outbus, pregain=1;
	var in = In.ar(inbus);
	var res = SoftClipAmp.ar(in,pregain);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_SoftClipAmp4,{
	arg inbus, outbus, pregain=1;
	var in = In.ar(inbus);
	var res = SoftClipAmp4.ar(in,pregain);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_SoftClipAmp8,{
	arg inbus, outbus, pregain=1;
	var in = In.ar(inbus);
	var res = SoftClipAmp8.ar(in,pregain);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_SoftClipper4,{
	arg inbus, outbus;
	var in = In.ar(inbus);
	var res = SoftClipper4.ar(in);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_SoftClipper8,{
	arg inbus, outbus;
	var in = In.ar(inbus);
	var res = SoftClipper8.ar(in);
	Out.ar(outbus,res);
}).add;

// FILTERS
SynthDef.new(\eff_BHiPass ,{
	arg inbus, outbus, freq=1200, rq=1;
	var in = In.ar(inbus);
	var res = BHiPass.ar(in,freq, rq);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_BHiPass4 ,{
	arg inbus, outbus, freq=1200, rq=1;
	var in = In.ar(inbus);
	var res = BHiPass4.ar(in,freq,rq);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_BHiShelf ,{
	arg inbus, outbus, freq=1200, rs=1, gain=0;
	var in = In.ar(inbus);
	var res = BHiShelf.ar(in,freq, rs, gain);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_BLowPass,{
	arg inbus, outbus, freq=1200, rq=1;
	var in = In.ar(inbus);
	var res = BLowPass.ar(in,freq,rq);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_BLowPass4,{
	arg inbus, outbus, freq=1200, rq=1;
	var in = In.ar(inbus);
	var res = BLowPass4.ar(in,freq,rq);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_BLowShelf,{
	arg inbus, outbus, freq=1200, rs=1, gain=0;
	var in = In.ar(inbus);
	var res = BLowShelf.ar(in,freq,rs,gain);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_BPeakEQ,{
	arg inbus, outbus, freq=1200, rq=1, gain=0;
	var in = In.ar(inbus);
	var res = BPeakEQ.ar(in,freq,rq,gain);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_BBandPass,{
	arg inbus, outbus, freq=1200, bw=1;
	var in = In.ar(inbus);
	var res = BBandPass.ar(in,freq,bw);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_BAllPass,{
	arg inbus, outbus, freq=1200, rq=1;
	var in = In.ar(inbus);
	var res = BAllPass.ar(in,freq,rq);
	Out.ar(outbus,res);
}).add;