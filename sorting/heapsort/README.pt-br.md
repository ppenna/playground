# Heapsort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O que é o Heapsort?](#o-que-é-o-heapsort)
- [Quais são as características do Heapsort?](#quais-são-as-características-do-heapsort)
- [Qual é o algoritmo de Heapsort?](#qual-é-o-algoritmo-de-heapsort)
- [Qual é o desempenho do Heapsort?](#qual-é-o-desempenho-do-heapsort)

## O que é o Heapsort?

O Heapsort (Ordenação por Heap) é um algoritmo de ordenação que utiliza uma estrutura de dados Heap Binária para ordenar um arranjo de elementos. A ideia central do algoritmo se resume a construir uma heap de máximo a partir do arranjo desordenado, e, em seguida, trocar o primeiro elemento com o último e manter a propriedade de heap máxima para os elementos restantes. Esse processo é repetido até que todos os elementos do arranjo estejam ordenados.

## Quais são as características do Heapsort?

- O Heapsort é um algoritmo iterativo.
- O Heapsort é um algoritmo de ordenação por comparação.
- O Heapsort é um algoritmo de ordenação estável.
- O desempenho do algoritmo não é sensível aos dados de entrada.

## Qual é o algoritmo de Heapsort?

1. Construa uma heap de máximo a partir do arranjo de entrada.
2. Troque do primeiro elemento com o último elemento do arranjo.
3. Corrija a propriedade de heap máximo, com os `N-1` elementos restantes no arranjo.
4. Repetição dos Passos 2 e 3 até que todos os elementos estejam ordenados. Após cada iteração, o tamanho da heap de máximo é reduzido em 1.
5. O arranjo está ordenado.

## Qual é o desempenho do Heapsort?

O desempenho do Heapsort não é impactado pela disposição inicial dos elementos no arranjo de entrada. Por esse motivo, o algoritmo apresenta um custo super-linear no pior e melhor caso, em função do comprimento `n` do arranjo de entrada:

- `O(n log₂ n)` comparações
