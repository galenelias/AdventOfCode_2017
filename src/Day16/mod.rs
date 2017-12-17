use std::io::{self, BufRead};
use std::ascii::AsciiExt;

fn dance(dancers : &mut Vec<char>, moves : &Vec<&str>) {
	for mv in moves {
		let (instruction, params) = mv.split_at(1);
		match instruction {
			"s" => {
				let x : usize = params.parse().unwrap();
				let dancers_len = dancers.len();
				dancers.rotate(dancers_len - x);
			}
			"x" => {
				let pair : Vec<&str> = params.split('/').collect();
				dancers.swap(pair[0].parse().unwrap(), pair[1].parse().unwrap());
			}
			"p" => {
				let pair : Vec<&str> = params.split('/').collect();
				let pos_a = dancers.iter().position(|d| d == &pair[0].chars().next().unwrap()).unwrap();	
				let pos_b = dancers.iter().position(|d| d == &pair[1].chars().next().unwrap()).unwrap();	
				dancers.swap(pos_a, pos_b);
			}
			_ => panic!("Unrecognized instruction: {}", instruction),
		}
	}
}

fn part1(mut dancers : Vec<char>, moves : &Vec<&str>) {
	dance(&mut dancers, &moves);
	println!("Part 1: {}", dancers.iter().collect::<String>());
}

fn part2(mut dancers : Vec<char>, moves : &Vec<&str>, iterations : usize) {
	let mut dance_history : Vec<Vec<char>> = Vec::new();
	dance_history.push(dancers.clone());
	for i in 1..iterations+1 {
		dance(&mut dancers, &moves);

		match dance_history.iter().position(|d| d == &dancers) {
			Some(pos) => {
				// Cycle detected. Find terminal state in loop
				// pos = start of cycle
				// i - pos = length of cycle
				let final_state = &dance_history[(iterations - pos) % (i - pos) + pos];
				println!("Found repeat of {} at {}", i, pos);
				println!("Part 2: {}", final_state.iter().collect::<String>());
				break;
			},
			None => dance_history.push(dancers.clone())
		}
	}
}

pub fn solve() {
	println!("Enter input:");
	let stdin = io::stdin();
	let input = stdin.lock().lines().next().unwrap().unwrap();

	let dancers : Vec<char> = (0..16).map(|i| (0x61 + i).to_ascii_lowercase() as char).collect();
	let move_list = input.split(',').collect::<Vec<&str>>();

	part1(dancers.clone(), &move_list);
	part2(dancers.clone(), &move_list, 1000000000);
}