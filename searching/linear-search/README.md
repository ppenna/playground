# Linear Search

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Read this in other languages: [English](README.md), [Português](README.pt-br.md)_

- [About](#about)
- [Properties](#properties)
- [Algorithm](#algorithm)
- [Performance](#performance)
- [Further Reading](#further-reading)

## About

Linear Search or Sequential search is a search algorithm that finds a particular
element in an input list or array by iterating through each element one at a
time and checking if it is the element searched for.

## Properties

- Linear Search works on lists and arrays.
- Linear Search works on unordered data.
- Linear Search does not require auxiliary data structures to work.
- The performance of Linear Search is impacted by how the input data is layout
on the list or array.

## Algorithm

1. Initialize a variable called `position` to `-1`. This variable will be used
to store the position of the element being searched for.
2. Enter a loop that iterates through each element in the list or array.
3. In the loop, compare the current element with the element being searched for.
4. If the current element is equal to the element being searched for, set the
`position` variable to the current index and break out of the loop.
5. After exiting the loop, check the element of the `position` variable. If it
is still `-1`, the element was not found in the list or array. If it is not
`-1`, the element was found at the position stored in the `position` variable.

## Performance

### Best-Case

The best-case performance for Linear Search happens when the element being
searched for is at the first position in the input list or array. In this
scenario, Linear Search presents a takes a constant number of comparisons, in
respect to the number of elements `n` in the input list or array:

- `O(1)` comparisons

### Worst-Case

The worst-case performance for Linear Search happens when the element being
search for is at the first position in the input array or list. In this
scenario, Linear Search takes a linear number of comparisons, in respect to the
number of elements `n` in the input list or array:

- `O(n)` comparisons

## Further Reading

- [Wikipedia](https://en.wikipedia.org/wiki/Linear_search)
