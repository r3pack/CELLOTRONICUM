~p = thisProcess.nowExecutingPath.dirname;
~q = Platform.userExtensionDir +/+ "SC3plugins\\PitchDetection\\extraqitchfiles";
~qitch_filename = (~q +/+ "QspeckernN4096SR44100.wav");
// ~qitch_buffer - after server boot contains buffered file for Qitch pitch detector

//DO TESTÓW - najpierw uruchom server!!!
~b = Dictionary.new(0); //buffers
~qitch_buffer = Buffer.read(s, ~qitch_filename); // może nie zadziałać bez włączonego servera - poprawki jutro!
~b.add( ~qitch_buffer.bufnum -> ~qitch_buffer);


s.options.numAudioBusChannels=512;
(~p +/+"server_boot.scd").loadPaths;

/*
s.plotTree;
s.meter;
s.freqscope;

s.options.numChannels;


SynthDef.all;

Zrobić pitch shift ze zmianą szybkosci odtwarzania

WAŻNE: nagrywanie do buffora

czy da się z poziomu sc-lang robić sprawdzanie, czy działa server super collidera? Jakis ping-pong?

Quarks.gui

FFT - wycinanie najniższych składowych
jakies przekształcenie sparametryzowane matematycznie
pomysł - ograniczanie iloci skłądowych

IFWT - hadamard w jedną stronę

TODO: http://chrisjeffs.com/blog/?p=750
http://permalink.gmane.org/gmane.comp.audio.supercollider.user/87244
http://danielnouri.org/docs/SuperColliderHelp/Collections/Wavetable.html

*/


