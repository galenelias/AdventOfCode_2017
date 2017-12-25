use std::io::{self, BufRead};
use std::collections::HashMap;
use regex::Regex;

struct StateRule {
	value : i32,
	move_offset : i32,
	next_state : String,
}

impl StateRule {
	fn default() -> StateRule {
		StateRule {
			value: 0,
			move_offset: 0,
			next_state: String::from(""),
		}
	}
}

pub fn solve() {
	println!("Enter input:");
	let stdin = io::stdin();
	let inputs: Vec<_> = stdin.lock().lines()
		.filter_map(|l| l.ok())
		.collect();

	let re_state = Regex::new(r"state (.)").unwrap();
	let re_diag = Regex::new(r"checksum after (\d+) steps.").unwrap();
	let re_number = Regex::new("[[:digit:]]+").unwrap();

	let start_state = &re_state.captures(&inputs[0]).unwrap()[1];
	let checksum_trigger = re_diag.captures(&inputs[1]).unwrap()[1].parse::<i32>().unwrap();

	let mut state_rules : HashMap<String, [StateRule; 2]> = HashMap::new();
	let mut i = 3;
	while i < inputs.len() {
		let mut subrules = [StateRule::default(), StateRule::default()];
		let cur_state = re_state.captures(&inputs[i]).unwrap()[1].to_string();

		for r in 0..2 {
			subrules[r].value = re_number.find(&inputs[i+r*4+2]).unwrap().as_str().parse::<i32>().unwrap();
			subrules[r].move_offset = match inputs[i+r*4+3].split_whitespace().last().unwrap() {
				"left." => -1,
				"right." => 1,
				_ => panic!("Bad move direction"),
			};
			subrules[r].next_state = re_state.captures(&inputs[i+r*4+4]).unwrap()[1].to_string();
		}

		state_rules.insert(cur_state, subrules);
		i += 10;
	}

	let mut tape : HashMap<i32, i32> = HashMap::new();
	let mut pos = 0;
	let mut state : String = start_state.to_string();

	for _ in 0..checksum_trigger {
		let val = tape.entry(pos).or_insert(0);
		let rule = &state_rules.get(&state).unwrap()[*val as usize];
		*val = rule.value;
		pos += rule.move_offset;
		state = rule.next_state.clone();
	}

	println!("Part 1: {}", tape.iter().map(|(_k,v)| v).sum::<i32>());
}
