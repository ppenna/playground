# Queue

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Read this in other languages: [English](README.md), [Português](README.pt-br.md)_

- [What is a queue?](#what-is-a-queue)
- [Where are queues used?](#where-are-queues-used)
- [How to implement a queue?](#how-to-implement-a-queue)
- [What are the basic operations of a queue?](#what-are-the-basic-operations-of-a-queue)

## What is a queue?

A queue is a linear data structure in which elements are inserted at one end (the back of the queue) and removed from the other (the front of the queue). Due to this characteristic, queues are also known as FIFO (First-In First-Out) structures.

An analogy for this data structure is a grocery store queue. People enter the line at the end and wait their turn, while people at the front of the line leave and are served.

## Where are queues used?

- Process management in operating systems. Tasks are added to a queue to be executed and tasks are removed from the queue when they are completed.
- Packet transmission in computer networks. Packets are added to a queue to be transmitted and are removed from the queue when they are delivered.
- Search algorithms in artificial intelligence. States are added to the queue to be explored and are removed from the queue when they are processed.

## How to implement a queue?

A queue `q` can be built with the following components:

`q.cells[]`: cells that store the elements of the queue.
`q.first`: a pointer that references the first element of the queue.
`q.last`: a pointer that references the last element of the queue.
`q.length`: an integer that counts the number of elements in the queue.

## What are the basic operations of a queue?

- [`length()` returns the length of a queue.](#length-operation)
- [`enqueue()` inserts an element at the end of a queue.](#enqueue-operation)
- [`dequeue()` removes the element from the beginning of a queue.](#dequeue-operation)

### Length Operation

1. Return the value of `q.length`.

### Enqueue Operation

1. Update the last pointer of the queue `q.last` to reference a new cell.
2. Store the element `x` in the cell referenced by the last pointer of the queue `q.last.
3. Increment by one the length counter of the queue q.length.

### Dequeue Operation

1. Check if the queue `q` is empty. If affirmative, go to step 2. Otherwise, go to step 3.
2. The queue is empty, so return `"empty queue"`.
3. Save in `x` the element referenced by the first pointer of the queue `q.first`.
4. Update the first pointer of the queue `q.first` to reference the cell before the current first of the queue.
5. Decrement by one the length counter of the queue `q.length`.
6. Return the element `x`.
