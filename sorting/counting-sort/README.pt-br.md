# Counting Sort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

O _Counting Sort_ (Ordenação por Contagem) é um algoritmo de ordenação de
inteiros criado por Harold Seward em 1954. Ele é um algoritmo de Programação
Dinâmica, que funciona construindo um histograma cumulativo das chaves do
arranjo de entrada e o usa para construir um arranjo de saída ordenado.

Em sua definição clássica, o _Counting Sort_ assume que as chaves do arranjo
possuem valores positivos e que o valor da maior chave é conhecido de antemão. O
_Counting Sort_ é geralmente usado como sub-rotina em outros métodos de
ordenação não comparativos, como o _Radix Sort_ e o _Bucket Sort_.

## Algoritmo

1. Construa o histograma cumulativo das chaves do arranjo de entrada. Nessa
estrutura de dados auxiliar, a primeira classe dá a frequência das chaves de
valor 0, a segunda classe dá a frequência das chaves de valor 1 mais o valor da
classe anterior, e assim por diante.
2. Construa um arranjo de saída ordenado usando o histograma cumulativo para
determinar a posição correta dos elementos. Por exemplo, se $x$ é um elemento do
arranjo de entrada, $x$ possui uma chave $k$, e $h(k) é a frequência cumulativa
para a chave $k$, então $x$ deve ser colocado no arranjo de saída na posição
$[h(k), h(k+1))$.

## Desempenho

- Melhor Caso: $O(n + k)$
- Pior Caso: $O(n + k)$

## Leitura Complementar

- [Desenvolvendo Software](http://desenvolvendosoftware.com.br/algoritmos/ordenacao/counting-sort.html)
- [Wikipédia](https://pt.wikipedia.org/wiki/Counting_sort)
