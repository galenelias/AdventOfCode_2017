use std::io::{self, BufRead};

pub fn solve() {
	let stdin = io::stdin();

	println!("Enter input:");

	let input = stdin.lock().lines().next().unwrap().unwrap();

	let mut score = 0;
	let mut garbage = 0;
	let mut nesting = 0;

	let mut it = input.chars();
	while let Some(ch) = it.next() {
		match ch {
			'{' => {
				nesting += 1;
			},
			'}' => {
				score += nesting;
				nesting -= 1;
			},
			',' => (),
			'<' => {
				while let Some(ch2) = it.next() {
					if ch2 == '!' { it.next(); } 
					else if ch2 == '>' { break; }
					else { garbage += 1; }
				}
			},
			_ => panic!("Unexpected character: {}", ch),
		}
	}
	println!("Score (part 1) = {}", score);
	println!("Gargabe (part 2) = {}", garbage);
}