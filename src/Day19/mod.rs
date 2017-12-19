use std::io::{self, BufRead};

enum Dir { Up, Down, Left, Right, }

fn move_dir(pos : (usize, usize), dir : &Dir) -> (usize, usize) {
	match dir {
		&Dir::Up => (pos.0 - 1, pos.1),
		&Dir::Down => (pos.0 + 1, pos.1),
		&Dir::Left => (pos.0, pos.1 - 1),
		&Dir::Right => (pos.0, pos.1 + 1),
	}
}

fn try_dir(grid: &Vec<Vec<char>>, pos : (usize, usize), dir : &Dir) -> bool {
	let npos = move_dir(pos, dir);
	grid[npos.0][npos.1] != ' '
}

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

	let mut pos = (0, grid[0].iter().position(|c| c == &'|').unwrap());
	let mut dir = Dir::Down;
	let mut steps = 0;
	let mut path_str = String::new();
	loop {
		steps += 1;

		if "ABCDEFGHIJKLMNOPQRSTUVWXYZ".contains(grid[pos.0][pos.1]) {
			path_str.push(grid[pos.0][pos.1]);
		}

		if !try_dir(&grid, pos, &dir) {
			match &dir {
				&Dir::Up | &Dir::Down if try_dir(&grid, pos, &Dir::Left) => dir = Dir::Left,
				&Dir::Up | &Dir::Down if try_dir(&grid, pos, &Dir::Right) => dir = Dir::Right,
				&Dir::Left | &Dir::Right if try_dir(&grid, pos, &Dir::Up) => dir = Dir::Up,
				&Dir::Left | &Dir::Right if try_dir(&grid, pos, &Dir::Down) => dir = Dir::Down,
				_ => break,
			}
		}
		pos = move_dir(pos, &dir);
	}

	println!("Part 1: {}", path_str);
	println!("Part 2: {}", steps);
}