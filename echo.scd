//DIST ECHO
SynthDef.new(\eff_distecho, {
	arg inbus=8, outbus=0, amp=0.5, delay=0.5, decay=0.5;
	var in = In.ar(inbus,1);
	var pom = in/(abs(in)+1);
	var delayed = CombC.ar(pom,delay,delay,decay,1,in);
	Out.ar(outbus,delayed);
}).add;

//TESTS
x = Synth.new(\eff_distecho, [\inbus, 8, \outbus, 0, \, 1.0, \delay, 0.5, \decay, 0.9]);
x.set(\delay,0.04);
x.set(\freq,200);

//FREQ SHIFT ECHO (not finished)
SynthDef.new(\eff_freqshiftecho, {
	arg inbus=8, outbus=0, amp=0.5, delay=0.5, decay=0.5;
	var in = In.ar(inbus,1);
	var pom = HilbertFIR.ar(in,LocalBuf(2048));
	//zobacz: FreqShift, Hilbert, HilbertFIR
	var delayed = CombC.ar(pom,delay,delay,decay,1,in);
	Out.ar(outbus,delayed);
}).add;
