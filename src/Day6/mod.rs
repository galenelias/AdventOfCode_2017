use std::io::{self, BufRead};

fn part1(input: &Vec<i32>) -> u32 {
	let mut jump_offsets = input.clone();
	let mut instruction_counter = 0;
	let mut iteration_count = 0;
	while instruction_counter < jump_offsets.len() {
		iteration_count += 1;
		let jump_val = jump_offsets[instruction_counter];
		jump_offsets[instruction_counter] += 1;
		instruction_counter = (instruction_counter as i32 + jump_val) as usize;
	}
	iteration_count
}

fn part2(input: &Vec<i32>) -> u32 {
	let mut jump_offsets = input.clone();
	let mut instruction_counter = 0;
	let mut iteration_count = 0;
	while instruction_counter < jump_offsets.len() {
		iteration_count += 1;
		let jump_val = jump_offsets[instruction_counter];
		if jump_val >= 3 {
			jump_offsets[instruction_counter] -= 1;
		} else {
			jump_offsets[instruction_counter] += 1;
		}
		instruction_counter = (instruction_counter as i32 + jump_val) as usize;
	}
	iteration_count
}

pub fn solve() {
	let stdin = io::stdin();

	println!("Enter input:");
	let input: Vec<i32> = stdin.lock().lines()
		.filter_map(|line| line.ok())
		.filter_map(|line| line.parse::<i32>().ok())
		.collect();

	println!("Part 1 (iterations) = {}", part1(&input));
	println!("Part 2 (iterations) = {}", part2(&input));
}