# Interpolation Search

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Read this in other languages: [English](README.md), [Português](README.pt-br.md)_


## What is the Interpolation Search?

Interpolation Search is a search algorithm created by William Wesley Peterson in 1957 that can search for a specific element in an ordered array. The algorithm consists of a variation of the Binary Search algorithm, using an interpolation technique to reduce the number of iterations required to find the desired element. The interpolation method used can take into account the characteristics of the data in the search array, but often a linear interpolation method is chosen.

## When to use Interpolation Search?

- Interpolation Search is indicated when it is known that there is a uniform distribution of elements in the search array. In this case, the average performance of the algorithm is `O(log₂ (log₂ n))` where n is the length of the search array.

## What are the characteristics of Interpolation Search?

- Interpolation Search is a variation of Binary Search.
- Interpolation Search only works on ordered arrays.
- The performance of Interpolation Search is sensitive to the elements in the search array.

## What is the Interpolation Search algorithm?

1. Initially, consider the entire search array as the search interval.
2. If the search interval is empty, stop. The desired element is not in the search array.
3. Estimate the position of the desired element using an interpolation method (e.g. linear interpolation).
4. Compare the desired element with the element at the interpolated position.
5. If the desired element is the one at the interpolated position, stop. The desired element has been found.
6. Otherwise, if the desired element is greater than the element at the interpolated position, consider the interval to the left of the element at the interpolated position as the new search interval and search in this new interval (go to Step 2).
7. Otherwise, if the desired element is less than the element at the interpolated position, consider the interval to the right of the element at the interpolated position as the new search interval and search in this new interval (go to Step 2).

## What is the performance of Interpolation Search?

### Best-Case

The best-case of the Interpolation Search algorithm occurs when the sought element is the first element considered. In this scenario, the algorithm has a constant cost of comparisons:

- `O(1)` comparisons

## Worst-Case

The worst-case of the Interpolation Search algorithm occurs when the search array does not have a uniform distribution of elements. In this scenario, the algorithm has a linear cost of comparisons, depending on length of the search array:

- `O(n)` comparisons

## Further Reading

- [Wikipedia](https://en.wikipedia.org/wiki/Interpolation_search)
