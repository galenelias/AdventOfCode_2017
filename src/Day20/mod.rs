use std::io::{self, BufRead};
use std::ops::AddAssign;
use std::collections::HashMap;
use regex::Regex;

#[derive(PartialEq, Eq, Copy, Clone, Hash, Debug)]
struct Point {
	x : i64,
	y : i64,
	z : i64,
}

impl Point {
	fn magnitude(&self) -> i64 {
		self.x.abs() + self.y.abs() + self.z.abs()
	}
}

impl AddAssign for Point {
	fn add_assign(&mut self, other: Point) {
		*self = Point {
			x: self.x + other.x,
			y: self.y + other.y,
			z: self.z + other.z,
		};
	}
}

#[derive(PartialEq, Copy, Clone, Debug)]
struct Particle {
	pos : Point,
	vel : Point,
	acc : Point,
	num : usize,
}

impl Particle {
	fn step(&mut self) {
		self.vel += self.acc;
		self.pos += self.vel;
	}
}

fn part1(mut particles : Vec<Particle>, simulation_steps : usize) {
	for _ in 0..simulation_steps {
		for p in &mut particles {
			p.step();
		}
	}

	println!("Part 1: {}", particles.iter().min_by_key(|p| p.pos.magnitude()).unwrap().num);
}

fn part2(mut particles : Vec<Particle>, simulation_steps : usize) {
	for _ in 0..simulation_steps {
		let mut positions = HashMap::new();
		for p in &particles {
			*positions.entry(p.pos).or_insert(0) += 1;
		}

		particles.retain(|p| positions.get(&p.pos).unwrap() == &1);
		for p in &mut particles {
			p.step();
		}
	}

	println!("Part 2: {}", particles.len());
}

pub fn solve() {
	let re = Regex::new("-?[[:digit:]]+").unwrap();

	println!("Enter input:");
	let stdin = io::stdin();
	let lines: Vec<Vec<_>> = stdin.lock().lines()
		.filter_map(|l| l.ok())
		.map(|l| re.find_iter(&l)
		.filter_map(|m| m.as_str().parse::<i64>().ok())
		.collect())
		.collect();	

	let particles : Vec<Particle> = lines.iter().enumerate().map(|(i, line)| {
		Particle {
			pos: Point { x: line[0], y: line[1], z: line[2] },
			vel: Point { x: line[3], y: line[4], z: line[5] },
			acc: Point { x: line[6], y: line[7], z: line[8] },
			num: i,
		}
	}).collect::<Vec<_>>();

	let simulation_steps = 1_000;
	part1(particles.clone(), simulation_steps);
	part2(particles, simulation_steps);
}