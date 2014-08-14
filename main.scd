~p = thisProcess.nowExecutingPath.dirname;

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

Zwykły sygnał opóźnić o czas potrzebny do pitch detection.

Zrobić pitch shift ze zmianą szybkosci odtwarzania

*/
