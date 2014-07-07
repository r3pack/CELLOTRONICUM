//~app_netaddr;

var func_onFailure = {
	'Bum!'.postln;
};

var func_start = {
	~app_netaddr.sendMsg('\status_ok', s.pid.asInteger);
	//INITIALISATION CODE HERE:

};

OSCdef.new(
	\app_start,
	{
		arg msg, time, addr, recvPort;
		[msg, time, addr, recvPort].postln;
		~app_netaddr = addr;
		s.waitForBoot(func_start, inf, func_onFailure);
	},
	'/app_start'
);

OSCdef.new(
	\app_quit,
	{
		arg msg, time, addr, recvPort;
		[msg, time, addr, recvPort].postln;
		s.quit;
		'Server killed.'.postln;
	},
	'/app_quit'
);

OSCdef.all;