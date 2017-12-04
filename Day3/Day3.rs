use std::collections::HashMap;

#[derive(PartialEq)]
enum Direction {
    East,
    North,
    West,
    South,
}

// Manually simulate walking the spiral, keeping track of heading, distance to walk, and current coordinates
fn part1() {
    let mut x = 0;
    let mut y = 0;
    let mut dir = Direction::East;
    let mut next_step_dist = 1;
    let mut step_progress = 0;

    for i in 1..277679 {
        if i == 277678 {
            println!("Iteration: {}, x={}, y={}  dist={}", i, x, y, i32::abs(x) + i32::abs(y));
        }

        match dir {
            Direction::East => x += 1,
            Direction::North => y += 1,
            Direction::West => x -= 1,
            Direction::South => y -= 1,
        }
        step_progress += 1;
        if step_progress == next_step_dist {
            step_progress = 0;

            if dir == Direction::North || dir == Direction::South {
                next_step_dist += 1;
            }
            match dir {
                Direction::East => dir = Direction::North,
                Direction::North => dir = Direction::West,
                Direction::West => dir = Direction::South,
                Direction::South => dir = Direction::East,
            }
        }
    }
}

fn sum_grid(grid: &HashMap<(i32,i32),i32>, x: i32, y: i32) -> i32 {
    let mut sum = 0;
    for xoffset in -1..2 {
        for yoffset in -1..2 {
            // println!("Summing ({} + {}, {} + {}", x, xoffset, y, yoffset);
            match grid.get(&(x + xoffset, y + yoffset)) {
                Some(&number) => sum += number,
                _ => {} /*no-op*/,
            }
        }
    }
    sum
}

// Manually simulate walking the spiral again, storing the square values in a HashMap (rather
// than trying to figure out flexible infinite grid storage)
fn part2() {
    let mut x = 0;
    let mut y = 0;
    let mut dir = Direction::East;
    let mut next_step_dist = 1;
    let mut step_progress = 0;

    let mut grid: HashMap<(i32,i32),i32> = HashMap::new();

    // Seed the grid
    grid.insert((0,0), 1);

    for i in 1.. {
        let cell_value = sum_grid(&grid, x, y);
        grid.insert((x,y), cell_value);

        // println!("Iteration: {}, x={}, y={}  value={}", i, x, y, cell_value);

        if cell_value > 277678 {
            println!("Iteration: {}, x={}, y={}  value={}", i, x, y, cell_value);
            break;
        }

        match dir {
            Direction::East => x += 1,
            Direction::North => y += 1,
            Direction::West => x -= 1,
            Direction::South => y -= 1,
        }
        step_progress += 1;
        if step_progress == next_step_dist {
            step_progress = 0;

            if dir == Direction::North || dir == Direction::South {
                next_step_dist += 1;
            }
            match dir {
                Direction::East => dir = Direction::North,
                Direction::North => dir = Direction::West,
                Direction::West => dir = Direction::South,
                Direction::South => dir = Direction::East,
            }
        }
    }
}

fn main() {
    println!("Part 1:");
    part1();

    println!("\nPart 2:");
    part2();
}