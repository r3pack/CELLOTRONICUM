SynthDef.new(\eff_playbuf, {
	arg outbus=0, bufnum=0;
	Out.ar( outbus, PlayBuf.ar(1, bufnum, BufRateScale.kr(bufnum)));
}).add;

SynthDef.new(\eff_shepard_tone, {
	arg outbus=0, freq=440, amp=0.5, num=2;
	var res;
	(num.asInteger*2+1).do({
		arg f;
		res = res + SinOsc.ar(freq*(2**f),0,amp);
	});
	Out.ar(outbus, res);
}).add;

	[x | x<-(1..5)]
	(all{:x, x <- (1..3)}).do({ |x|
		x.postln;
	})
a=5;
(all{:x, x<-((0-a)..a)}).do({
		arg f;
	    f.postln;
		//res = res + SinOsc.ar(freq*f,0,amp);
	});

2**4
n = 5;
Array.fill(n*2+1,{arg i; (i-n)})