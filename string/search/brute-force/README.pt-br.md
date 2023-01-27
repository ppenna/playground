# Algoritmo Força-Bruta

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o Algoritmo Força-Bruta?](#o-quê-é-o-algoritmo-força-bruta)
- [Quais são as características do Algoritmo Força-Bruta?](#quais-são-as-características-do-algoritmo-força-bruta)
- [Qual é o Algoritmo Força-Bruta?](#qual-é-o-algoritmo-força-bruta)
- [Qual o desempenho do Algoritmo Força-Bruta?](#qual-o-desempenho-do-algoritmo-força-bruta)

## O quê é o Algoritmo Força-Bruta?

O Algoritmo Força-Bruta consiste em uma forma simples, ingênua e ineficiente para realizar o casamento de padrões. O algoritmo funciona deslizando uma janela de comparação no texto de entrada símbolo a símbolo e comparando se cada trecho de texto considerado corresponde ao padrão buscado.

## Quais são as características do Algoritmo Força-Bruta?

- O Algoritmo de Força-Bruta faz uma busca exata de um padrão em um texto de entrada.
- O Algoritmo de Força-Bruta funciona deslizando uma janela de comparação pelo texto de entrada.
- O Algoritmo de Força-Bruta não necessita de espaço auxiliar de memória para funcionar.
- O Algoritmo de Força-Bruta é ineficiente.
- O desempenho do Algoritmo Força-Bruta não depende do padrão buscado.

## Qual é o Algoritmo Força-Bruta?

1. Posicione a janela deslizante de comparação no primeiro símbolo do texto de entrada e inicie a busca:
   1. Compare o trecho de texto na janela deslizante com o padrão buscado, começado pelo último símbolo do padrão em direção ao primeiro.
   2. Caso algum símbolo seja diferente, avance para o próximo símbolo no texto de entrada.
   3. Caso o trecho de texto corresponda ao padrão buscado, adicione esse trecho ao conjunto de trechos encontrados e interrompa a busca.
2. Retorne o conjunto de trechos que correspondem ao padrão buscado. Se nenhuma correspondência foi encontrada, esse conjunto está vazio.

## Qual o desempenho do Algoritmo Força-Bruta?

### Melhor Caso

O melhor caso para o Algoritmo Força-Bruta para o casamento de padrões ocorre quando o padrão buscado está nas posições iniciais do texto de entrada. Nesse cenário, o desempenho do algoritmo é linear no número de comparações, em função do comprimento `n` do padrão buscado:

- `O(n)` comparações

### Pior Caso

O pior caso para o Algoritmo Força-Bruta para o casamento de padrões ocorre quando o padrão buscado não está no texto de entrada. Nesse cenário, o desempenho do algoritmo é quadrático no número de comparações, em função do comprimento `m` do texto de entrada e do comprimento `n` do padrão buscado:

- `O(mn)` comparações
