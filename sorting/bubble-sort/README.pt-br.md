# Bubble Sort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

O _Bubble Sort_ (Ordenação por Bolha) é um algoritmo de ordenação que funciona
trocando repetidamente de posição, os elementos adjacentes em um arranjo que
estão fora de ordem entre si. O algoritmo leva esse nome por "borbulhar" os
maiores elementos para o final do arranjo.

O _Bubble Sort_ apresenta um desempenho ruim, quando comparado à outros
algoritmos de ordenação. No entanto, por ser de simples compreensão, é
frequentemente usado para motivar o estudo de outros algoritmos de ordenação.

## Algoritmo

1. Percorra a o arranjo de entrada, do início ao fim.
2. Para cada elemento considerado, verifique se o elemento subsequente no
arranjo é menor.
3. Em caso afirmativo, troque os dois elementos de posição no arranjo.
4. Ao terminar de percorrer o arranjo, verifique se algum elemento trocou de
posição. Em caso afirmativo, volte ao Passo 1.
5. O arranjo está ordenado.

## Desempenho

- Melhor Caso: $O(n^2)$ comparações, $O(1)$ trocas
- Pior Caso: $O(n^2)$ comparações, $O(n^2)$ trocas

## Leitura Complementar

- [Desenvolvendo Software](http://desenvolvendosoftware.com.br/algoritmos/ordenacao/bubble-sort.html)
- [Wikipédia](https://pt.wikipedia.org/wiki/Bubble_sort)
