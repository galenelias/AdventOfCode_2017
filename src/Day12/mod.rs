use std::io::{self, BufRead};
use std::collections::HashSet;
use std::collections::HashMap;
use std::collections::VecDeque;
use regex::Regex;

fn build_graph(input : Vec<Vec<i32>>) -> HashMap<i32,Vec<i32>> {
	let mut graph : HashMap<i32,Vec<i32>> = HashMap::new();

	for line in input {
		let children = line.iter().skip(1).cloned().collect::<Vec<i32>>();
		graph.insert(line[0], children);
	}
	return graph;
}

fn build_group(node : i32, graph : &HashMap<i32,Vec<i32>>) -> HashSet<i32> {
	let mut group = HashSet::new();

	let mut pending_nodes = VecDeque::new();
	pending_nodes.push_back(node);

	while !pending_nodes.is_empty() {
		let n = pending_nodes.pop_front().unwrap();
		if !group.contains(&n) {
			group.insert(n);
			pending_nodes.extend(graph.get(&n).unwrap().iter());
		}
	}
	return group;
}

pub fn solve() {
	let re = Regex::new("[[:digit:]]+").unwrap();

	println!("Enter input:");
	let stdin = io::stdin();
	let lines: Vec<Vec<_>> = stdin.lock().lines()
		.filter_map(|l| l.ok())
		.map(|l| re.find_iter(&l)
		.filter_map(|m| m.as_str().parse::<i32>().ok())
		.collect())
		.collect();

	let graph = build_graph(lines);
	let mut groups : Vec<HashSet<i32>> = Vec::new();

	for (node,_children) in &graph {
		if !groups.iter().any(|group| group.contains(node)) {
			groups.push(build_group(*node, &graph));
		}
	}

	let group_0_size = groups.iter().find(|group| group.contains(&0)).unwrap().len();
	println!("Part 1: {}", group_0_size);
	println!("Part 2: {}", groups.len());
}