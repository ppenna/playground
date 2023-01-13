// Copyright (C) 2023 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

use anyhow::Result;
use rand::{
    distributions::{uniform::SampleUniform, Uniform},
    Rng, SeedableRng,
};
use rand_chacha::ChaCha20Rng;
use std::{env::args, time::Instant};

/// Sorts an array using Shell Sort.
fn shell_sort<T: PartialOrd + Copy>(array: &mut [T]) {
    let mut gap: usize = 1;

    // Find initial gap in Knuth's Sequence (3^k - 1)/2.
    while gap < array.len() {
        gap = 3 * gap + 1;
    }

    // Perform gapped insertion sort using Knuth's sequence.
    while gap > 0 {
        // Sorts the input array.
        // Run gapped insertion sort.
        for i in (gap..array.len()).step_by(gap) {
            let mut j: usize = i;
            let tmp: T = array[i];

            // Shift right elements while searching for insertion point.
            while (j >= gap) && (tmp < array[j - gap]) {
                array[j] = array[j - gap];
                j -= gap;
            }

            // Place the element in its final position.
            array[j] = tmp;
        }

        gap /= 3;
    }
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

/// Checks if an array is sorted.
fn is_sorted<T: PartialOrd>(array: &[T]) -> bool {
    for i in 1..array.len() {
        if array[i] < array[i - 1] {
            return false;
        }
    }
    true
}

/// Tests Shell Sort.
fn test(length: usize, verbose: bool) {
    // Fix random number generator seed so that we have
    // a deterministic behavior across runs.
    let mut rng: ChaCha20Rng = ChaCha20Rng::seed_from_u64(0);
    let range: Uniform<usize> = Uniform::new(0, length);

    // Allocate and initialize array.
    let mut array: Vec<usize> = Vec::<usize>::with_capacity(length);
    init_array(&mut array, &mut rng, range);

    if verbose {
        println!("Input: {:?}", array);
    }

    let start: Instant = Instant::now();
    shell_sort(&mut array);
    let end: Instant = Instant::now();

    // Report time.
    println!("Shell Sort: {:.2?} us", (end - start).as_micros());

    if verbose {
        println!("Output: {:?}", array);
    }

    // Check if array is sorted.
    assert_eq!(is_sorted(&array), true);
}

// Prints program usage.
fn usage(args: &Vec<String>) {
    println!("{} - Testing program for shell sort.", args[0]);
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
