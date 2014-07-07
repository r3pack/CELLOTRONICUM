//~app_netaddr;

var func_onFailure = {
	'Bum!'.postln;
};


var func_main_loop = {
	~app_netaddr.sendMsg('\status_ok', s.pid.asInteger);
};

OSCdef.new(
	\app_start,
	{
		arg msg, time, addr, recvPort;
		[msg, time, addr, recvPort].postln;
		//~x.set(\freq, msg[1]);
		~app_netaddr = addr;
		//s.boot(recover:true); //onFailure:func_onFailure report sender!
		//zamiast tego:
		s.waitForBoot(func_main_loop, inf, func_onFailure);
		//re.sendMsg('\status', s.status);
		//re.sendMsg('\status', [s.status, s.sampleRate, s.numSynths]);
	},
	'/app_start'
);