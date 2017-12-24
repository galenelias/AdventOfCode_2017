use std::io::{self, BufRead};

fn tuple_other(tup : &(u32, u32), val : u32) -> u32
{
	if tup.0 == val { tup.1 } else { tup.0 }
}

fn build_bridge(adapter : u32, value : u32, pieces : &[(u32,u32)]) -> u32
{
	pieces.iter().enumerate().filter_map(|(i,p)| {
		if p.0 == adapter || p.1 == adapter {
			let mut leftovers = pieces.to_vec();
			leftovers.swap_remove(i);
			Some(build_bridge(tuple_other(p, adapter), value + p.0 + p.1, &leftovers))
		} else {
			None
		}
	}).max().unwrap_or(value)
}

fn build_longest_bridge(adapter : u32, length : u32, value : u32, pieces : &[(u32,u32)]) -> (u32, u32)
{
	pieces.iter().enumerate().filter_map(|(i,p)| {
		if p.0 == adapter || p.1 == adapter {
			let mut leftovers = pieces.to_vec();
			leftovers.swap_remove(i);
			Some(build_longest_bridge(tuple_other(p, adapter), length + 1, value + p.0 + p.1, &leftovers))
		} else {
			None
		}
	}).max().unwrap_or((length, value))
}

pub fn solve() {
	println!("Enter input:");
	let stdin = io::stdin();
	let pieces: Vec<_> = stdin.lock().lines()
		.filter_map(|l| l.ok())
		.map(|s| {
			let mut parts = s.split('/');
			(parts.next().unwrap().parse::<u32>().unwrap(),parts.next().unwrap().parse::<u32>().unwrap())
		}).collect();

	println!("Part 1: {}", build_bridge(0, 0, &pieces));

	let part2 = build_longest_bridge(0, 0, 0, &pieces);
	println!("Part 2: {} (length = {})", part2.1, part2.0);
}
