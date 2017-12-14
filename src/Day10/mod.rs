use std::io::{self, BufRead};

fn rotate(lengths: &Vec<usize>, buffer : &mut Vec<u32>, start : &mut usize, skip : &mut usize)
{
	let buf_len = buffer.len();
	for len in lengths {
		for i in 0..len/2 {
			buffer.swap((*start + i) % buf_len, (*start + len - 1 - i) % buf_len);
		}

		*start += len + *skip;
		*skip += 1;
	}
}

fn part1(input : &String) -> u32 {
	let lengths : Vec<usize> = input.split(',').filter_map(|el| el.parse::<usize>().ok()).collect();
	let mut buffer : Vec<u32> = (0..256).collect();
	let mut start = 0;
	let mut skip = 0;
	rotate(&lengths, &mut buffer, &mut start, &mut skip);
	buffer[0] * buffer[1]
}

fn part2(input : &String) {
	let mut lengths : Vec<usize> = input.chars().map(|c| c as usize).collect();
	lengths.extend(&[17, 31, 73, 47, 23]);

	let mut buffer : Vec<u32> = (0..256).collect();
	let mut start = 0;
	let mut skip = 0;

	for _round in 0..64 {
		rotate(&lengths, &mut buffer, &mut start, &mut skip);
	}

	for chunk in 0..16 {
		let mut xor = 0;
		for i in 0..16 {
			xor = xor ^ buffer[chunk*16 + i];
		}
		print!("{:02x}", xor);
	}
}

pub fn solve() {
	println!("Enter input:");

	let stdin = io::stdin();
	let input = stdin.lock().lines().next().unwrap().unwrap();

	println!("Part 1: {}", part1(&input));
	part2(&input);
}