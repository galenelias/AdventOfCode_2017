use std::io::{self, BufRead};
// use itertools::Itertools;

pub fn solve() {
	println!("Enter input:");

	let stdin = io::stdin();
	let lines: Vec<Vec<u32>> = stdin.lock().lines()
		.filter_map(|line| line.ok())
		.map(|line|
			line
				.split_whitespace()
				.filter_map(|el| el.parse::<u32>().ok())
				.collect())
		.collect();

	let part1 : u32 = lines.iter()
		.map(|line| line.iter().max().unwrap() - line.iter().min().unwrap())
		.sum();

	// Hmmm, how to do this functionally...

	// With itertools::Itertools tuple_combinations?
	// let part2 = lines.iter()
	// 	.map(|line|
	// 		line.iter().tuple_combinations());

	// Brute force procedural means (with inner functional)
	let mut part2 : u32 = 0;
	for line in lines
	{
		for el1 in &line
		{
			part2 += line.iter()
				.filter_map(|el2| if el1 > el2 && el1 % el2 == 0 { Some(el1/el2) } else { None })
				.sum::<u32>();
		}
	}

	println!("Part 1: {}", part1);
	println!("Part 2: {}", part2);
	println!("Part 2: {}", part2_functional);
}