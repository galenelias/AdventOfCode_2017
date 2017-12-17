use std::io::{self, BufRead};

fn part1(stride : usize) {
	let mut buffer : Vec<usize> = Vec::new();
	let mut pos = 0;
	buffer.push(0);
	for i in 0..2017 {
		pos = (pos + stride) % buffer.len() + 1;
		buffer.insert(pos, i + 1);
	}

	match buffer.iter().position(|el| el == &2017) {
		Some(pos) => println!("Part 1: {}", buffer[(pos + 1) % buffer.len()]),
		None => panic!("Unexpected! Didn't find '2017'"),
	}
}

fn part2(stride : usize) {
	let mut buf_len = 1;
	let mut pos = 0;
	let mut pos1_value = 0;
	for i in 0..50000000 {
		pos = (pos + stride) % buf_len + 1;
		if pos == 1 {
			pos1_value = i + 1;
		}
		buf_len += 1;
	}
	println!("Part 2: {}", pos1_value);
}

pub fn solve() {
	let stdin = io::stdin();
	let input = stdin.lock().lines().next().unwrap().unwrap();
	let stride = input.parse::<usize>().unwrap();

	part1(stride);
	part2(stride);
}
