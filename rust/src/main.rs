extern crate ufire_sht20;
extern crate shrust;
use shrust::{Shell, ShellIO};
use std::io::prelude::*;
use ufire_sht20::*;

fn main() {
	println!("Isolated EC Probe Interface shell");
	println!("type `help` for a list of commands");
	let v = vec![0x40];
	let mut shell = Shell::new(v);

	shell.new_command_noargs("t", "Measure temperature", move |io, v| {
		let mut sht20 = SHT20::new("/dev/i2c-3", v[0]).unwrap();
		sht20.begin(::RESOLUTION_12BITS).unwrap();
		try!(writeln!(io, "{}", sht20.temperature().unwrap()));
		Ok(())
	});

	shell.new_command_noargs("h", "Measure humidity", move |io, v| {
		let mut sht20 = SHT20::new("/dev/i2c-3", v[0]).unwrap();
		sht20.begin(::RESOLUTION_12BITS).unwrap();
		try!(writeln!(io, "{}", sht20.humidity().unwrap()));
		Ok(())
	});

    shell.run_loop(&mut ShellIO::default());
}
