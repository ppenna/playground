# Busca Sequencial

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é a Busca Sequencial?](#o-quê-é-a-busca-sequencial)
- [Quais são as propriedades da Busca Sequencial?](#quais-são-as-propriedades-da-busca-sequencial)
- [Qual é o algoritmo da Busca Sequencial?](#qual-é-o-algoritmo-da-busca-sequencial)
- [Qual o desempenho da Busca Sequencial?](#qual-o-desempenho-da-busca-sequencial)
- [Leitura Complementar](#leitura-complementar)

## O quê é a Busca Sequencial?

A Busca Sequencial (_Sequential Search_) ou Busca Linear (_Linear Search_) é um algoritmo de busca que encontra um elemento específico em uma lista ou arranjo, iterando por um elemento de cada vez e verificando se aquele elemento é o do elemento procurado.

## Quais são as propriedades da Busca Sequencial?

- A Busca Sequencial funciona em listas e arranjos.
- A Busca Sequencial funciona em dados não ordenados.
- A Busca Sequencial não requer uma estrutura de dados auxiliar para funcionar.
- O desempenho da Busca Sequencial é impactado pela forma como os dados de entrada estão dispostos na lista ou arranjo.

## Qual é o algoritmo da Busca Sequencial?

1. Inicialize uma variável chamada `posição` com `-1`. Essa variável será usada para armazenar a posição do elemento procurado.
2. Inicie um laço que itere através de cada elemento na lista ou arranjo.
3. Dentro do laço, compare o elemento atual com o elemento procurado.
4. Se o elemento atual for igual ao elemento procurado, defina a variável `posição` como o índice atual e saia do laço.
5. Depois que o laço terminar, verifique o elemento da variável `posição`. Se ela ainda for `-1`, o elemento não foi encontrado na lista ou arranjo. Se não for `-1`, o elemento foi encontrado na posição armazenada na variável `posição`.

## Qual o desempenho da Busca Sequencial?

### Melhor Caso

O desempenho do melhor caso para o algoritmo de Busca Sequencial acontece quando o elemento buscado está na primeira posição do arranjo ou lista de entrada. Nesse cenário, a Busca Sequencial apresenta um custo constante de comparações, em função do número de elementos `n` na lista ou arranjo de entrada:

- `O(1)` comparações

### Pior Caso

O desempenho do pior caso para o algoritmo de Busca Sequencial acontece quando o elemento buscado está na última posição do arranjo ou lista de entrada. Nesse cenário, a Busca Sequencial apresenta um custo linear de comparações, em função do número de elementos `n` na lista ou arranjo de entrada:

- `O(n)`

## Leitura Complementar

- [Wikipédia](https://pt.wikipedia.org/wiki/Busca_linear)
