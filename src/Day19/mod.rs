use std::io::{self, BufRead};

pub fn solve() {
	println!("Enter input:");
	let stdin = io::stdin();
	let mut grid: Vec<Vec<char>> = stdin.lock().lines()
		.filter_map(|l| l.ok())
		.map(|l| format!(" {} ", l))
		.map(|l| l.chars().collect())
		.collect();
	
	let cols = grid[0].len();
	grid.push(" ".repeat(cols).chars().collect());

	let mut row = 0;
	let mut col = grid[0].iter().position(|c| c == &'|').unwrap();
	let mut row_dir : isize = 0;
	let mut col_dir : isize = 1;
	let mut steps = 0;
	let mut path_str = String::new();
	loop {
		steps += 1;

		if "ABCDEFGHIJKLMNOPQRSTUVWXYZ".contains(grid[row][col]) {
			path_str.push(grid[row][col]);
		}
		if row_dir != 0 && grid[(row as isize + row_dir) as usize][col] == ' ' {
			row_dir = 0;
			if grid[row][col - 1] != ' ' {
				col_dir = -1;
			} else if grid[row][col + 1] != ' ' {
				col_dir = 1;
			}
		} else if col_dir != 0 && grid[row][(col as isize + col_dir) as usize] == ' ' {
			col_dir = 0;
			if grid[row + 1][col] != ' ' {
				row_dir = 1;
			} else if grid[row - 1][col] != ' ' {
				row_dir = -1;
			}		
		}

		if row_dir == 0 && col_dir == 0 {
			break;
		}

		row = (row as isize + row_dir) as usize;
		col = (col as isize + col_dir) as usize;
	}

	println!("Part 1: {}", path_str);
	println!("Part 2: {}", steps);
}