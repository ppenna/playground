# Bubble Sort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o _Bubble Sort_?](#o-quê-é-o-bubble-sort)
- [Quais são as características do _Bubble Sort_?](#quais-são-as-características-do-bubble-sort)
- [Qual é o algoritmo do _Bubble Sort_?](#qual-é-o-algoritmo-do-bubble-sort)
- [Qual é o desempenho do _Bubble Sort_?](#qual-é-o-desempenho-do-bubble-sort)
- [Leitura Complementar](#leitura-complementar)

## O quê é o _Bubble Sort_?

O _Bubble Sort_ (Ordenação por Bolha) é um algoritmo de ordenação que funciona trocando repetidamente de posição, os elementos adjacentes em um arranjo que estão fora de ordem entre si. O algoritmo leva esse nome por "borbulhar" os maiores elementos para o final do arranjo.

O _Bubble Sort_ apresenta um desempenho ruim, quando comparado à outros algoritmos de ordenação. No entanto, por ser de simples compreensão, é frequentemente usado para motivar o estudo de outros algoritmos de ordenação.

## Quais são as características do _Bubble Sort_?

- O _Bubble Sort_ é um algoritmo iterativo.
- O _Bubble Sort_ é um algoritmo de ordenação por comparação.
- O _Bubble Sort_ é um algoritmo de ordenação estável.
- O desempenho do algoritmo não é sensível aos dados de entrada.

## Qual é o algoritmo do _Bubble Sort_?

1. Percorra a o arranjo de entrada, do início ao fim.
2. Para cada elemento considerado, verifique se o elemento subsequente no arranjo é menor.
3. Em caso afirmativo, troque os dois elementos de posição no arranjo.
4. Ao terminar de percorrer o arranjo, verifique se algum elemento trocou de posição. Em caso afirmativo, volte ao Passo 1.
5. O arranjo está ordenado.

## Qual é o desempenho do _Bubble Sort_?

O _Bubble Sort_ não é um algoritmo de ordenação indicado para a ordenação de grandes conjuntos de dados.

### Pior Caso

O pior caso para o algoritmo _Bubble Sort_ ocorre quando o arranjo de entrada está ordenado de forma inversa. Nessa situação, o algoritmo tem um custo quadrático de comparações e trocas, em função do número de elementos a serem ordenados:

- `O(n²)` comparações
- `O(n²)` trocas

### Melhor Caso

O melhor caso para o algoritmo _Bubble Sort_ ocorre quando o arranjo de entrada já está ordenado. Nessa situação, o algoritmo tem um custo linear de comparações e um custo constante de trocas, em função do número de elementos a serem ordenados:

- `O(n)` comparações
- `O(1)` trocas

## Leitura Complementar

- [Desenvolvendo Software | Bubble Sort](http://desenvolvendosoftware.com.br/algoritmos/ordenacao/bubble-sort.html)
