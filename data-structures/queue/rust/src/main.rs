// Copyright (C) 2023 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

use anyhow::Result;
use std::{
    alloc::{self, Layout},
    env::args,
    fmt::Debug,
    mem, ptr, slice,
    time::Instant,
};

// A queue that can grow dynamically.
struct Queue<T> {
    ptr: ptr::NonNull<T>, // Elements stored in the queue.
    length: usize,        // Current number of elements that are stored in the queue.
    capacity: usize,      // Max number of elements that can be stored in the queue.
    front: usize,         // Indexes front element in the queue.
    back: usize,          // Indexes back position in the queue.
}

impl<T: Copy> Queue<T> {
    // Initial capacity for a queue.
    const INITIAL_CAPACITY: usize = 1024;

    // Creates a new queue.
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
            front: 0,
            back: 0,
        }
    }

    // Expands the capacity of the target queue.
    fn expand(&mut self) {
        self.capacity *= 2;
        let layout: Layout = match Layout::array::<T>(self.capacity) {
            Ok(layout) => layout,
            Err(_) => {
                panic!("failed to create memory layout for raw array");
            }
        };
        self.ptr = {
            let new_size: usize = self.capacity * mem::size_of::<T>();
            let ptr: *mut u8 =
                unsafe { alloc::realloc(self.ptr.as_ptr() as *mut u8, layout, new_size) };
            match ptr::NonNull::new(ptr as *mut T) {
                Some(p) => p,
                None => alloc::handle_alloc_error(layout),
            }
        };
    }

    // Returns the number of elements that are stored in the target queue.
    pub fn length(&self) -> usize {
        self.length
    }

    // Gets an immutable reference to back position of the target queue.
    fn front(&self) -> &T {
        unsafe {
            (self.ptr.as_ptr() as *const T)
                .add(self.front)
                .as_ref()
                .unwrap()
        }
    }

    // Gets a mutable reference to the back position of the target queue.
    fn back_mut(&mut self) -> &mut T {
        unsafe { (self.ptr.as_ptr()).add(self.back).as_mut().unwrap() }
    }

    // Inserts an element in the target queue.
    pub fn push_back(&mut self, element: T) {
        // The queue is full, thus expand its capacity.
        if self.length == (self.capacity - 1) {
            self.expand();
        }

        // Insert element.
        let back: &mut T = self.back_mut();
        *back = element;
        self.back = (self.back + 1) % self.capacity;

        // Increase the length of the queue.
        self.length += 1;
    }

    // Removes an element from the target queue.
    pub fn pop_front(&mut self) -> T {
        // Empty queue.
        if self.length == 0 {
            panic!("the queue is empty")
        }

        // Remove element.
        let x: T = self.front().to_owned();
        self.front = (self.front + 1) % self.capacity;

        // Decrease the length of the queue.
        self.length -= 1;

        x
    }
}

impl<T: Debug> Debug for Queue<T> {
    // Prints the contents of the target queue.
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let slice = unsafe { slice::from_raw_parts(self.ptr.as_ptr(), self.length) };
        f.debug_struct("Queue")
            .field("capacity", &self.capacity)
            .field("length", &self.length)
            .field("elements", &slice)
            .finish()
    }
}

// Tests Queues.
fn test(length: usize, verbose: bool) {
    let mut queue: Queue<usize> = Queue::new();

    // Inserts elements in the queue.
    let start: Instant = Instant::now();
    for i in 0..length {
        queue.push_back(i);
    }
    let end: Instant = Instant::now();
    if verbose {
        println!("{:?}", queue);
    }
    println!(
        "{:>12}: {:.2?} us",
        "queue.push_back()",
        (end - start).as_micros()
    );

    assert_eq!(queue.length(), length);

    // Remove all elements from the queue.
    let start: Instant = Instant::now();
    for i in 0..length {
        assert_eq!(queue.pop_front(), i);
    }
    let end: Instant = Instant::now();
    if verbose {
        println!("{:?}", queue);
    }
    println!(
        "{:>12}: {:.2?} us",
        "queue.pop_front()",
        (end - start).as_micros()
    );
}

// Prints program usage.
fn usage(args: &Vec<String>) {
    println!("{} - Testing program for queues.", args[0]);
    println!("Usage: {} [--verbose] <queue length>", args[0]);
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
