use std::io::{self, BufRead};
use regex::Regex;


pub fn solve() {
	let re = Regex::new("[[:digit:]]+").unwrap();

	println!("Enter input:");
	let stdin = io::stdin();
		let lines: Vec<Vec<_>> = stdin.lock().lines()
		.filter_map(|l| l.ok())
		.map(|l| re.find_iter(&l)
		.map(|m| m.as_str().parse::<i32>())
		.collect())
		.collect();


}