use std::io::{self, BufRead};
use std::collections::HashMap;

#[derive(Debug, PartialEq)]
enum State {
	Clean,
	Infected,
	Weakened,
	Flagged,
}

enum Direction {
	Up, Right, Down, Left
}

impl Direction {
	fn move_pos(&self, pos : (i32, i32)) -> (i32, i32) {
		match self {
			&Direction::Up => (pos.0 - 1, pos.1),
			&Direction::Right => (pos.0, pos.1 + 1),
			&Direction::Down => (pos.0 + 1, pos.1),
			&Direction::Left => (pos.0, pos.1 - 1),
		}
	}
}

impl From<u8> for Direction {
	fn from(original: u8) -> Direction {
		match original % 4 {
			0 => Direction::Up,
			1 => Direction::Right,
			2 => Direction::Down,
			3 => Direction::Left,
			_ => panic!("Unexpected direction"),
		}
	}
}

fn build_grid(input : &Vec<Vec<char>>) -> HashMap<(i32,i32),State> {
	let mut grid = HashMap::new();
	let grid_offset = (input.len() / 2) as i32;
	for (r, row) in input.iter().enumerate() {
		for (c, ch) in row.iter().enumerate() {
			if ch == &'#' {
				grid.insert((r as i32 - grid_offset, c as i32 - grid_offset), State::Infected);
			}
		}
	}
	grid
}

fn part1(input : &Vec<Vec<char>>)
{
	let mut grid = build_grid(input);

	let mut dir = Direction::Up;
	let mut pos = (0,0);
	let mut infections = 0;

	for _ in 0..10000 {
		let cell = grid.entry(pos).or_insert(State::Clean);
		dir = match *cell {
			State::Infected => {
				*cell = State::Clean;
				Direction::from(dir as u8 + 1) // turn right
			}
			State::Clean => {
				infections += 1;
				*cell = State::Infected;
				Direction::from(dir as u8 + 3) // turn left
			}
			_ => panic!("Unexpected state"),
		};

		pos = dir.move_pos(pos);
	}
	println!("Part 1: {}", infections);
}

fn part2(input : &Vec<Vec<char>>)
{
	let mut grid = build_grid(input);

	let mut dir = Direction::Up;
	let mut pos = (0,0);
	let mut infections = 0;

	for _ in 0..10000000 {
		let cell = grid.entry(pos).or_insert(State::Clean);
		dir = match *cell {
			State::Clean => {
				*cell = State::Weakened;
				Direction::from(dir as u8 + 3) // turn left
			}
			State::Weakened => {
				*cell = State::Infected;
				dir
			}
			State::Infected => {
				*cell = State::Flagged;
				Direction::from(dir as u8 + 1) // turn right
			}
			State::Flagged => {
				*cell = State::Clean;	
				Direction::from(dir as u8 + 2) // turn around
			}
		};

		if *cell == State::Infected {
			infections += 1;
		}

		pos = dir.move_pos(pos);
	}
	println!("Part 2: {}", infections);
}

pub fn solve() {
	println!("Enter input:");
	let stdin = io::stdin();
	let lines: Vec<Vec<char>> = stdin.lock().lines()
		.filter_map(|l| l.ok())
		.map(|l| l.chars().collect::<Vec<_>>())
		.collect();	

	part1(&lines);
	part2(&lines);
}
