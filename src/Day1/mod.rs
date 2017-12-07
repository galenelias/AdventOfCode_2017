use std::io::{self, BufRead};

pub fn solve() {
	println!("Enter input to checksum:");
	let stdin = io::stdin();
	let input = stdin.lock().lines().next().unwrap().unwrap();
	let input_ints = input.chars().filter_map(|c| { return c.to_digit(10);}).collect::<Vec<u32>>();

	let sum1 : u32 = input_ints.iter()
		.zip(input_ints.iter().cycle().skip(1))
		.filter_map(|(a, b)| { if a == b { Some(a) } else { None }})
		.sum();

	let sum2 : u32 = input_ints.iter()
		.zip(input_ints.iter().cycle().skip(input_ints.len()/2))
		.filter_map(|(a, b)| { if a == b { Some(a) } else { None }})
		.sum();

	println!("Part1: {}", sum1);
	println!("Part2: {}", sum2);
}