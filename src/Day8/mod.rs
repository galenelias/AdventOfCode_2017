use std::io::{self, BufRead};
use std::collections::HashMap;
use std::cmp;

pub fn solve() {
	let stdin = io::stdin();

	println!("Enter input:");

	// Read stdin into an array of the form ["node", "(weight)", "child", ...]
	let input: Vec<Vec<String>> = stdin.lock().lines()
		.filter_map(|line| line.ok())
		.map(|line| line.split_whitespace().map(|word| word.to_string()).collect())
		.collect();

	let mut largest_register_value = <i32>::min_value();
	let mut registers : HashMap<String, i32> = HashMap::new();

	for line in &input {
		let condition_reg = *registers.get(&(line[4])).unwrap_or(&0);
		let condition_imm = line[6].parse::<i32>().unwrap();

		let cmp = match line[5].as_ref() {
			"<" => condition_reg < condition_imm,
			"<=" => condition_reg <= condition_imm,
			">" => condition_reg > condition_imm,
			">=" => condition_reg >= condition_imm,
			"==" => condition_reg == condition_imm,
			"!=" => condition_reg != condition_imm,
			_ => panic!("Unrcognized comparison operator: {}", line[5]),
		};

		if cmp {
			let reg = registers.entry(line[0].clone()).or_insert(0);
			let immediate = line[2].parse::<i32>().unwrap();
			match line[1].as_ref() {
				"inc" => *reg += immediate,
				"dec" => *reg -= immediate,
				_ => panic!("Unrcognized operator: {}", line[1]),
			}

			largest_register_value = cmp::max(largest_register_value, *reg);
		}
	}

	println!("Largest final register: {}", registers.values().max().unwrap());
	println!("Largest observed register value: {}", largest_register_value);
}