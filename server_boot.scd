//~app_netaddr;

var func_onFailure = {
	'Bum!'.postln;
};

var func_start = {
	~app_netaddr.sendMsg('\status_ok', s.pid.asInteger);
	//INITIALISATION CODE HERE:
	~e = Dictionary.new(0); //synths on server
	~b = Dictionary.new(0); //buffers
	~bus = Dictionary.new(0); //busses
};

OSCdef.new(
	\app_start,
	{
		arg msg, time, addr, recvPort;
		[msg, time, addr, recvPort].postln;
		~app_netaddr = addr;
		s.quit;
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
		~bus.do({
			arg item, i;
			item.free;
		});
		~bus = Dictionary.new(0);
		s.waitForBoot(func_start, inf, func_onFailure);
	},
	'/app_start'
);

s.status.postln;

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
		~bus.do({
			arg item, i;
			item.free;
		});
		~bus = Dictionary.new(0);
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
		~bus=Dictionary.new(0);
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
			msg.copyRange(3,msg.size-1).postln;
			if((~e[msg[1].asString] !== nil),{
				"ERROR: Effect already exist. ".post;
				msg.postln;
			},{
				"NEW SYNTH: ".post;
				msg[2].post;
				" args: ".post;
					~e.add( (msg[1]).asString -> Synth.new(msg[2], (msg.copyRange(3,msg.size-1)).postln));
			});
		},{
			"Wrong params:".postln;
			msg.postln;
		});
	},
	'/new_effect_instance'
);


OSCdef.new(
	\new_effect_instance_paused,
	{
		arg msg, time, addr, recvPort;
		if((msg.size > 1),{
			msg.copyRange(3,msg.size-1).postln;
			if((~e[msg[1].asString] !== nil),{
				"ERROR: Effect already exist. ".post;
				msg.postln;
			},{
				"NEW SYNTH: ".post;
				msg[2].post;
				" args: ".post;
					~e.add( (msg[1]).asString -> Synth.newPaused(msg[2], (msg.copyRange(3,msg.size-1)).postln));
			});
		},{
			"Wrong params:".postln;
			msg.postln;
		});
	},
	'/new_effect_instance_paused'
);

OSCdef.new(
	\unpause_effect_instance,
	{
		arg msg, time, addr, recvPort;
		~e[(msg[1]).asString].run;
	},
	'/unpause_effect_instance'
);


OSCdef.new(
	\pause_effect_instance,
	{
		arg msg, time, addr, recvPort;
		~e[(msg[1]).asString].run(false);
	},
	'/pause_effect_instance'
);

OSCdef.new(
	\move_before_effect_instance,
	{
		arg msg, time, addr, recvPort;
		"MOVE ".post; ~e[msg[1].asString].post; " before ".post; ~e[msg[2].asString].postln;
		~e[(msg[1]).asString].moveBefore(~e[msg[2].asString]);
	},
	'/move_before_effect_instance'
);

OSCdef.new(
	\move_after_effect_instance,
	{
		arg msg, time, addr, recvPort;
		"MOVE ".post; ~e[msg[1].asString].post; " after ".post; ~e[msg[2].asString].postln;
		~e[(msg[1]).asString].moveAfter(~e[msg[2].asString]);
	},
	'/move_after_effect_instance'
);

OSCdef.new(
	\move_to_head,
	{
		arg msg, time, addr, recvPort;
		"MOVE TO HEAD:".post; ~e[msg[1].asString].post;
		~e[(msg[1]).asString].moveToHead(~e[(msg[1]).asString].group);
	},
	'/move_to_head'
);

OSCdef.new(
	\move_to_tail,
	{
		arg msg, time, addr, recvPort;
		"MOVE TO TAIL".post; ~e[msg[1].asString].post;
		~e[(msg[1]).asString].moveToTail(~e[(msg[1]).asString].group);
	},
	'/move_to_tail'
);

OSCdef.new(
	\delete_effect_instance,
	{
		arg msg, time, addr, recvPort;
		~e[msg[1].asString].free;
		~e.removeAt(msg[1].asString);
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
		~bus.add( new_bus.index -> new_bus);
		~app_netaddr.sendMsg('\free_bus', new_bus.index);
	},
	'/get_free_bus'
);

OSCdef.new(
	\delete_bus,
	{
		arg msg, time, addr, recvPort;
		var busindex = msg[1].asInt;
		~bus[busindex].free();
		~bus.removeAt(busindex);
	},
	'/delete_bus'
);

OSCdef.new(
	\set_param,
	{
		arg msg, time, addr, recvPort;
		//if(msg.size = 1) {("Invalid set_param :"++ msg).error;};
		msg.postln;
		~e.[msg[1].asString].set((msg[2]).asSymbol, msg[3]); //TODO: Być może zrobić ustawianie wielu parametrów na raz.
	},
	'/set_param'
);

OSCdef.new(
	\file_to_record,
	{
		arg msg, time, addr, recvPort;
		s.prepareForRecord(~p +/+ msg[1]);
	},
	'/file_to_record'
);

OSCdef.new(
	\start_record,
	{
		arg msg, time, addr, recvPort;
		s.record;
	},
	'/start_record'
);

OSCdef.new(
	\stop_record,
	{
		arg msg, time, addr, recvPort;
		s.stopRecording;
	},
	'/stop_record'
);

OSCdef.new(
	\load_buffer,
	{
		arg msg, time, addr, recvPort;
		var buf;
		(msg[1]).postln;
		buf = Buffer.read(s, msg[1]);
		~b.add( buf.bufnum -> buf);
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
		buf.free();
		~app_netaddr.sendMsg('\buffer_deleted', msg[1]);
	},
	'/delete_buffer'
);


//TODO: /app_all_working_effects //Do debugu
/*
OSCdef.new(
	\app_all_working_effects
);*/

/*
~e.["0"].set(\delay, 0.5);
~e.postln;
~e.["0"].moveBefore(~e["1"]);*/


