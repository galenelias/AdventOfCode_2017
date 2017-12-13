use std::io::{self, BufRead};
use std::cmp;

fn hex_distance(x: i32, y: i32, z: i32) -> i32 {
	cmp::max(x.abs(), cmp::max(y.abs(), z.abs()))
}

pub fn solve() {
	println!("Enter input:");
	let input = io::stdin().lock().lines().next().unwrap().unwrap();

	let (mut x, mut y, mut z) = (0, 0, 0);
	let mut max_dist = 0;

	for dir in input.split(',') {
		match dir {
			"n" => { y += 1; z -= 1; },
			"s" => { y -= 1; z += 1; },
			"ne" => { x += 1; z -= 1; },
			"se" => { x += 1; y -= 1; },
			"nw" => { x -= 1; y += 1; },
			"sw" => { x -= 1; z += 1; },
			_ => panic!("Unrecognized direction: {}", dir),
		}
		max_dist = cmp::max(max_dist, hex_distance(x, y, z));
	}

	println!("Final distance (part 1): {}", hex_distance(x, y, z));
	println!("Max distance (part 2): {}", max_dist);
}