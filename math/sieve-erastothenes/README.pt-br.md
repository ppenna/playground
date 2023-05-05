# Sieve of Eratosthenes

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o _KNN_?](#o-quê-é-o-knn)
- [Quais são as características do _KNN_?](#quais-são-as-características-do-knn)
- [Quais as aplicações do _KNN_?](#quais-as-aplicações-do-knn)
- [Quais são os passos do algoritmo _KNN_?](#quais-são-os-passos-do-algoritmo-knn)
- [Como melhorar a precisão do algoritmo _KNN_](#como-melhorar-a-precisão-do-algoritmo-knn)
- [Qual o desempenho do _KNN_?](#qual-o-desempenho-do-knn)

## O quê é o _Crivo de Eratóstenes_?

O _Crivo de Eratóstenes_ é um método antigo e simples para encontrar todos os números primos menores que um determinado número natural. Esse método foi desenvolvido pelo matemático grego Eratóstenes de Cirene por volta do século III a.C. O algoritmo funciona de forma iterativamente removendo todos os números compostos do intervalo.

## Quais são as características do _Crivo de Eratóstenes_?

- O _Crivo de Eratóstenes_ encontra todos os número primos em um intervalo.
- O _Crivo de Eratóstenes_ é um algoritmo determinístico.
- O _Crivo de Eratóstenes_ requer um espaço de memória auxiliar para funcionar.

## Quais as aplicações do _Crivo de Eratóstenes_?

- **Algoritmos de Criptografia** - Alguns sistemas criptográficos modernos, como o RSA, dependem da dificuldade de fatorar números grandes em seus fatores primos. O _Crivo de Eratóstenes_ pode ser usado para gerar uma lista de números primos que podem ser usados como base para a geração de chaves criptográficas.
- **Algoritmos de Fatoração** - Alguns algoritmos de fatoração, como o método da fatoração por tentativa, dependem da verificação de primalidade dos números para identificar seus fatores primos. O _Crivo de Eratóstenes_ pode ser usado para gerar uma lista de números primos que podem ser usados para acelerar a fatoração desses números.
- **Algoritmos de Geração de Números Aleatórios** - Alguns algoritmos de geração de números aleatórios dependem da geração de números primos aleatórios. O Crivo de Eratóstenes pode ser usado para pré-computar uma lista de números primos e, em seguida, selecionar um número aleatório dessa lista para uso em algoritmos de geração de números aleatórios.

## Quais são os passos do _Crivo de Eratóstenes_?

1. Inicie com uma lista de números inteiros de 2 até o limite máximo desejado.
2. Marque o número 2 como primo e circule-o na lista.
3. Para cada número não marcado na lista, identifique-o como primo e circule-o, em seguida, marque todos os seus múltiplos como compostos (não primos) riscando-os da lista.
4. Continue o processo até que todos os números na lista tenham sido marcados como primos ou compostos.
5. A lista final conterá apenas os números primos menores que o limite máximo desejado.

## Qual o desempenho do _Crivo de Eratóstenes_?

O desempenho do _Crivo de Eratóstenes_ depende do limite máximo desejado para a lista de primos. O algoritmo tem complexidade de `O(n log log n)`, onde n é o limite máximo desejado.
