# Busca Exponencial

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é a Busca Exponencial?](#o-quê-é-a-busca-exponencial)
- [Quando usar a Busca Exponencial?](#quando-usar-a-busca-exponencial)
- [Quais são as características da Busca Exponencial?](#quais-são-as-características-da-busca-exponencial)
- [Qual é o algoritmo da Busca Exponencial?](#qual-é-o-algoritmo-da-busca-exponencial)
- [Qual é o desempenho da Busca Exponencial?](#qual-é-o-desempenho-da-busca-exponencial)
- [Leitura Complementar](#leitura-complementar)

## O quê é a Busca Exponencial?

A Busca Exponencial (_Exponential Search_) é um algoritmo de busca criado por Jon Bentley e Andrew Chi-Chih Yao em 1976 que é capaz de procurar um elemento em um arranjo ordenado ilimitado (um arranjo que possui o limite superior desconhecido). O algoritmo consiste em uma combinação dos algoritmos de Busca Sequencial e Busca Binária, usando o primeiro algoritmo para restringir o espaço de busca e o segundo algoritmo para efetivamente procurar o elemento desejado.

## Quando usar a Busca Exponencial?

- A Busca Exponencial deve ser usada quando deseja-se fazer uma busca em um arranjo ordenado ilimitado (o limite superior do arranjo é desconhecido).
- A Busca exponencial é indicada quando estima-se que o elemento buscado está próximo do início do arranjo. Nesse caso, o desempenho médio do algoritmo é de `O(log₂ i)`, onde `i` é a posição do elemento buscado no arranjo de entrada.

## Quais são as características da Busca Exponencial?

- A Busca Exponencial é um algoritmo híbrido, que combina a Busca Sequencial e a Busca Binária.
- A Busca Exponencial funciona apenas em arranjos ordenados.
- A Busca Exponencial funciona em arranjos ilimitados.
- O desempenho da Busca Exponencial é muito sensível ao elemento buscado.

## Qual é o algoritmo da Busca Exponencial?

1. Defina a variável inicial `i` como `1` e `n` como o comprimento do arranjo.
2. Enquanto `i` for menor que `n` e o elemento no índice `i` for menor que o elemento procurado, dobre o valor de `i`.
3. Execute uma busca binária no intervalo de `i/2` até `min(n, i)`.
4. Retorne o resultado da busca binária.

## Qual é o desempenho da Busca Exponencial?

### Melhor Caso

O melhor caso do algoritmo de Busca Exponencial ocorre quando o elemento procurado é o primeiro elemento considerado. Nesse cenário, o algoritmo tem um custo constante de comparações:

- `O(1)` comparações

### Pior Caso

O pior caso do algoritmo de Busca Exponencial ocorre quando o elemento procurado não está presente no arranjo de entrada. Nesse cenário, o algoritmo tem um custo logarítmico de comparações, em função do número elementos `n` no arranjo:

- `O(log₂ n)` comparações

## Leitura Complementar

- [Wikipédia](https://pt.wikipedia.org/wiki/Busca_exponencial)
