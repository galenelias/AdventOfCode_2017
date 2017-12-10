use std::io::{self, BufRead};
use regex::Regex;
use std::collections::HashMap;
use std::collections::HashSet;

struct Node {
	weight: u32,
	children: Vec<String>,
}

fn compute_weight(root: &String, nodes : &HashMap<String, Node>) -> u32 {
	let node = nodes.get(root).unwrap();
	node.weight + node.children.iter().map(|n| compute_weight(n, nodes)).sum::<u32>()
}

fn find_mismatch(root: &String, nodes : &HashMap<String, Node>, target_weight: u32) -> u32 {
	let node = nodes.get(root).unwrap();
	let child_weights = node.children.iter().map(|n| compute_weight(n, nodes)).collect::<Vec<u32>>();

	let mut weight_histogram : HashMap<u32,u32> = HashMap::new();
	for weight in child_weights {
		let count = weight_histogram.entry(weight).or_insert(0);
		*count += 1;
	}

	if weight_histogram.len() == 1 {
		// If all our children are balanced, then we must be the unbalaned one. Return the ideal weight minus our children (which are correct)
		return target_weight - weight_histogram.iter().map(|(k,v)| k * v).sum::<u32>();
	} else {
		let (target_child_weight, _) = weight_histogram.iter().find(|&(_,v)| *v > 1).unwrap();
		let (incorrect_child_weight, _) = weight_histogram.iter().find(|&(_,v)| *v == 1).unwrap();
		let incorrect_child_name = node.children.iter().find(|&child| compute_weight(child, nodes) == *incorrect_child_weight).unwrap();

		// println!("Found mismatch in {}. Wrong weight = {}.  Correct weight = {}", root, incorrect_child_weight, target_child_weight);
		// Recurse into the node with the wrong weight, passing in the expected weight
		return find_mismatch(incorrect_child_name, nodes, *target_child_weight);
	}
}

pub fn solve() {
	let stdin = io::stdin();

	println!("Enter input:");

	let re = Regex::new("[[:word:]]+").unwrap();

	// Read stdin into an array of the form ["node", "(weight)", "child", ...]
	let lines: Vec<Vec<_>> = stdin.lock().lines()
		.filter_map(|l| l.ok())
		.map(|l| re.find_iter(&l)
		.map(|m| m.as_str().to_string())
		.collect())
		.collect();

	let mut nodes = HashMap::new();
	let mut potential_roots : HashSet<String> = HashSet::new();

	for line in lines {
		let name = line[0].clone();
		let weight = line[1].parse::<u32>().unwrap();

		let children = line.iter().skip(2).map(|w| w.clone()).collect();
		nodes.insert(name.clone(), Node { weight, children});

		potential_roots.insert(name);
	}

	for (_name,node) in &nodes {
		for child in &node.children {
			potential_roots.remove::<String>(&child);
		}
	}

	let root_node = potential_roots.iter().next().unwrap();
	println!("Root node: {}", root_node);
	println!("Corrected weight: {}", find_mismatch(root_node, &nodes, 0));
}