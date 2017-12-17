
use std::io::{self, BufRead};

use day10;

fn color_grid(grid : &mut [[i32; 128]; 128], row : i32, col : i32, color : i32) {
	if row < 0 || col < 0 || row >= 128 || col >= 128 || grid[row as usize][col as usize] != -1 {
		return;
	}
	
	grid[row as usize][col as usize] = color;
	color_grid(grid, row + 1, col, color);
	color_grid(grid, row - 1, col, color);
	color_grid(grid, row, col + 1, color);
	color_grid(grid, row, col - 1, color);
}

pub fn solve() {
	println!("Enter input:");
	let stdin = io::stdin();
	let input = stdin.lock().lines().next().unwrap().unwrap();

	let mut grid = [[0i32; 128]; 128];

	for row in 0..128 {
		let hash : Vec<u32> = day10::knot_hash(&(format!("{}-{}", input, row)));
		for col in 0..16 {
			let ch = hash[col];
			for bit in 0..8 {
				grid[row][col * 8 + bit] = if (ch & (1 << (7 - bit))) != 0 { -1 } else { 0 };
			}
		}
	}

	let part1 = grid.iter()
				.map(|row| {
					row.iter().filter(|el| *el == &-1).count()
				}).sum::<usize>();
	println!("Part 1: {}", part1);

	let mut next_color = 0;
	for row in 0..128 {
		for col in 0..128 {
			if grid[row][col] == -1 {
				next_color += 1;
				color_grid(&mut grid, row as i32, col as i32, next_color);
			}
		}
	}

	println!("Part 2: {}", next_color);
}