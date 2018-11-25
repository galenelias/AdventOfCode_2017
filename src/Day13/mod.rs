use std::io::{self, BufRead};

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
	let stdin = io::stdin();
	let lines: Vec<Vec<u32>> = stdin.lock().lines()
		.filter_map(|l| l.ok())
		.map(|l| l.split(": ").map(|w| w.parse::<u32>().unwrap()).collect())
		.collect();

	let scanners = lines.iter().map(|line| Scanner { depth: line[0], range: line[1] }).collect();

	println!("Part 1: {}", check_scanners(0 /*depth*/, &scanners).1);

	let part2 = (0..)
		.filter(|&delay| !check_scanners(delay, &scanners).0)
		.next().unwrap();
	println!("Part 2: {}", part2);
}