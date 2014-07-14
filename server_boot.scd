//~app_netaddr;

var func_onFailure = {
	'Bum!'.postln;
};

var func_start = {
	~app_netaddr.sendMsg('\status_ok', s.pid.asInteger);
	//INITIALISATION CODE HERE:
	~e = Dictionary.new(0);
	~b = Dictionary.new(0);
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
		~e.do({
			arg item, i;
			item.postln;
			i.postln;
			item.free;
		});
		~e=Dictionary.new(0);
		~b.do({
			arg item, i;
			item.free;
		});
		~b=Dictionary.new(0);
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
		~b=Dictionary.new(0);
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
				if(name.beginsWith("eff_"),{d.add(name.postln)},{});
			};
		};
		~app_netaddr.sendMsg('\effects_count', d.size.asInteger.postln);
		d.do{ arg it, i;
			~app_netaddr.sendMsg('\effect', it);
		}
	},
	'/app_list_effects'
);

OSCdef.new(
	\new_effect_instance,
	{
		arg msg, time, addr, recvPort;
		if((msg.size > 1),{
			~e.put( msg[1] -> Synth.new(msg[2], msg.copyRange(3,msg.size-1)));
		},{
			"Wrong params:".postln;
			msg.postln;
		});
	},
	'/new_effect_instance'
);

OSCdef.new(
	\delete_effect_instance,
	{
		arg msg, time, addr, recvPort;
		msg.postln;
		~e.removeAt(msg[1]);
	},
	'\delete_effect_instance'
);

OSCdef.new(
	\get_free_bus,
	{
		arg msg, time, addr, recvPort;
		var new_bus;
		"GET FREE BUS".postln;
		if((msg.size>1),{
			new_bus = Bus.audio(s,msg[1]);
		},{ //just one!
			new_bus = Bus.audio(s,1);
		});
		~app_netaddr.sendMsg('\free_bus', new_bus.index);
	},
	'/get_free_bus'
);

OSCdef.new(
	\set_param,
	{
		arg msg, time, addr, recvPort;
		var args, effect;
		if(msg.size = 1) {("Invalid set_param :"++ msg).error;};
		effect = ~e.[msg[1]];
		effect.set(args[2], args[3]); //TODO: Być może zrobić ustawianie wielu parametrów na raz.
	},
	'/set_param'
);

OSCdef.new(
	\load_buffer,
	{
		arg msg, time, addr, recvPort;
		var buf;
		(~p +/+ msg[1]).postln;
		buf = Buffer.read(s, ~p +/+ msg[1]);
		~b.put( buf.bufnum -> buf);
		buf.postln;
		~app_netaddr.sendMsg('\new_buffer', buf.bufnum);
	},
	'/load_buffer'
);

OSCdef.new(
	\delete_buffer,
	{
		arg msg, time, addr, recvPort;
		var buf = ~b.[msg[1]];
		~b.removeAt(msg[1]);
		~app_netaddr.sendMsg('\buffer_deleted', msg[1]);
	},
	'/delete_buffer'
);


//TODO: /app_all_working_effects //Do debugu
/*
OSCdef.new(
	\app_all_working_effects
);*/

