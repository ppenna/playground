// Copyright (C) 2023 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

use anyhow::Result;
use rand::{
    distributions::{uniform::SampleUniform, Uniform},
    Rng, SeedableRng,
};
use rand_chacha::ChaCha20Rng;
use std::{cmp, env::args, time::Instant};

// Searches for an element in a sorted range using Binary Search.
fn binary_search<T: PartialOrd>(array: &[T], mut low: usize, mut high: usize, x: &T) -> usize {
    while low < high {
        let mid: usize = low + (high - low) / 2;

        eprintln!("low: {:?}, mid: {:?} high: {:?}", low, mid, high);

        // Found.
        if &array[mid] == x {
            return mid;
        }
        // Search on the left sub-array.
        else if x < &array[mid] {
            high = mid;
        }
        // Search on the right sub-array.
        else {
            low = mid + 1;
        }
    }

    usize::MAX
}

/// Searches an element in an array using Exponential Search.
fn exponential_search<T: PartialOrd + std::fmt::Debug>(array: &[T], x: &T) -> usize {
    let mut bound: usize = 1;

    while (bound < array.len()) && (&array[bound] < x) {
        bound *= 2;
    }
    eprintln!("bound={:?} x={:?}", bound, x);
    binary_search(array, bound / 2, cmp::min(bound + 1, array.len()), x)
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

/// Tests Exponential Search.
fn test(length: usize, verbose: bool) {
    // Fix random number generator seed so that we have
    // a deterministic behavior across runs.
    let mut rng: ChaCha20Rng = ChaCha20Rng::seed_from_u64(0);
    let range: Uniform<usize> = Uniform::new(0, length);

    // Allocate and initialize array.
    let mut array: Vec<usize> = Vec::<usize>::with_capacity(length);
    init_array(&mut array, &mut rng, range);
    array.sort();

    let key: &usize = &array[(rng.sample(&range))];

    if verbose {
        println!("Input: {:?}", array);
    }

    let start: Instant = Instant::now();
    let index: usize = exponential_search(&array, key);
    let end: Instant = Instant::now();

    // Report time.
    println!("Exponential Search: {:.2?} us", (end - start).as_micros());

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
    println!("{} - Testing program for exponential search.", args[0]);
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
