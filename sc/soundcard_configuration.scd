// KONFIGURACJA POD KARTĘ MOTU TRAVELER
s.options.device="MOTU Audio ASIO";
s.options.memSize = 4096;
s.options.numOutputBusChannels = 14;
s.options.numInputBusChannels = 14;

//ZWIĘKSZENIE ILOŚCI BUSÓW
s.options.numAudioBusChannels=512;

/*
ServerOptions.inDevices
WAŻNE: http://new-supercollider-mailing-lists-forums-use-these.2681727.n2.nabble.com/Audio-in-with-Soundflower-td6504425.html
http://doc.sccode.org/Classes/ServerOptions.html
*/