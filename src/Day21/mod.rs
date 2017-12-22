use std::io::{self, BufRead};
use std::collections::HashMap;

fn rotate(input : Vec<Vec<char>>) -> Vec<Vec<char>> {
	let mut output = input.clone();
	let ln = input.len();
	for r in 0..ln {
		for c in 0..ln {
			output[c][ln-1-r] = input[r][c];
		}
	}
	output
}

fn flip(input : Vec<Vec<char>>) -> Vec<Vec<char>> {
	let mut output = input.clone();
	let ln = input.len();
	for r in 0..ln {
		for c in 0..ln {
			output[r][ln-1-c] = input[r][c];
		}
	}
	output
}

fn add_rules(input : Vec<Vec<char>>, output : Vec<Vec<char>>, rules : &mut HashMap<Vec<Vec<char>>,Vec<Vec<char>>>) {
	let mut temp = input;
	for _ in 0..4 {
		temp = rotate(temp);
		rules.insert(temp.clone(), output.clone());
		rules.insert(flip(temp.clone()), output.clone());
	}
}

fn resample(image : Vec<Vec<char>>, rules : &HashMap<Vec<Vec<char>>,Vec<Vec<char>>>) -> Vec<Vec<char>> {
	let image_size = image.len();
	let sample_size = if image.len() % 2 == 0 { 2 } else { 3 };
	let new_size = image.len() * (sample_size + 1) / sample_size;

	let mut result = vec![vec![' '; new_size]; new_size];
	for sample_row in 0..image_size/sample_size {
		for sample_col in 0..image_size/sample_size {
			let mut sample = vec![vec![' '; sample_size]; sample_size];
			for row in 0..sample_size {
				for col in 0..sample_size {
					sample[row][col] = image[sample_row * sample_size + row][sample_col * sample_size + col];
				}
			}

			let ref upsample = rules.get(&sample).unwrap();
			let upsample_size = sample_size + 1;
			for row in 0..upsample_size {
				for col in 0..upsample_size {
					result[sample_row * upsample_size + row][sample_col * upsample_size + col] = upsample[row][col];
				}
			}
		}
	}
	result
}

pub fn solve() {
	println!("Enter input:");
	let stdin = io::stdin();
	let lines: Vec<_> = stdin.lock().lines()
		.filter_map(|l| l.ok())
		.collect();	

	let mut rules = HashMap::new();

	for line in lines {
		let mut sp = line.split(" => ");
		let input = sp.next().unwrap().split('/').map(|s| s.chars().collect::<Vec<char>>()).collect::<Vec<Vec<char>>>();
		let output = sp.next().unwrap().split('/').map(|s| s.chars().collect::<Vec<char>>()).collect::<Vec<Vec<char>>>();
		add_rules(input, output, &mut rules);
	}

	let mut image = vec![vec!['.','#','.'], vec!['.','.','#'], vec!['#','#','#']];

	for i in 0..18 {
		image = resample(image, &rules);

		if i+1 == 5 || i+1 == 18 {
			println!("Resample phase #{}  {}", i + 1, image.iter().map(|row| row.iter().filter(|&ch| ch == &'#').count()).sum::<usize>());
		}
	}
}