# Bubble Sort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Read this in other languages: [English](README.md), [Português](README.pt-br.md)_

Bubble Sort is a sorting algorithm that works by repeatedly swapping pair of
adjacent elements in the input array that are relatively out-of-order. The
algorithm takes this name for the way that large elements "bubble up" to the end
of the array.

Bubble Sort presents a poor performance, when compared to other sorting
algorithms. Still, it is simple to understand and thus it is often used to motivate
the study of other sorting algorithms.

## Performance

- Best-Case: $O(n^2)$ comparisons, $O(1)$ swaps
- Worst-Case: $O(n^2)$ comparisons, $O(n^2)$ swaps

## Algorithm

1. Traverse the input array, from the begin towards the end.
2. For each element that is considered, check if the following element is a smaller one.
3. If that is the case, swap the two elements.
4. When done traversing the array, check if any pair of elements were swapped.
If that is the case, go back to Step 1.
5. The array is sorted.


## Further Reading

- [Desenvolvendo Software](http://desenvolvendosoftware.com.br/algoritmos/ordenacao/bubble-sort.html) (Portuguese)
- [Wikipedia](https://en.wikipedia.org/wiki/Bubble_sort)
