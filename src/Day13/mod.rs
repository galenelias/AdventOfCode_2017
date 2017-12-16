use std::io::{self, BufRead};
use regex::Regex;

struct Scanner {
	depth: u32,
	range: u32,
}

fn check_scanners(delay: u32, scanners: &Vec<Scanner>) -> (bool, u32) {
	let mut score = 0;
	let mut hit = false;
	for scanner in scanners {
		if ((delay + scanner.depth) % ((scanner.range - 1)*2)) == 0 {
			hit = true;
			score += scanner.depth * scanner.range;
		}
	}
	(hit, score)
}

pub fn solve() {
	let re = Regex::new("[[:digit:]]+").unwrap();

	println!("Enter input:");
	let stdin = io::stdin();
	let lines: Vec<Vec<_>> = stdin.lock().lines()
		.filter_map(|l| l.ok())
		.map(|l| re.find_iter(&l)
		.filter_map(|m| m.as_str().parse::<u32>().ok())
		.collect())
		.collect();

	let scanners = lines.iter().map(|line| Scanner { depth: line[0], range: line[1] }).collect();
	
	println!("Part 1: {}", check_scanners(0 /*depth*/, &scanners).1);

	for delay in 0.. {
		let (hit, _score) = check_scanners(delay, &scanners);
		if !hit {
			println!("Part 2: {}", delay);
			break;
		}
	}
}