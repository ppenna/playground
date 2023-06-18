// Copyright (C) 2023 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#![cfg_attr(feature = "strict", deny(clippy:all))]

use anyhow::Result;
use std::{env::args, fmt::Debug};

//==============================================================================
// Disjoint Set
//==============================================================================

/// A disjoint set of sets.
///
/// This implementation uses the tree-based representation and the union-find
/// algorithm. Weighted-union (union-by-size) and path compression heuristics
/// are used to improve performance.
#[derive(Debug)]
struct DisjointSet {
    /// Elements.
    elements: Vec<usize>,
    /// Weight of elements.
    weights: Vec<usize>,
}

impl DisjointSet {
    /// Creates a disjoint set.
    pub fn new(size: usize) -> Self {
        let mut elements: Vec<usize> = Vec::<usize>::with_capacity(size);
        let mut weights: Vec<usize> = Vec::<usize>::with_capacity(size);

        // Initialize.
        for i in 0..size {
            elements.push(i);
            weights.push(1);
        }

        Self { elements, weights }
    }

    /// Finds the representative element of set in a disjoint set.
    pub fn find(&mut self, mut p: usize) -> usize {
        // Sanity check arguments
        assert!(p < self.elements.len());

        // Traverse set.
        while p != self.elements[p] {
            // Path compression.
            self.elements[p] = self.elements[self.elements[p]];

            // Move to next element.
            p = self.elements[p];
        }

        // Found.
        p
    }

    /// Merges two sets of a disjoint set.
    pub fn union(&mut self, p: usize, q: usize) -> usize {
        // Sanity check arguments.
        assert!(p < self.elements.len());
        assert!(q < self.elements.len());

        // Find representatives elements of each set.
        let mut p_set: usize = self.find(p);
        let mut q_set: usize = self.find(q);

        // Merge sets.
        if p_set != q_set {
            // Weighted-union heuristic: link the representative element of the
            // smaller set  to the representative element of the larger set.
            if self.weights[p_set] > self.weights[q_set] {
                std::mem::swap(&mut p_set, &mut q_set);
            }
            self.elements[p_set] = q_set;
            self.weights[q_set] += self.weights[p_set];
        }

        q_set
    }
}

//==============================================================================
// Test
//==============================================================================

/// Drives tests on a disjoint set.
fn test(size: usize, verbose: bool) {
    // Create disjoint set.
    let mut dset: DisjointSet = DisjointSet::new(size);
    if verbose {
        println!("{:?}", dset);
    }

    // Merge even sets.
    for i in (2..size).step_by(2) {
        dset.union(0, i);
    }
    if verbose {
        println!("{:?}", dset);
    }

    // Sanity check result.
    for i in (0..size).step_by(2) {
        assert_eq!(dset.find(0), dset.find(i));
    }

    // Merge odd sets.
    for i in (1..size).step_by(2) {
        dset.union(1, i);
    }
    if verbose {
        println!("{:?}", dset);
    }

    // Sanity check result.
    for i in (1..size).step_by(2) {
        assert_eq!(dset.find(1), dset.find(i));
    }

    // Merge even and odd set.
    dset.union(0, 1);
    if verbose {
        println!("{:?}", dset);
    }

    // Sanity check result.
    for i in 0..size {
        assert_eq!(dset.find(0), dset.find(i));
    }
}

//==============================================================================
// Usage
//==============================================================================

// Prints program usage.
fn usage(args: &Vec<String>) {
    println!("{} - Testing program for disjoint sets.", args[0]);
    println!("Usage: {} [--verbose] <length>", args[0]);
}

//==============================================================================
// Main
//==============================================================================

/// Test program.
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
