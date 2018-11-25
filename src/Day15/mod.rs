use std::io::{self, BufRead};
use regex::Regex;

struct Generator {
	value: u64,
	factor: u64,
}

impl Iterator for Generator {
	type Item = u64;

	fn next(&mut self) -> Option<u64> {
		self.value = (self.value * self.factor) % 2147483647;
		Some(self.value)
	}
}

fn generator_a(seed: u64) -> Generator {
	Generator { value: seed, factor: 16807}
}

fn generator_b(seed: u64) -> Generator {
	Generator { value: seed, factor: 48271}
}

pub fn solve() {
	let re = Regex::new("[[:digit:]]+").unwrap();

	println!("Enter input:");
	let stdin = io::stdin();
	let inputs: Vec<_> = stdin.lock().lines()
		.filter_map(|l| l.ok())
		.map(|l| re.find(&l).unwrap().as_str().parse::<u64>().ok().unwrap())
		.collect();

	let gen_a = generator_a(inputs[0]);
	let gen_b = generator_b(inputs[1]);
	let part1 = gen_a.take(40000000).zip(gen_b).filter(|&(a,b)| (a & 0xFFFF) == (b & 0xFFFF)).count(); 
	println!("Part 1: {}", part1);

	let gen_a = generator_a(inputs[0]).filter(|x| (x % 4) == 0);
	let gen_b = generator_b(inputs[1]).filter(|x| (x % 8) == 0);
	let part2 = gen_a.take(5000000).zip(gen_b).filter(|&(a,b)| (a & 0xFFFF) == (b & 0xFFFF)).count(); 
	println!("Part 2: {}", part2);
}