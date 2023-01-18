// Copyright (C) 2023 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

use anyhow::Result;
use rand::{
    distributions::{uniform::SampleUniform, Uniform},
    Rng, SeedableRng,
};
use rand_chacha::ChaCha20Rng;
use std::{env::args, time::Instant};

/// Sorts an array using Counting Sort.
fn counting_sort<T: Default + PartialOrd + Copy + Into<usize>>(array: &mut [T]) {
    // Find the largest key in the input array.
    let max_key: usize = {
        let mut max: usize = 0;
        for i in 1..array.len() {
            if array[i] > array[max] {
                max = i;
            }
        }
        array[max].into()
    };

    // Allocate and initialize count array with an increased
    // length by 1 to enable us to count zero frequencies as well.
    let mut count: Vec<usize> = vec![0; max_key + 1];

    // Count frequency of keys.
    for i in 0..count.len() {
        let key: usize = array[i].into();
        count[key] += 1;
    }

    // Compute prefix sum.
    for i in 1..count.len() {
        count[i] += count[i - 1];
    }

    // Sort by performing lookups in the prefix sum table.
    // Note that we traverse the input array in reverse
    // order to ensure a stable sort.
    let mut aux: Vec<T> = vec![T::default(); array.len()];
    for i in (0..array.len()).rev() {
        let key: usize = array[i].into();
        count[key] -= 1;
        aux[count[key]] = array[i];
    }

    // Reconstruct original array.
    for i in 0..array.len() {
        array[i] = aux[i]
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

/// Tests Counting Sort.
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
    counting_sort(&mut array);
    let end: Instant = Instant::now();

    // Report time.
    println!("Counting Sort: {:.2?} us", (end - start).as_micros());

    if verbose {
        println!("Output: {:?}", array);
    }

    // Check if array is sorted.
    assert_eq!(is_sorted(&array), true);
}

// Prints program usage.
fn usage(args: &Vec<String>) {
    println!("{} - Testing program for counting sort.", args[0]);
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
