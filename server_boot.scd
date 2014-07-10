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

OSCdef.new(
	\app_reboot,
	{
		arg msq, time, addr, recvPort;
		s.reboot;
		~e=Dictionary.new(0);
	},
	'/app_reboot'
);
OSCdef.new(
	\app_list_effects,
	{
		arg msg, time, addr, recvPort;
		var d = List.newClear;
		var name;
		SynthDescLib.global.synthDescs.do{ |desc|
			if(desc.def.notNil) {
				name = desc.name.asString;
				//"\n SynthDef %\n".postf(name);
				if(name.beginsWith("eff_"),{d.add(name.postln)},{});
				//desc.def.func.postcs;
			};
		};
		~app_netaddr.sendMsg('\effects_count', d.size.asInteger.postln);
		d.do{ arg it, i;
			~app_netaddr.sendMsg('\effect', it);
		}
	},
	'\app_list_effects'
);

OSCdef.new(
	\new_effect,
	{
		arg msg, time, addr, recvPort;
		var args;
		if((msg.size > 1),{
			args = msg[1].split($ );
			//TEST - pucić jutro!
			//args = "aaa eff_brassage \inbus 8 \outbus 0\eff_brassage".split($ );
			if(args>4) {
				~e.put( args[0] -> Synth.new("\\"++args[1], args.copyRange(2,args.size-1)));
			};
		},{
			"Wrong params:".postln;
			msg.postln;
		});
	},
	'\new_effect'
);
