use std::io::{self, BufRead};

fn rotate(lengths: &Vec<usize>, buffer : &mut Vec<u32>, rounds : u32)
{
	let mut start = 0;
	let mut skip = 0;
	let buf_len = buffer.len();

	for _round in 0..rounds {
		for len in lengths {
			for i in 0..len/2 {
				buffer.swap((start + i) % buf_len, (start + len - 1 - i) % buf_len);
			}

			start += len + skip;
			skip += 1;
		}
	}
}

fn part1(input : &String) -> u32 {
	let lengths : Vec<usize> = input.split(',').filter_map(|el| el.parse::<usize>().ok()).collect();
	let mut buffer : Vec<u32> = (0..256).collect();
	rotate(&lengths, &mut buffer, 1);
	buffer[0] * buffer[1]
}

fn part2(input : &String) -> String {
	let mut lengths : Vec<usize> = input.chars().map(|c| c as usize).collect();
	lengths.extend(&[17, 31, 73, 47, 23]);

	let mut buffer : Vec<u32> = (0..256).collect();
	rotate(&lengths, &mut buffer, 64);

	buffer.chunks(16)
		.map(|chunk| chunk.iter().fold(0, |acc, &val| acc ^ val))
		.map(|xor| format!("{:02x}", xor))
		.collect::<Vec<String>>()
		.join("")
}

pub fn solve() {
	println!("Enter input:");

	let stdin = io::stdin();
	let input = stdin.lock().lines().next().unwrap().unwrap();

	println!("Part 1: {}", part1(&input));
	println!("Part 2: {}", part2(&input));
}