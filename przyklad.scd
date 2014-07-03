
b = Buffer.read(s, "C:\\Users\\praktykant\\kotek.wav"); //ładujemy kotka



(// przykładowy synthDef odtwarzający podany w argumencie bufor z fajnym efektem
SynthDef(\tutorial,{ arg out = 0, which=20, bufnum;
	Out.ar( out,
		WalshHadamard.ar((PlayBuf.ar(2, bufnum, BufRateScale.kr(bufnum))),which)
	)
}).add;

);


x = Synth.new(\tutorial, [\bufnum, b.bufnum ]); //tworzymy synth-a z buforem z kotem

x.set(\which,5); //zmieniamy wartosc efektu

