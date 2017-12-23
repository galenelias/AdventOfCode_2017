use std::io::{self, BufRead};
use std::collections::HashMap;

struct Cpu {
	registers : HashMap<String,i64>,
	pc : usize, // program counter
	mul_count : u32,
}

impl Cpu {
	fn new(a : i64) -> Cpu {
		let mut cpu = Cpu {
			registers : HashMap::new(),
			pc : 0,
			mul_count : 0,
		};
		cpu.registers.insert(String::from("a"), a);
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
			"sub" => (*self.registers.entry(op[1].clone()).or_insert(0)) -= self.get_value(&op[2]),
			"mul" => {self.mul_count += 1; (*self.registers.entry(op[1].clone()).or_insert(0)) *= self.get_value(&op[2])},
			"mod" => (*self.registers.entry(op[1].clone()).or_insert(0)) %= self.get_value(&op[2]),
			"jnz" => if self.get_value(&op[1]) != 0 { self.pc = (self.pc as i64 + self.get_value(&op[2]) - 1) as usize; }, // -1 to cancel out the automatic pc increment
			_ => panic!("Unexpected instruction {}", op[0]),
		}

		self.pc += 1;
		true
	}
}

fn part1(program : &Vec<String>) {
	let mut cpu = Cpu::new(0);
	while cpu.run_one_instruction(&program) {
	}

	println!("Part 1: {}", cpu.mul_count);
}

fn part2(program : &Vec<String>) {
	let mut cpu = Cpu::new(1);

	// Run the program for a while to find the initial values of B and C (our start and end loop values)
	for _ in 0..10 {
		cpu.run_one_instruction(&program);
	}

	let start = *cpu.registers.get("b").unwrap();
	let end = *cpu.registers.get("c").unwrap();

	let non_primes = (start..(end+1)).step_by(17).filter(|&n| {
		for i in 2..n {
			if n % i == 0 {
				return true;
			}
		}
		return false;
	}).count();

	println!("Part 2: {}", non_primes);
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
