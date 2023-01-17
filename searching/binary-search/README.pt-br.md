# Busca Binária

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é a Busca Binária?](#o-quê-é-a-busca-binária)
- [Quais são as características da Busca Binária?](#quais-são-as-características-da-busca-binária)
- [Qual é o algoritmo da Busca Binária?](#qual-é-o-algoritmo-da-busca-binária)
- [Qual o desempenho da Busca Binária?](#qual-o-desempenho-da-busca-binária)
- [Leitura Complementar](#leitura-complementar)

## O quê é a Busca Binária?

A Busca Binária (_Binary Search_) é um algoritmo de busca que procura por um elemento desejado em um arranjo ordenado. O algoritmo funciona dividindo o arranjo no meio repetidamente e comparando o elemento no meio com o elemento procurado. Se o elemento procurado for menor que o elemento no meio, então uma busca recursiva é feita na metade inferior do arranjo. Se o elemento procurado for maior que o elemento no meio, então uma busca recursiva é feia na metade superior do arranjo. Esse processo continua, até que o elemento desejado seja encontrado ou então não haja mais elementos para serem pesquisados.

## Quais são as características da Busca Binária?

- A Busca Binária é um algoritmo de Divisão e Conquista.
- A Busca Binária funciona apenas em arranjos ordenados.
- A Busca Binária não requer uma estrutura de dados auxiliar para funcionar.

## Qual é o algoritmo da Busca Binária?

1. Inicialmente, considere como intervalo de busca todo o arranjo de entrada.
2. Caso o intervalo de busca for vazio, pare. O elemento desejado não está no arranjo de entrada.
3. Compare o elemento desejado com o elemento do meio no intervalo de busca.
4. Se o elemento desejado for o que estiver no meio do intervalo de busca, pare. O elemento desejado foi encontrado.
5. Senão, se o elemento desejado for menor que o elemento no meio do intervalo de busca, considere o intervalo à esquerda do elemento do meio como o novo intervalo de busca e faça uma busca nesse novo intervalo (vá para o Passo 2).
6. Senão, se o elemento desejado for maior que o elemento no meio do intervalo de busca, considere o intervalo à direita do elemento do meio como novo intervalo de busca e faça uma busca nesse novo intervalo (vá para o Passo 2).

## Qual o desempenho da Busca Binária?

### Melhor Caso

O melhor caso do algoritmo de Busca Binária ocorre quando o elemento procurado é o primeiro elemento considerado. Nesse cenário, o algoritmo tem um custo constante de comparações, em função do número de elementos `n` no arranjo:

- `O(1)` comparações

### Pior Caso

O pior caso do algoritmo de Busca Binária ocorre quando o elemento procurado não está presente no arranjo de entrada. Nesse cenário, o algoritmo tem um custo logarítmico de comparações, em função do número elementos `n` no arranjo:

- `O(log₂ n)` comparações

## Leitura Complementar

- [Wikipédia](https://pt.wikipedia.org/wiki/Pesquisa_bin%C3%A1ria)
