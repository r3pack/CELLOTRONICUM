~p = thisProcess.nowExecutingPath.dirname;
~q = "C:\\Users\\praktykant\\AppData\\Local\\SuperCollider\\Extensions\\SC3plugins\\PitchDetection\\extraqitchfiles";
~quitch_filename = (~q +/+ "QspeckernN4096SR44100.wav");
// ~quitch_buffer - after server boot contains buffered file for Qitch pitch detector

//DO TESTÓW - najpierw uruchom server!!!
~b = Dictionary.new(0); //buffers
~quitch_buffer = Buffer.read(s, ~quitch_filename); // może nie zadziałać bez włączonego servera - poprawki jutro!
~b.add( ~quitch_buffer.bufnum -> ~quitch_buffer);


s.options.numAudioBusChannels=512;

(~p +/+"server_boot.scd").loadPaths;
(~p +/+"brassage.scd").loadPaths;
(~p +/+"echo.scd").loadPaths;
(~p +/+"bit_crush.scd").loadPaths;
(~p +/+"sound_sources.scd").loadPaths;
(~p +/+"harmonizer.scd").loadPaths;
(~p +/+"base.scd").loadPaths;

/*
s.plotTree;
s.meter;
s.options.numChannels;
s.freqscope;

SynthDef.all;

WAŻNE: Zrobić jeszcze jeden poziom ładowania plików - inicjalizowane po uruchomieniu servera i załadowaniu bufora do quitcha!

Zrobić pitch shift ze zmianą szybkosci odtwarzania

WAŻNE: nagrywanie do buffora

przy bootowaniu servera ustawić, żeby zawsze wysyłało jakis komunikat do aplikacji, zeby odswieżyć Ugeny!!!

czy da się z poziomu sc-lang robić sprawdzanie, czy działa server super collidera? Jakis ping-pong?

TODO: wystawić gain z clippingiem!!!

Quarks.gui

//jeden klocek - gertzel z sinusem: parametry: amp freq

selector - jeden sygnał z 2, 3, 4, 5?

FFT - wycinanie najniższych składowych
jakies przekształcenie sparametryzowane matematycznie
pomysł - ograniczanie iloci skłądowych

IFWT - hadamard w jedną stronę

*/


