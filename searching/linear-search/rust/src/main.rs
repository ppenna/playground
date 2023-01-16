// Copyright (C) 2023 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

use anyhow::Result;
use rand::{
    distributions::{uniform::SampleUniform, Uniform},
    Rng, SeedableRng,
};
use rand_chacha::ChaCha20Rng;
use std::{cmp::Eq, env::args, time::Instant};

/// Finds an element in an array using Linear Search.
fn linear_search<T: Eq>(array: &[T], x: &T) -> usize {
    // Traverse the array searching for the target element.
    for i in 0..array.len() {
        // Found.
        if &array[i] == x {
            return i;
        }
    }

    usize::MAX
}

/// Initializes an array.
fn init_array<T>(array: &mut Vec<T>, rng: &mut ChaCha20Rng, range: Uniform<T>)
where
    T: SampleUniform,
{
    for _ in 0..array.capacity() {
        array.push(rng.sample(&range))
    }
}

/// Tests Linear Search.
fn test(length: usize, verbose: bool) {
    // Fix random number generator seed so that we have
    // a deterministic behavior across runs.
    let mut rng: ChaCha20Rng = ChaCha20Rng::seed_from_u64(0);
    let range: Uniform<usize> = Uniform::new(0, length);

    // Allocate and initialize array.
    let mut array: Vec<usize> = Vec::<usize>::with_capacity(length);
    init_array(&mut array, &mut rng, range);

    let key: &usize = &array[(rng.sample(&range))];

    if verbose {
        println!("Input: {:?}", array);
    }

    let start: Instant = Instant::now();
    let index: usize = linear_search(&array, key);
    let end: Instant = Instant::now();

    // Report time.
    println!("Linear Search: {:.2?} us", (end - start).as_micros());

    if verbose {
        let result: String = if index != usize::MAX {
            "found".to_string()
        } else {
            "not found".to_string()
        };
        println!("Output: {:?}", result);
    }

    // Check solution.
    assert_eq!(key, &array[index]);
}

// Prints program usage.
fn usage(args: &Vec<String>) {
    println!("{} - Testing program for linear search.", args[0]);
    println!("Usage: {} [--verbose] <array length>", args[0]);
}

fn main() -> Result<()> {
    let args: Vec<String> = args().collect();

    // Check for missing arguments.
    if (args.len() < 2) || (args.len() > 3) {
        usage(&args);
        anyhow::bail!("invalid number of arguments {:?}", args);
    }

    // Parse command line arguments.
    let (length, verbose): (usize, bool) = if args.len() == 2 {
        (args[1].parse()?, false)
    } else if (args.len() == 3) && (args[1] == "--verbose") {
        (args[2].parse()?, true)
    } else {
        anyhow::bail!("invalid argument");
    };

    test(length, verbose);

    Ok(())
}
