
b = Buffer.read(s, "C:\\Users\\praktykant\\zBrody1.wav");

(


SynthDef("buffer", { arg out=0,  bufnum;
	var buf=PlayBuf.ar(1, bufnum, BufRateScale.kr(bufnum));

	Out.ar( out, buf);
}).add;



SynthDef("sinefreq", { arg out=0,  bufnum;
	var in=PlayBuf.ar(1, bufnum, BufRateScale.kr(bufnum));

	var sine= SinOsc.ar(Pitch.kr(in));

	Out.ar( out, sine);
}).add;
)

SynthDef("fm1", { arg bufnum, bus = 0, freq = 440, carPartial = 1, modPartial = 1, index = 3, mul = 0.05;

    // index values usually are between 0 and 24
    // carPartial :: modPartial => car/mod ratio

    var mod;
    var car;

	var in=PlayBuf.ar(1, bufnum, BufRateScale.kr(bufnum));

    mod = SinOsc.ar(
        freq * modPartial,
        0,
        freq * index // * LFNoise1.kr(5.reciprocal).abs
    );

    car = SinOsc.ar(
        (freq * carPartial) + mod,
        0,
        mul
    );

    Out.ar(
        bus,
        car
    )
}).add;
)

{SinOsc.ar(440)}.play;

Synth("sinefreq", [\out, 0, \bufnum, b.bufnum]);

Synth("buffer", [\out, 17, \bufnum, b.bufnum]);


Synth("fm1", [\bus, 0, \freq, 440, \carPartial, 1, \modPartial, 2.4]);



Synth("fm1", [\bus, 1, \freq, 442, \carPartial, 1, \modPartial, 2.401]);


(
s.queryAllNodes;
)