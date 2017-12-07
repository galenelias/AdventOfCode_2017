use std::collections::HashSet;
use std::io::{self, BufRead};

pub fn solve() {
	let stdin = io::stdin();
	let input: Vec<Vec<_>> = stdin.lock().lines()
		.filter_map(|line| line.ok())
		.map(|line| line.split_whitespace().map(|word| word.to_string()).collect())
		.collect();

	let valid_count_1 = input.iter()
		.filter(|line| {
			let mut seen_words = HashSet::new();
			let count_invalid = line.iter().filter(|word| {
				!seen_words.insert(word.clone())
			}).count();
			count_invalid == 0
		}).count();

	let valid_count_2 = input.iter()
		.filter(|line| {
			let mut seen_words = HashSet::new();
			let count_invalid = line.iter().filter(|word| {
				let mut chars: Vec<char> = word.chars().collect();
				chars.sort();
				!seen_words.insert(chars)
			}).count();
			count_invalid == 0
		}).count();

	println!("Valid count (part 1)= {}", valid_count_1);
	println!("Valid count (part 2)= {}", valid_count_2);
}