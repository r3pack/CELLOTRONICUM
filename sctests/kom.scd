
OSCdef.new(
	\toggle,
	{
		arg msg, time, addr, recvPort;
		[msg, time, addr, recvPort].postln;
		~x.set(\freq, msg[1]);
	},
	'/ping',
);

Server

OSCdef.new(
	\toggle,
	{
		arg msg, time, addr, recvPort;
		var re = NetAddr.new(addr, recvPort);
		[msg, time, addr, recvPort].postln;
		//~x.set(\freq, msg[1]);
		s.boot(recover:true); //onFailure:func_onFailure report sender!
		//zamiast tego:
		//s.waitForBoot(func_główna_pętla, inf, func_onFailure)
		re.sendMsg('\status', s.status);
		re.sendMsg('\status', [s.status, s.sampleRate, s.numSynths]);
		//re.sendMsg(
	},
	'/start',
);


NetAddr.langPort; //odbierający

SynthDef(\biip,
	{
		arg freq=60, nharm=12, detune =0.2, gate=0,
		pan =0, amp=0.5, out=0;
		var sig, env;
		env = EnvGen.kr(Env.adsr(0.05,0.1,0.5,3), gate);
		sig = Blip.ar( freq, nharm);
		sig = Splay.ar(sig);
		sig = Balance2.ar(sig[0], sig[1], pan);
		sig = sig*env*amp;
		Out.ar(out,sig);
	}
).add;

{Blip.ar(200,0,0.5)}.play;

~x = Synth.new(\biip, [\gate,1]);