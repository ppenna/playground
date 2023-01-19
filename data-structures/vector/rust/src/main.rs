// Copyright (C) 2023 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

use anyhow::Result;
use std::{
    alloc::{self, Layout},
    env::args,
    fmt::Debug,
    ops::{Index, IndexMut},
    ptr, slice,
    time::Instant,
};

// A dynamic array with bound checking.
struct Vector<T> {
    ptr: ptr::NonNull<T>, // Elements stored in the vector.
    length: usize,        // Current number of elements that are stored in the vector.
    capacity: usize,      // Max number of elements that can be stored in the vector.
}

impl<T: Copy> Vector<T> {
    // Initial capacity for a vector.
    const INITIAL_CAPACITY: usize = 1024;

    // Creates a new vector.
    pub fn new() -> Self {
        // Allocate underlying memory.
        let layout: Layout = match Layout::array::<T>(Self::INITIAL_CAPACITY) {
            Ok(layout) => layout,
            Err(_) => {
                panic!("failed to create memory layout for raw array");
            }
        };
        let ptr: ptr::NonNull<T> = {
            let ptr: *mut u8 = unsafe { alloc::alloc(layout) };
            match ptr::NonNull::new(ptr as *mut T) {
                Some(p) => p,
                None => alloc::handle_alloc_error(layout),
            }
        };

        // Initialize data structure.
        Self {
            capacity: Self::INITIAL_CAPACITY,
            length: 0,
            ptr,
        }
    }

    // Returns the number of elements that are stored in a vector.
    pub fn length(&self) -> usize {
        self.length
    }

    // Expands the capacity of the target vector.
    fn expand(&mut self) {
        self.capacity *= 2;
        let layout: Layout = match Layout::array::<T>(self.capacity) {
            Ok(layout) => layout,
            Err(_) => {
                panic!("failed to create memory layout for raw array");
            }
        };
        self.ptr = {
            let ptr: *mut u8 =
                unsafe { alloc::realloc(self.ptr.as_ptr() as *mut u8, layout, self.capacity) };
            match ptr::NonNull::new(ptr as *mut T) {
                Some(p) => p,
                None => alloc::handle_alloc_error(layout),
            }
        };
    }

    // Inserts an element in a specific position of a vector.
    pub fn insert(&mut self, index: usize, element: T) {
        // The vector is full, thus expand its capacity.
        if self.length == self.capacity {
            self.expand();
        }

        // Increase the size of the vector.
        self.length += 1;

        // Shift right elements.
        for i in ((index + 1)..self.length).rev() {
            self[i] = self[i - 1];
        }

        // Insert the element in the specified position.
        self[index] = element;
    }

    // Removes an element from a vector.
    pub fn remove(&mut self, index: usize) -> T {
        // Out of bounds.
        if index >= self.length {
            panic!("{:?} is out of the bounds of the vector", index)
        }

        let x: T = self[index];

        // Shift right elements.
        for i in index..self.length - 1 {
            self[i] = self[i + 1];
        }

        // Decrease the size of the vector.
        self.length -= 1;

        x
    }
}

impl<T> Index<usize> for Vector<T> {
    type Output = T;

    // Gets an immutable reference to an element in a vector.
    fn index(&self, index: usize) -> &Self::Output {
        if index >= self.length {
            panic!("{:?} is out of the bounds of the vector", index)
        }
        unsafe { (self.ptr.as_ptr() as *const T).add(index).as_ref().unwrap() }
    }
}

impl<T> IndexMut<usize> for Vector<T> {
    // Gets a mutable reference to an element in a vector.
    fn index_mut(&mut self, index: usize) -> &mut Self::Output {
        if index >= self.length {
            panic!("{:?} is out of the bounds of the vector", index)
        }
        unsafe { (self.ptr.as_ptr()).add(index).as_mut().unwrap() }
    }
}

impl<T: Debug> Debug for Vector<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let slice = unsafe { slice::from_raw_parts(self.ptr.as_ptr(), self.length) };
        f.debug_struct("Vector")
            .field("capacity", &self.capacity)
            .field("length", &self.length)
            .field("elements", &slice)
            .finish()
    }
}

// Tests Vectors.
fn test(length: usize, verbose: bool) {
    let mut v: Vector<usize> = Vector::new();

    assert_eq!(v.length(), 0);

    // Inserts elements in the vector.
    let start: Instant = Instant::now();
    for i in 0..length {
        v.insert(i, i + 1);
    }
    let end: Instant = Instant::now();
    if verbose {
        println!("{:?}", v);
    }
    println!(
        "{:>18}: {:.2?} us",
        "vector.insert()",
        (end - start).as_micros()
    );

    assert_eq!(v.length(), length);

    // Get all elements in the vector.
    let start: Instant = Instant::now();
    for i in 0..length {
        assert_eq!(v[i], (i + 1));
    }
    let end: Instant = Instant::now();
    if verbose {
        println!("{:?}", v);
    }
    println!(
        "{:>18}: {:.2?} us",
        "vector.index()",
        (end - start).as_micros()
    );

    // Replace all elements in the vector.
    let start: Instant = Instant::now();
    for i in 0..length {
        v[i] = 0;
    }
    let end: Instant = Instant::now();
    if verbose {
        println!("{:?}", v);
    }
    println!(
        "{:>18}: {:.2?} us",
        "vector.index_mut()",
        (end - start).as_micros()
    );

    // Remove all elements from the vector.
    let start: Instant = Instant::now();
    for _ in 0..length {
        v.remove(0);
    }
    let end: Instant = Instant::now();
    if verbose {
        println!("{:?}", v);
    }
    println!(
        "{:>18}: {:.2?} us",
        "vector.remove()",
        (end - start).as_micros()
    );

    assert_eq!(v.length(), 0);
}

// Prints program usage.
fn usage(args: &Vec<String>) {
    println!("{} - Testing program for vectors.", args[0]);
    println!("Usage: {} [--verbose] <vector length>", args[0]);
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
