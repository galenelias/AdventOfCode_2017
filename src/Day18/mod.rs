use std::io::{self, BufRead};
use std::collections::HashMap;
use std::collections::VecDeque;

struct Cpu {
	registers : HashMap<String,i64>,
	input_queue : VecDeque<i64>,
	output_queue : Vec<i64>,
	pc : usize, // program counter
	send_count : usize,
	part1_behavior : bool,
	part1_last_received : i64,
}

impl Cpu {
	fn new(id: i64, part1_behavior : bool) -> Cpu {
		let mut cpu = Cpu {
			registers : HashMap::new(),
			input_queue : VecDeque::new(),
			output_queue : Vec::new(),
			pc : 0,
			send_count : 0,
			part1_behavior : part1_behavior,
			part1_last_received : 0,
		};
		cpu.registers.insert(String::from("p"), id);
		return cpu;
	}

	// Get the value based on a string.  Either an immediate (number) or the name of a register
	fn get_value(&self, param : &str) -> i64 {
		match param.parse::<i64>() {
			Ok(val) => val,
			Err(_) => *self.registers.get(param).unwrap_or(&0),
		}
	}

	// Returns true if progress was made.  False if the cpu is either blocked on input or at the end of the program
	fn run_one_instruction(&mut self, program : &Vec<String>) -> bool {
		if self.pc >= program.len() {
			return false;
		}

		let op : Vec<_> = program[self.pc].split(' ').map(String::from).collect();
		match op[0].as_ref() {
			"set" => (*self.registers.entry(op[1].clone()).or_insert(0)) = self.get_value(&op[2]),
			"add" => (*self.registers.entry(op[1].clone()).or_insert(0)) += self.get_value(&op[2]),
			"mul" => (*self.registers.entry(op[1].clone()).or_insert(0)) *= self.get_value(&op[2]),
			"mod" => (*self.registers.entry(op[1].clone()).or_insert(0)) %= self.get_value(&op[2]),
			"jgz" => if self.get_value(&op[1]) > 0 { self.pc = (self.pc as i64 + self.get_value(&op[2]) - 1) as usize; }, // -1 to cancel out the automatic pc increment
			"snd" => {
				let val = self.get_value(&op[1]);
				self.output_queue.push(val);
				self.send_count += 1;
			}
			"rcv" => {
				if self.part1_behavior {
					if self.get_value(&op[1]) != 0 {
						self.part1_last_received = *self.input_queue.back().unwrap_or(&0);
						return false;
					}
				} else {
					if self.input_queue.is_empty() {
						return false;
					} else {
						(*self.registers.entry(op[1].clone()).or_insert(0)) = self.input_queue.pop_front().unwrap();
					}
				}
			}
			_ => panic!("Unexpected instruction {}", op[0]),
		}

		self.pc += 1;
		true
	}
}

fn part1(program : &Vec<String>) {
	let mut cpu = Cpu::new(0, true /*part1_behavior*/);
	while cpu.run_one_instruction(&program) {
		// Loop the send commands back into the input queue
		cpu.input_queue.extend(cpu.output_queue.drain(..));
	}
	println!("Part 1: {}", cpu.part1_last_received);
}

fn part2(program : &Vec<String>) {
	let mut cpu0 = Cpu::new(0, false /*part1_behavior*/);
	let mut cpu1 = Cpu::new(1, false /*part1_behavior*/);

	while cpu0.run_one_instruction(&program) || cpu1.run_one_instruction(&program) {
		// Exchange input/output
		cpu0.input_queue.extend(cpu1.output_queue.drain(..));
		cpu1.input_queue.extend(cpu0.output_queue.drain(..));
	}

	println!("Part 2: {}", cpu1.send_count);
}

pub fn solve() {
	println!("Enter input:");
	let stdin = io::stdin();
	let program: Vec<String> = stdin.lock().lines()
		.filter_map(|l| l.ok())
		.collect();

	part1(&program);
	part2(&program);
}