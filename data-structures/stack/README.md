# Stack

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Read this in other languages: [English](README.md), [Português](README.pt-br.md)_

- [What is a stack?](#what-is-a-stack)
- [Where are stacks used?](#where-are-stacks-used)
- [How to implement a stack?](#how-to-implement-a-stack)
- [What are the basic operations in stacks?](#what-are-the-basic-operations-in-stacks)

## What is a stack?

A stack is a linear data structure in which elements are added and removed from the same end. Because of this characteristic, stacks are also known as LIFO (Last-In First-Out) structures.

An analogy for this data structure is a stack of books. Books are always placed and removed from the top of the stack.

## Where are stacks used?

- Undo and Redo -- Stacks are used in text editors to store user actions, allowing for undoing and redoing actions.
- Navigation History -- Stacks are used to store the pages visited by the user in a web browser, allowing the user to go back to the previous page when the "back" button is pressed.
- Search Algorithms -- Stacks are used in search algorithms to store pending states to be explored.
- Execution Stacks -- When a function is called, the parameters and the return address are pushed onto the stack. When the function returns, the return address is popped and control is transferred back to the previous call.

## How to implement a stack?

A stack `s` can be constructed with the following components:

- `s.cells[]`: cells that store the elements of the stack.
- `s.top`: a pointer that references the top element of the stack.
- `s.size`: an integer that counts the number of elements in the stack.

## What are the basic operations in stacks?

- [`size()` returns the number of elements in a stack.](#size-operation)
- [`push()` inserts an element on top of a stack.](#push-operation)
- [`pop()` removes the top element of a stack.](#pop-operation)

### Size Operation

1. Return the value of `p.size`.

### Push Operation

1. Update the top pointer of stack `s.top` to reference a new cell.
2. Store the element `x` in the cell referenced by the top pointer of stack `s.top`.
3. Increment the size counter of stack `s.size` by one.

### Pop Operation

1. Check if stack `s` is empty. If yes, go to Step 2. Otherwise, go to Step 3.
2. The stack is empty, so return `"empty stack"`.
3. Save in x the element referenced by the top pointer of stack `s.top`.
4. Update the top pointer of stack `s.top` to reference the cell below the current top.
5. Decrement the size counter of stack `s.size` by one.
6. Return element `x`.
