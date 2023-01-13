# Insertion Sort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Read this in other languages: [English](README.md), [Português](README.pt-br.md)_

Insertion sort is a comparison sorting algorithm that works similar to the way
that some people sort cards in a bridge hand. When a new card should be inserted
in the bridge hand, the player compares that new card with the others, to
determine the right point of insertion.

## Algorithm

1. Partition the input array in two: (i) a sub-array $A$ that initially contains
only the first element of the input array; and (ii) a sub-array $B$ that
initially contains all the remainder elements.
2. Take the first element of sub-array $B$ and call it $x$.
3. Search the sub-array $A$ for the insertion point for $x$, from right to left.
4. Shift one position to the right, all elements in the sub-array $A$ that are
left to the of the insertion point.
5. Insert $x$ in the insertion position in $A$.
6. If sub-array $B$ is not empty, go to Step 2.
7. Return sub-array $A$, which contains all elements from the original array
sorted.

## Performance

- Best-Case: $O(n)$ comparisons, $O(1)$ trocas.
- Worst-Case: $O(n^2)$ comparisons, $O(n^2)$ swaps.

## Further Reading

- [Desenvolvendo Software](http://desenvolvendosoftware.com.br/algoritmos/ordenacao/insertion-sort.html)
- [Wikipédia](https://en.wikipedia.org/wiki/Insertion_sort)
