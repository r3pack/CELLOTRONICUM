// PITCH SHIFT

SynthDef.new(\eff_pitchshift, {
	arg inbus=8, outbus=0, semitones=0, window_size=0.2;
	var in = In.ar(inbus,1);
	var res = PitchShift.ar(in,window_size,semitones*pow(2,1/12));
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_rand_pitchshift, {
	arg inbus=8, outbus=0, freq=2;
	var in = In.ar(inbus,1);
	var trig = Impulse.kr(freq);
	var pp = 1/2;
	var index = TWindex.kr(trig,[pp, pp]);
	var selection = Select.kr(index, [5,7]); //do interwałów konsonansowych niedoskonałych potrzebny jest chyba pitch detector
	var res = PitchShift.ar(in,0.2,(selection*pow(2,1/12)));
	var resfreq = Tartini.kr(res).poll();
	Out.ar(outbus,res*SinOsc.ar(resfreq*0.5)+in);
}).add;

SynthDef.new(\eff_rand_pitchshift2, {
	arg inbus=8, outbus=0, freq=2;
	var in = In.ar(inbus,1);
	var trig = Impulse.kr(freq);
	var pp = 1/2;
	var index = TWindex.kr(trig,[pp, pp]);
	var selection = Select.kr(index, [5,7,12]); //do interwałów konsonansowych niedoskonałych potrzebny jest chyba pitch detector
	var res = PitchShift.ar(in,0.2,(selection*pow(2,1/12)));
	Out.ar(outbus,res+in);
}).add;


SynthDef.new(\eff_harmonizer_4, {
	arg inbus=8, outbus=0,
	    amp_attack=0.02, amp_release=0.5,
	   // int,     0 do 1     0 do 1      0 do 1
	    semitones1, amp1=0, amp_threshold1=0.06, ampmax1=0.09,
	    semitones2, amp2=0, amp_threshold2, ampmax2,
	    semitones3, amp3=0, amp_threshold3, ampmax3,
	    semitones4, amp4=0, amp_threshold4, ampmax4;
	var in = In.ar(inbus,1);
	var res = in;
	var amp = Amplitude.ar(in, amp_attack,amp_release);
	var w1 = ceil(thresh(amp ,amp_threshold1));
	var a1 = Clip.ar((amp1*(amp-amp_threshold1))/(ampmax1-amp_threshold1), 0, amp1);
	var p1 = Select.ar( w1, [DC.ar(0), PitchShift.ar(in, 0.2,(semitones1*pow(2,1/12)), mul: w1*a1)]);

	var w2 = ceil(thresh(amp ,amp_threshold2));
	var a2 = Clip.ar((amp2*(amp-amp_threshold2))/(ampmax2-amp_threshold2), 0, amp2);
	var p2 = Select.ar( w2, [DC.ar(0), PitchShift.ar(in, 0.2,(semitones2*pow(2,1/12)), mul: w2*a2)]);

	var w3 = ceil(thresh(amp ,amp_threshold3));
	var a3 = Clip.ar((amp3*(amp-amp_threshold3))/(ampmax3-amp_threshold3), 0, amp3);
	var p3 = Select.ar( w3, [DC.ar(0), PitchShift.ar(in, 0.2,(semitones3*pow(2,1/12)), mul: w3*a3)]);

	var w4 = ceil(thresh(amp ,amp_threshold4));
	var a4 = Clip.ar((amp4*(amp-amp_threshold4))/(ampmax4-amp_threshold4), 0, amp4);
	var p4 = Select.ar( w1, [DC.ar(0), PitchShift.ar(in, 0.2,(semitones4*pow(2,1/12)), mul: w4*a4)]);
	Out.ar(outbus,(in+p1+p2+p3+p4)/5);
}).add;

b = Buffer.read(s, ~p +/+ "zBrody1.wav");

x = Synth.new(\eff_harmonizer_4, [\inbus, 17, \outbus, 0]);
z = Synth.new(\eff_playbuf, [\outbus, 17, \bufnum, 0]);

//TODO: Pitch shifter na delayach!

/*/ TESTS
b = Buffer.read(s, ~p +/+ "zBrody1.wav");
b.bufnum.postln;
b = Buffer.read(s, ~p +/+ "G-DUR.aiff");

s.prepareForRecord(~p +/+ "rand_pitchshift2.aiff");
s.record;

x = Synth.new(\eff_rand_pitchshift, [\inbus, 17, \outbus, 0]);
z = Synth.new(\eff_playbuf, [\outbus, 17, \bufnum, 1]);

//z = Synth.new(\eff_playbuf, [\outbus, 1, \bufnum, 0]);

x.set(\freq, 5);

s.stopRecording;

x = Synth.new(\eff_rand_pitchshift, [\inbus, 8, \outbus, 0]);
*/

//FREQ SHIFT
SynthDef.new(\eff_freqshift, {
	arg inbus=8, outbus=0, freq=10;
	var in = In.ar(inbus,1);
	var res = FreqShift.ar(in, freq);
	Out.ar(outbus,res);
}).add;

SynthDef.new(\eff_freq_shift, {
	arg inbus=8, outbus=0, freq_bus;
	var in = In.ar(inbus,1);
	var freq = In.kr(freq_bus,1);
	var res = FreqShift.ar(in, freq);
	Out.ar(outbus,res);
}).add;

////DIST ECHO
SynthDef.new(\eff_distecho, {
	arg inbus=8, outbus=0, amp=0.5, delay=0.5, decay=0.5;
	var in = In.ar(inbus,1);
	var pom = in/(in.abs+1);
	var delayed = CombC.ar(pom,delay,delay,decay,1,in);
	Out.ar(outbus,delayed);
}).add;

/*/TESTS
x = Synth.new(\eff_distecho, [\inbus, 8, \outbus, 0, \amp, 1.0, \delay, 0.5, \decay, 2]);

x.set(\delay,0.04);
x.set(\freq,200);
*/

//SHIFT ECHO (działa)
SynthDef.new(\eff_shiftecho, {
	arg inbus=8, outbus=0, freq=1, phase=0, delay=0.5, decay=0.5;
	var in = In.ar(inbus,1);
	var pom = FreqShift.ar(in,freq,phase);
	var delayed = CombC.ar(pom,delay,delay,decay,1,in);
	Out.ar(outbus,delayed);
}).add;

/*/TESTS
x = Synth.new(\eff_shiftecho, [\inbus, 8, \outbus, 0, \delay, 0.5, \decay, 0.9, \freq, 10]);
*/

//rmdelay
SynthDef.new(\eff_rmdelay, {
	arg inbus=8, outbus=0, delay=0.5;
	var in = In.ar(inbus,1);
	var delayed = in*DelayC.ar(in,delay,delay,1,in);
	Out.ar(outbus,delayed);
}).add;

/*/TESTS
x = Synth.new(\eff_rmdelay, [\inbus, 8, \outbus, 0, \delay, 0.0, \freq, 10]);
*/

SynthDef.new(\eff_rmdelayrec, {
	arg inbus=8, outbus=0, delay=0.5;
	var in = In.ar(inbus,1);
	var del = ((in+1)/2)*delay;
	var delayed = in*DelayC.ar(in,del,del,1,in);
	Out.ar(outbus,delayed);
}).add;

/*/TESTS
x = Synth.new(\eff_rmdelayrec, [\inbus, 8, \outbus, 0, \delay, 0.5]);
*/

//rmchorus
SynthDef.new(\eff_rmchorus, {
	arg inbus=8, outbus=0, freq=1, delay=0.5;
	var in = In.ar(inbus,1);
	var os = (SinOsc.kr(freq)+1)*delay;
	var delayed = in*DelayC.ar(in,os,os,1,in);
	Out.ar(outbus,delayed);
}).add;

/*/TESTS
x = Synth.new(\eff_rmchorus, [\inbus, 8, \outbus, 0, \delay, 0.0, \freq, 10]);
*/

SynthDef.new(\eff_rmchorus2, {
	arg inbus=8, outbus=0, delay=0.5;
	var in = In.ar(inbus,1);
	var os = (SinOsc.kr(Tartini.kr(in))+1)*delay/2;
	var delayed = in*DelayC.ar(in,os,os,1,in);
	Out.ar(outbus,delayed);
}).add;

/*/TESTS
x = Synth.new(\eff_rmchorus2, [\inbus, 8, \outbus, 0, \delay, 0.5]);
*/

//ECHO WITH CUSTOMIZED FEEDBACK?
SynthDef.new(\eff_genecho, {
	arg inbus=8, outbus=0, feedback_input=99, feedback_output=99, delay=0, decay=0; //.zobaczyć, czy ten feedback output jest potrzebny!
	var input = In.ar(inbus,1)+InFeedback.ar(feedback_input);
	OffsetOut.ar(feedback_output, DelayC.ar(decay*input, delay, delay - ControlRate.ir.reciprocal)); // subtract block size
	Out.ar(outbus,input);
}).add;

//Wypasione ECHO!
/*
SynthDef.new(\eff_genecho, {
	arg inbus=8, outbus=0, delay_bus, feedback_input=99, feedback_output=99, decay=0; //.zobaczyć, czy ten feedback output jest potrzebny!
	var input = In.ar(inbus,1)+InFeedback.ar(feedback_input);
	OffsetOut.ar(feedback_output, DelayC.ar(decay*input, delay, delay - ControlRate.ir.reciprocal)); // subtract block size
	Out.ar(outbus,input);
}).add;
*/

/*/TEST
x = Synth.new(\eff_genecho, [\inbus, 8, \outbus, 0, \delay, 0.5, \decay, 0.7]);
*/

//wsdistortion
SynthDef.new(\eff_wsdistortion, {
	arg inbus=8, outbus=0, gain=2;
	var in = In.ar(inbus,1)*gain;
	var res = pow(in,7)+pow(in,3);
	Out.ar(outbus,res);
}).add;

/*/TEST
x = Synth.new(\eff_wsdistortion, [\inbus, 8, \outbus, 0, \gain, 2]);
*/

//wsdistortionwetDry
SynthDef.new(\eff_wsdistortionwetDry, {
	arg inbus=8, outbus=0, gain=2, freq, sin_amp=1, noise_amp=1, const_amp=0;
	var in = In.ar(inbus,1)*gain;
	var ing = In.ar(inbus,1)*gain;
	var sth = min((((SinOsc.ar(freq)+1)/2)*sin_amp)+((WhiteNoise.ar()+1)/2*noise_amp)+const_amp, 1);
	var res = (pow(ing,7)+pow(ing,3)*sth) + ((sth-1)*(-1)*in);
	Out.ar(outbus,res);
}).add; //TODO: Equalization

/*/TEST
x = Synth.new(\eff_wsdistortionwetDry, [\inbus, 8, \outbus, 0, \gain, 2, \freq, 5, \sin_amp, 1, \noise_amp, 1, \const_amp, 0]);
*/

SynthDef.new(\gramophone, {
	arg inbus=8, outbus=0, noise_amp = 0.2, rq=1, freq=1000, imp_freq=5, blip_freq=3, gain = 2;
	var input = gain* In.ar(inbus,1);
	var filtered = BBandPass.ar(WhiteNoise.ar(noise_amp/300),freq,rq);
	var sig = Impulse.kr(imp_freq,0,WhiteNoise.kr(noise_amp)) + Impulse.kr(imp_freq/2,0.1,WhiteNoise.kr(noise_amp)) + Impulse.kr(imp_freq/3,0.1,WhiteNoise.kr(noise_amp/2));
	var impulses = Blip.ar(blip_freq,300,sig*2);
	var res = input/(input.abs+1);
	var noises = (0.98*impulses) + filtered  + GrayNoise.ar(noise_amp/100) + WhiteNoise.ar(noise_amp/1000);
	var filtr = MidEQ.ar(res,750,1,0.9);
	var mid = BLowPass.ar(BHiPass.ar(filtr,168,0.5),2000,0.5);
	var comp = Compander.ar(mid,mid,0.1,2,0.5,0.01,0.02);
	Out.ar(outbus, comp+noises);
}).add;

/* TEST - nagrywanie do pliku

SynthDef(\recordTone, { |buffer|
    RecordBuf.ar(In.ar(0), buffer, loop: 0, doneAction: 2);
}).add;

b = Buffer.read(s, ~p +/+ "zBrody4.wav");
b.bufnum.postln;
Routine({
    var recordfn =
	 {  var server = Server.local;
		var buffer = Buffer.alloc(s, b.numFrames, b.numChannels,2);
        server.sync;
        server.makeBundle(func: {
			var recorder = Synth.tail(s, \recordTone, [\buffer, buffer]);
            var x = Synth.new(\gramophone, [\inbus, 16, \outbus, 0, \noise_amp, 1.0]);
			var y = Synth.new(\eff_playbuf, [\outbus, 16, \bufnum, 5]);
        });
        (b.numFrames/s.sampleRate).wait;
        buffer.write( ~p +/+ "test1.wav", "WAVE", "int16", completionMessage: ["/b_free", buffer]);
    };
    recordfn.value;
}).next;

//TEST 2 - nagrywanie w locie
b = Buffer.read(s, ~p +/+ "zBrody4.wav");
b.bufnum.postln;
a = Buffer.alloc(s, b.numFrames, b.numChannels,2);
Synth.new(\gramophone, [\inbus, 16, \outbus, 0, \noise_amp, 1.0]);
Synth.new(\eff_playbuf, [\outbus, 16, \bufnum, 5]);
Synth.tail(s, \recordTone, [\buffer, a]);

a.write( ~p +/+ "test1.wav", "WAVE", "int16", completionMessage: ["/b_free", a]);

//TEST 3 - nagrywanie przez server
s.prepareForRecord(~p +/+ "server_record.aiff");

Synth.new(\gramophone, [\inbus, 16, \outbus, 0, \noise_amp, 1.0]);
Synth.new(\eff_playbuf, [\outbus, 16, \bufnum, 5]);
s.record;

s.stopRecording;
//jest jeszze s.pauseRecording
*/
/*//TEST
/*
x = Synth.new(\gramophone, [\inbus, 8, \outbus, 0, \noise_amp, 0.8]);
x.set(\noise_amp, 0.5);
x.set(\imp_freq, 5);
x.set(\blip_freq, 3);
x.set(\gain, 2);
x.set(\freq,1200);*/
*/
