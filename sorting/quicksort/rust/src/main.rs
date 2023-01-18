// Copyright (C) 2023 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

use anyhow::Result;
use rand::{
    distributions::{uniform::SampleUniform, Uniform},
    Rng, SeedableRng,
};
use rand_chacha::ChaCha20Rng;
use std::{env::args, time::Instant};

/// Sorts an array using Quicksort.
fn quicksort<T: PartialOrd>(array: &mut [T]) {
    // Finds a Quicksort partition.
    fn partition<T: PartialOrd>(array: &mut [T], left: usize, right: usize) -> usize {
        let mut i: usize = left + 1;
        let mut j: usize = right;
        let mid: usize = left + (right - left) / 2;

        // Make the pivot element a sentinel.
        array.swap(left, mid);

        // Find partition and swap elements that are out of order.
        loop {
            // Skip elements that are smaller than *or* equal the pivot.
            while (i < right) && (array[i] <= array[left]) {
                i += 1;
            }

            // Skip elements that are *only* greater than the pivot.
            // Note that we don't need to perform a bound check here, because
            // At the leftmost position we placed the pivot element as sentinel.
            while array[j] > array[left] {
                j -= 1
            }

            // Partition found.
            if i >= j {
                break;
            }

            // Swap elements.
            array.swap(i, j)
        }

        // Place pivot element in its final position.
        array.swap(left, j);

        j
    }

    /// Recursive Quicksort function.
    fn _quicksort<T: PartialOrd>(array: &mut [T], left: usize, right: usize) {
        if right > left {
            let p: usize = partition(array, left, right);

            // Overflow protection: recurse only if there is a left-hand partition.
            if p > 0 {
                _quicksort(array, left, p - 1);
            }

            // There is always a right-hand partition.
            _quicksort(array, p + 1, right);
        }
    }

    _quicksort(array, 0, array.len() - 1);
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
        if array[i - 1] > array[i] {
            return false;
        }
    }
    true
}

/// Tests Quicksort.
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
    quicksort(&mut array);
    let end: Instant = Instant::now();

    // Report time.
    println!("Quicksort: {:.2?} us", (end - start).as_micros());

    // Check if array is sorted.
    assert_eq!(is_sorted(&array), true);

    if verbose {
        println!("Output: {:?}", array);
    }
}

// Prints program usage.
fn usage(args: &Vec<String>) {
    println!("{} - Testing program for quicksort.", args[0]);
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
