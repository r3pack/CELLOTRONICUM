SynthDef.new(\eff_hadamard_first, {
	arg inbus=8, outbus=0, hadamard_cut=10;
	var in = In.ar(inbus,1);
	var res = WalshHadamard.ar(in, hadamard_cut);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_hadamard_last, {
	arg inbus=8, outbus=0, hadamard_cut=10;
	var in = In.ar(inbus,1);
	var res = in - WalshHadamard.ar(in, hadamard_cut);
	Out.ar(outbus,res);
}).add;

/*
SynthDef.new(\eff_warm_chorus, {
	//Pierwsza próba - na razie na gotowych pitch shifterach
	//http://quod.lib.umich.edu/i/icmc/bbp2372.2012.014/--warm-chorus-re-thinking-the-chorus-effect-using/4?view=pdf
	arg inbus=8, outbus=0,
        amp_attack=0.02, amp_release=0.5, max_delay=0.2, hadamard_cut=1;
    var in = In.ar(inbus,1);
	var amp = Amplitude.ar(in, amp_attack,amp_release);
	var min_delay = SampleDur.ir*4;
	var semitones = [0, 0.02, 0.03, 0.05, 0.07, 0.11, 0.13];
	var delays = [ExpRand.new(min_delay,max_delay), ExpRand.new(min_delay,max_delay), ExpRand.new(min_delay,max_delay), ExpRand.new(min_delay,max_delay), ExpRand.new(min_delay,max_delay), ExpRand.new(min_delay,max_delay), ExpRand.new(min_delay,max_delay)];
	var sig = semitones.collect({|e, i| PitchShift.ar(DelayC.ar(in, max_delay, delays[i]), 0.2, (pow(2,e/12)));}); //optymalizacja na później - multiple-tap delay line
	var res = WalshHadamard.ar(Mix.ar(sig)/8, hadamard_cut);
	delays.poll;
    Out.ar(outbus,res);
}).add;
*/

/* TESTS

b = Buffer.read(s, ~p +/+ "D-DUR.aiff");
b = Buffer.read(s, ~p +/+ "zBrody1.wav");


s.prepareForRecord(~p +/+ "d-dur-harmonizer.aiff");
s.record;

x = Synth.new(\eff_hadamard_first,
	[\inbus, 16, \outbus, 0]);
Synth.new(\eff_playbuf, [\outbus, 0, \bufnum, 0]);

x.set(\hadamard_cut, 0);


s.stopRecording;

*/

SynthDef.new(\eff_harmonizer_4, {
	arg inbus=8, outbus=0,
	    amp_attack=0.02, amp_release=0.5,
	   // int,     0 do 1     0 do 1      0 do 1
	    semitones1, amp1=0, amp_threshold1=0.06, ampmax1=0.09,
	    semitones2, amp2=0, amp_threshold2, ampmax2,
	    semitones3, amp3=0, amp_threshold3, ampmax3,
	    semitones4, amp4=0, amp_threshold4, ampmax4;
	var in = In.ar(inbus,1);
	var amp = Amplitude.ar(in, amp_attack,amp_release);
	var w1 = ceil(thresh(amp ,amp_threshold1));
	var a1 = Clip.ar((amp1*(amp-amp_threshold1))/(ampmax1-amp_threshold1), 0, amp1);
	var p1 = Select.ar( w1, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones1/12)), mul: w1*a1)]);

	var w2 = ceil(thresh(amp ,amp_threshold2));
	var a2 = Clip.ar((amp2*(amp-amp_threshold2))/(ampmax2-amp_threshold2), 0, amp2);
	var p2 = Select.ar( w2, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones2/12)), mul: w2*a2)]);

	var w3 = ceil(thresh(amp ,amp_threshold3));
	var a3 = Clip.ar((amp3*(amp-amp_threshold3))/(ampmax3-amp_threshold3), 0, amp3);
	var p3 = Select.ar( w3, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones3/12)), mul: w3*a3)]);

	var w4 = ceil(thresh(amp ,amp_threshold4));
	var a4 = Clip.ar((amp4*(amp-amp_threshold4))/(ampmax4-amp_threshold4), 0, amp4);
	var p4 = Select.ar( w4, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones4/12)), mul: w4*a4)]);
	amp.poll();
	w1.poll();
	w2.poll();
	Out.ar(outbus,(in+p1+p2+p3+p4)/5);
}).add;

SynthDef.new(\eff_harmonizer_5, {
	arg inbus=8, outbus=0,
	    amp_attack=0.02, amp_release=0.5,
	   // int,     0 do 1     0 do 1      0 do 1
	    semitones1, amp1=0, amp_threshold1=0.06, ampmax1=0.09,
	    semitones2, amp2=0, amp_threshold2, ampmax2,
	    semitones3, amp3=0, amp_threshold3, ampmax3,
	    semitones4, amp4=0, amp_threshold4, ampmax4,
	    semitones5, amp5=0, amp_threshold5, ampmax5;
	var in = In.ar(inbus,1);
	var amp = Amplitude.ar(in, amp_attack,amp_release);
	var w1 = ceil(thresh(amp ,amp_threshold1));
	var a1 = Clip.ar((amp1*(amp-amp_threshold1))/(ampmax1-amp_threshold1), 0, amp1);
	var p1 = Select.ar( w1, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones1/12)), mul: w1*a1)]);

	var w2 = ceil(thresh(amp ,amp_threshold2));
	var a2 = Clip.ar((amp2*(amp-amp_threshold2))/(ampmax2-amp_threshold2), 0, amp2);
	var p2 = Select.ar( w2, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones2/12)), mul: w2*a2)]);

	var w3 = ceil(thresh(amp ,amp_threshold3));
	var a3 = Clip.ar((amp3*(amp-amp_threshold3))/(ampmax3-amp_threshold3), 0, amp3);
	var p3 = Select.ar( w3, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones3/12)), mul: w3*a3)]);

	var w4 = ceil(thresh(amp ,amp_threshold4));
	var a4 = Clip.ar((amp4*(amp-amp_threshold4))/(ampmax4-amp_threshold4), 0, amp4);
	var p4 = Select.ar( w4, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones4/12)), mul: w4*a4)]);

	var w5 = ceil(thresh(amp ,amp_threshold5));
	var a5 = Clip.ar((amp5*(amp-amp_threshold5))/(ampmax5-amp_threshold5), 0, amp5);
	var p5 = Select.ar( w5, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones5/12)), mul: w5*a5)]);

	amp.poll();

	Out.ar(outbus,(in+p1+p2+p3+p4+p5)/6);
}).add;

SynthDef.new(\eff_harmonizer_6, {
	arg inbus=8, outbus=0,
	    amp_attack=0.02, amp_release=0.5,
	   // int,     0 do 1     0 do 1      0 do 1
	    semitones1, amp1=0, amp_threshold1=0.06, ampmax1=0.09,
	    semitones2, amp2=0, amp_threshold2, ampmax2,
	    semitones3, amp3=0, amp_threshold3, ampmax3,
	    semitones4, amp4=0, amp_threshold4, ampmax4,
	    semitones5, amp5=0, amp_threshold5, ampmax5,
	    semitones6, amp6=0, amp_threshold6, ampmax6;
	var in = In.ar(inbus,1);
	var amp = Amplitude.ar(in, amp_attack,amp_release);
	var w1 = ceil(thresh(amp ,amp_threshold1));
	var a1 = Clip.ar((amp1*(amp-amp_threshold1))/(ampmax1-amp_threshold1), 0, amp1);
	var p1 = Select.ar( w1, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones1/12)), mul: w1*a1)]);

	var w2 = ceil(thresh(amp ,amp_threshold2));
	var a2 = Clip.ar((amp2*(amp-amp_threshold2))/(ampmax2-amp_threshold2), 0, amp2);
	var p2 = Select.ar( w2, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones2/12)), mul: w2*a2)]);

	var w3 = ceil(thresh(amp ,amp_threshold3));
	var a3 = Clip.ar((amp3*(amp-amp_threshold3))/(ampmax3-amp_threshold3), 0, amp3);
	var p3 = Select.ar( w3, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones3/12)), mul: w3*a3)]);

	var w4 = ceil(thresh(amp ,amp_threshold4));
	var a4 = Clip.ar((amp4*(amp-amp_threshold4))/(ampmax4-amp_threshold4), 0, amp4);
	var p4 = Select.ar( w4, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones4/12)), mul: w4*a4)]);

	var w5 = ceil(thresh(amp ,amp_threshold5));
	var a5 = Clip.ar((amp5*(amp-amp_threshold5))/(ampmax5-amp_threshold5), 0, amp5);
	var p5 = Select.ar( w5, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones5/12)), mul: w5*a5)]);

	var w6 = ceil(thresh(amp ,amp_threshold6));
	var a6 = Clip.ar((amp6*(amp-amp_threshold6))/(ampmax6-amp_threshold6), 0, amp6);
	var p6 = Select.ar( w6, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones6/12)), mul: w6*a6)]);

	Out.ar(outbus,(in+p1+p2+p3+p4+p5+p6)/7);
}).add;


SynthDef.new(\eff_harmonizer_7, {
	arg inbus=8, outbus=0,
	    amp_attack=0.02, amp_release=0.5,
	   // int,     0 do 1     0 do 1      0 do 1
	    semitones1, amp1=0, amp_threshold1=0.06, ampmax1=0.09,
	    semitones2, amp2=0, amp_threshold2, ampmax2,
	    semitones3, amp3=0, amp_threshold3, ampmax3,
	    semitones4, amp4=0, amp_threshold4, ampmax4,
	    semitones5, amp5=0, amp_threshold5, ampmax5,
	    semitones6, amp6=0, amp_threshold6, ampmax6,
	    semitones7, amp7=0, amp_threshold7, ampmax7;
	var in = In.ar(inbus,1);
	var amp = Amplitude.ar(in, amp_attack,amp_release);
	var w1 = ceil(thresh(amp ,amp_threshold1));
	var a1 = Clip.ar((amp1*(amp-amp_threshold1))/(ampmax1-amp_threshold1), 0, amp1);
	var p1 = Select.ar( w1, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones1/12)), mul: w1*a1)]);

	var w2 = ceil(thresh(amp ,amp_threshold2));
	var a2 = Clip.ar((amp2*(amp-amp_threshold2))/(ampmax2-amp_threshold2), 0, amp2);
	var p2 = Select.ar( w2, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones2/12)), mul: w2*a2)]);

	var w3 = ceil(thresh(amp ,amp_threshold3));
	var a3 = Clip.ar((amp3*(amp-amp_threshold3))/(ampmax3-amp_threshold3), 0, amp3);
	var p3 = Select.ar( w3, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones3/12)), mul: w3*a3)]);

	var w4 = ceil(thresh(amp ,amp_threshold4));
	var a4 = Clip.ar((amp4*(amp-amp_threshold4))/(ampmax4-amp_threshold4), 0, amp4);
	var p4 = Select.ar( w4, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones4/12)), mul: w4*a4)]);

	var w5 = ceil(thresh(amp ,amp_threshold5));
	var a5 = Clip.ar((amp5*(amp-amp_threshold5))/(ampmax5-amp_threshold5), 0, amp5);
	var p5 = Select.ar( w5, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones5/12)), mul: w5*a5)]);

	var w6 = ceil(thresh(amp ,amp_threshold6));
	var a6 = Clip.ar((amp6*(amp-amp_threshold6))/(ampmax6-amp_threshold6), 0, amp6);
	var p6 = Select.ar( w6, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones6/12)), mul: w6*a6)]);

	var w7 = ceil(thresh(amp ,amp_threshold7));
	var a7 = Clip.ar((amp7*(amp-amp_threshold7))/(ampmax7-amp_threshold7), 0, amp7);
	var p7 = Select.ar( w7, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones7/12)), mul: w7*a7)]);

	Out.ar(outbus,(in+p1+p2+p3+p4+p5+p6+p7)/8);
}).add;


SynthDef.new(\eff_harmonizer_8, {
	arg inbus=8, outbus=0,
	    amp_attack=0.02, amp_release=0.5,
	   // int,     0 do 1     0 do 1      0 do 1
	    semitones1, amp1=0, amp_threshold1=0.06, ampmax1=0.09,
	    semitones2, amp2=0, amp_threshold2, ampmax2,
	    semitones3, amp3=0, amp_threshold3, ampmax3,
	    semitones4, amp4=0, amp_threshold4, ampmax4,
	    semitones5, amp5=0, amp_threshold5, ampmax5,
	    semitones6, amp6=0, amp_threshold6, ampmax6,
	    semitones7, amp7=0, amp_threshold7, ampmax7,
	    semitones8, amp8=0, amp_threshold8, ampmax8;
	var in = In.ar(inbus,1);
	var res = in;
	var amp = Amplitude.ar(in, amp_attack,amp_release);
	var w1 = ceil(thresh(amp ,amp_threshold1));
	var a1 = Clip.ar((amp1*(amp-amp_threshold1))/(ampmax1-amp_threshold1), 0, amp1);
	var p1 = Select.ar( w1, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones1/12)), mul: w1*a1)]);

	var w2 = ceil(thresh(amp ,amp_threshold2));
	var a2 = Clip.ar((amp2*(amp-amp_threshold2))/(ampmax2-amp_threshold2), 0, amp2);
	var p2 = Select.ar( w2, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones2/12)), mul: w2*a2)]);

	var w3 = ceil(thresh(amp ,amp_threshold3));
	var a3 = Clip.ar((amp3*(amp-amp_threshold3))/(ampmax3-amp_threshold3), 0, amp3);
	var p3 = Select.ar( w3, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones3/12)), mul: w3*a3)]);

	var w4 = ceil(thresh(amp ,amp_threshold4));
	var a4 = Clip.ar((amp4*(amp-amp_threshold4))/(ampmax4-amp_threshold4), 0, amp4);
	var p4 = Select.ar( w4, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones4/12)), mul: w4*a4)]);

	var w5 = ceil(thresh(amp ,amp_threshold5));
	var a5 = Clip.ar((amp5*(amp-amp_threshold5))/(ampmax5-amp_threshold5), 0, amp5);
	var p5 = Select.ar( w5, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones5/12)), mul: w5*a5)]);

	var w6 = ceil(thresh(amp ,amp_threshold6));
	var a6 = Clip.ar((amp6*(amp-amp_threshold6))/(ampmax6-amp_threshold6), 0, amp6);
	var p6 = Select.ar( w6, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones6/12)), mul: w6*a6)]);

	var w7 = ceil(thresh(amp ,amp_threshold7));
	var a7 = Clip.ar((amp7*(amp-amp_threshold7))/(ampmax7-amp_threshold7), 0, amp7);
	var p7 = Select.ar( w7, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones7/12)), mul: w7*a7)]);

	var w8 = ceil(thresh(amp ,amp_threshold8));
	var a8 = Clip.ar((amp8*(amp-amp_threshold8))/(ampmax8-amp_threshold8), 0, amp8);
	var p8 = Select.ar( w8, [DC.ar(0), PitchShift.ar(in, 0.2,(pow(2,semitones8/12)), mul: w8*a8)]);

	Out.ar(outbus,(in+p1+p2+p3+p4+p5+p6+p7+p8)/8);
}).add;


/*
//TESTS
b = Buffer.read(s, ~p +/+ "D-DUR.aiff");


s.prepareForRecord(~p +/+ "d-dur-harmonizer.aiff");
s.record;

x = Synth.new(\eff_harmonizer_5,
	[\inbus, 16, \outbus, 0,
		\semitones1, -4, \amp1, 0.6, \amp_threshold1, 0.08, \ampmax1, 0.11,
		\semitones2, -9, \amp2, 0.6, \amp_threshold2, 0.09, \ampmax2, 0.12,
		\semitones3, -14, \amp3, 0.6, \amp_threshold3, 0.1, \ampmax3, 0.13,
		\semitones4, -19, \amp4, 0.6, \amp_threshold4, 0.11, \ampmax4, 0.14,
		\semitones5, 7, \amp5, 0, \amp_threshold5, 0.2, \ampmax5, 0.25,
]);
Synth.new(\eff_playbuf, [\outbus, 16, \bufnum, 14]);


s.stopRecording;


s.prepareForRecord(~p +/+ "harmonizer2.aiff");
s.record;

x = Synth.new(\eff_harmonizer_5,
	[\inbus, 16, \outbus, 0,
		\semitones1, 3, \amp1, 0.1, \amp_threshold1, 0.07, \ampmax1, 0.15,
		\semitones2, 7, \amp2, 0.9, \amp_threshold2, 0.13, \ampmax2, 0.18,
//		\semitones3, 19, \amp3, 0.3, \amp_threshold3, 0.17, \ampmax3, 0.21,
//		\semitones4, -5, \amp4, 0.3, \amp_threshold4, 0.18, \ampmax4, 0.2,
//		\semitones5, 0.01, \amp5, 0.1, \amp_threshold5, 0.2, \ampmax5, 0.22,
]);
Synth.new(\eff_playbuf, [\outbus, 16, \bufnum, 6]);


b = Buffer.read(s, ~p +/+ "zBrody1.wav");

x = Synth.new(\eff_harmonizer_4, [\inbus, 17, \outbus, 0]);
z = Synth.new(\eff_playbuf, [\outbus, 17, \bufnum, 0]);

//TODO: Pitch shifter na delayach!
*/