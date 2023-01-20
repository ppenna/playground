// Copyright (C) 2023 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

use anyhow::Result;
use std::{
    alloc::{self, Layout},
    env::args,
    fmt::Debug,
    mem, ptr, slice,
    time::Instant,
};

// A stack that can grow dynamically.
struct Stack<T> {
    ptr: ptr::NonNull<T>, // Elements stored in the stack.
    length: usize,        // Current number of elements that are stored in the stack.
    capacity: usize,      // Max number of elements that can be stored in the stack.
}

impl<T: Copy> Stack<T> {
    // Initial capacity for a stack.
    const INITIAL_CAPACITY: usize = 1024;

    // Creates a new stack.
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

    // Expands the capacity of the target stack.
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

    // Returns the number of elements that are stored in the target stack.
    pub fn length(&self) -> usize {
        self.length
    }

    // Gets an immutable reference to the top element of the target stack.
    pub fn top(&self) -> &T {
        // Empty stack.
        if self.length == 0 {
            panic!("cannot top() an empty stack")
        }

        unsafe {
            (self.ptr.as_ptr() as *const T)
                .add(self.length - 1)
                .as_ref()
                .unwrap()
        }
    }

    // Gets a mutable reference to the top element in the target stack.
    pub fn top_mut(&mut self) -> &mut T {
        // Empty stack.
        if self.length == 0 {
            panic!("cannot top_mut() an empty stack")
        }

        unsafe { (self.ptr.as_ptr()).add(self.length - 1).as_mut().unwrap() }
    }

    // Inserts an element in the target stack.
    pub fn push(&mut self, element: T) {
        // The stack is full, thus expand its capacity.
        if self.length == self.capacity {
            self.expand();
        }

        // Increase the size of the stack.
        self.length += 1;

        // Insert element.
        let top: &mut T = self.top_mut();
        *top = element;
    }

    // Removes an element from the target stack.
    pub fn pop(&mut self) -> T {
        // Empty stack.
        if self.length == 0 {
            panic!("cannot pop() an empty stack")
        }

        // Remove element.
        let x: T = self.top().to_owned();

        // Decrease the size of the stack.
        self.length -= 1;

        x
    }
}

impl<T: Debug> Debug for Stack<T> {
    // Prints the contents of the target stack.
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let slice = unsafe { slice::from_raw_parts(self.ptr.as_ptr(), self.length) };
        f.debug_struct("Stack")
            .field("capacity", &self.capacity)
            .field("length", &self.length)
            .field("elements", &slice)
            .finish()
    }
}

// Tests Stacks.
fn test(length: usize, verbose: bool) {
    let mut stack: Stack<usize> = Stack::new();

    // Inserts elements in the stack.
    let start: Instant = Instant::now();
    for i in 0..length {
        stack.push(i);
    }
    let end: Instant = Instant::now();
    if verbose {
        println!("{:?}", stack);
    }
    println!(
        "{:>12}: {:.2?} us",
        "stack.push()",
        (end - start).as_micros()
    );

    assert_eq!(stack.length(), length);

    // Remove all elements from the stack.
    let start: Instant = Instant::now();
    for i in (0..length).rev() {
        assert_eq!(stack.pop(), i);
    }
    let end: Instant = Instant::now();
    if verbose {
        println!("{:?}", stack);
    }
    println!(
        "{:>12}: {:.2?} us",
        "stack.pop()",
        (end - start).as_micros()
    );
}

// Prints program usage.
fn usage(args: &Vec<String>) {
    println!("{} - Testing program for stacks.", args[0]);
    println!("Usage: {} [--verbose] <stack length>", args[0]);
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
