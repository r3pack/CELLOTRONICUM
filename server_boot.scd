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
		s.quit;
		'Server killed.'.postln;
	},
	'/app_quit'
);

//TEST EFFECTS
OSCdef.new(
	'\effect_biip',
	{
		arg msg, time, addr, recvPort;
		[msg, time, addr, recvPort].postln;
		(msg.asString++"Biip!").postln;
	},
	'\effect_biip'
);

OSCdef.new(
	'\effect_biiip',
	{
		arg msg, time, addr, recvPort;
		[msg, time, addr, recvPort].postln;
		(msg.asString++"Biiip!").postln;
	},
	'\effect_biiip'
);

OSCdef.new(
	'\effect_biiiip',
	{
		arg msg, time, addr, recvPort;
		[msg, time, addr, recvPort].postln;
		(msg.asString++"Biiiip!").postln;
	},
	'\effect_biiiip'
);

//END OF TEST EFFECTS

OSCdef.new(
	'\app_list_effects',
	{
		arg msg, time, addr, recvPort;
		var d = List.newClear;
		OSCdef.all.keysDo{ |key|
			if(key.asString.beginsWith("effect"), {d.add(key.asString);}, {});
		};
		~app_netaddr.sendMsg('\effects_count', d.size.asInteger);
		d.do{ arg it, i;
			~app_netaddr.sendMsg('\effect', it);
		}
	},
	'\app_list_effects'
);

OSCdef.all;