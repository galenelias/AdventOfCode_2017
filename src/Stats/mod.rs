
extern crate serde_json;

use std::io::{self, BufRead};
use serde_json::{Value, Map};
use std::cmp;
use chrono::prelude::*;

#[derive(Deserialize)]
struct Member {
	local_score : i32,
	name : String,
	completion_day_level : Map<String, Value>,
}

#[derive(Deserialize)]
struct LeaderBoard {
	members : Map<String, Value>,
}

pub fn show_stats(day_filter : u32) {
	let stdin = io::stdin();
	let input = stdin.lock().lines().next().unwrap().unwrap();

	let leaderboard: LeaderBoard = serde_json::from_str(input.as_ref()).unwrap();

	let mut members : Vec<Member> = Vec::new();
	let mut max_day = 1;

	for (_id, mem_json) in leaderboard.members {
		let m : Member = serde_json::from_value(mem_json).unwrap();

		for (day, _) in &m.completion_day_level {
			max_day = cmp::max(max_day, day.parse::<u32>().unwrap());
		}

		if !m.completion_day_level.is_empty() {
			members.push(m);
		}
	}

	members.sort_by(|a,b| b.local_score.cmp(&a.local_score));

	let column_width = 19;

	print!("        ");
	for mem in &members {
		print!("    {:^col$} ", mem.name, col=column_width);
	}
	println!("");
	
	for day in 1..max_day+1 {
		if day_filter != 0 && day != day_filter {
			continue;
		}
		let str_day = day.to_string();
		for star in 1..3 {
			let str_star = star.to_string();
			print!("{:>2}-{}:  ", str_day, str_star);

			let mut times : Vec<DateTime<FixedOffset>>  = Vec::new();

			for mem in &members {
				if mem.completion_day_level.contains_key(&str_day) {
					let data = &mem.completion_day_level[&str_day].as_object().unwrap();
					if data.contains_key(&str_star) {
						let date_str = data[&str_star]["get_star_ts"].as_str().unwrap();
						let date = DateTime::parse_from_str(&date_str, "%Y-%m-%dT%H:%M:%S%z").unwrap();
						times.push(date);
					}
				}
			}

			times.sort();

			for mem in &members {
				if mem.completion_day_level.contains_key(&str_day) {
					let data = &mem.completion_day_level[&str_day].as_object().unwrap();
					if data.contains_key(&str_star) {
						let date_str = data[&str_star]["get_star_ts"].as_str().unwrap();
						let date = DateTime::parse_from_str(&date_str, "%Y-%m-%dT%H:%M:%S%z").unwrap();
						let date_local : DateTime<Local> = date.with_timezone(&Local);

						let rank = times.iter().position(|&t| t == date).unwrap();
						print!("({}) {:^column_width$} ", rank+1, date_local.format("%b %d %l:%M:%S%P").to_string(), column_width=column_width);
					}
					else {
						print!("    {:^column_width$} ", "-", column_width=column_width);
					}
				}
				else {
					print!("    {:^column_width$} ", "-", column_width=column_width);
				}
			}
			println!("");
		}
		println!(""); // End of day gap
	}
}