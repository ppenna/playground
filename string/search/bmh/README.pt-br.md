# Algoritmo BMH

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o Algoritmo BMH?](#o-quê-é-o-algoritmo-bmh)
- [Quais são as características do Algoritmo BMH?](#quais-são-as-características-do-algoritmo-bmh)
- [Qual é o Algoritmo BMH?](#qual-é-o-algoritmo-bmh)
- [Qual o desempenho do Algoritmo BMH?](#qual-o-desempenho-do-algoritmo-bmh)

## O quê é o Algoritmo BMH?

O Algoritmo BMH, Algoritmo de Boyer-Moore-Horspool, ou ainda Algoritmo de Horspool é um algoritmo de casamento de padrões criado por Horspool em 1980. Esse algoritmo funciona deslizando uma janela de comparação pelo texto de entrada e usando uma "tabela de saltos" para decidir em quantos símbolos a janela deslizante deve ser deslocada, quando ocorre um descasamento ocorre entre um símbolo na janela deslizante o no padrão buscado. O Algoritmo BMH é uma simplificação do Algoritmo de Boyer-Moore onde utiliza-se uma tabela de saltos, ao invés de duas.

## Quais são as características do Algoritmo BMH?

- O Algoritmo BMH faz uma busca exata de um padrão em um texto de entrada.
- O Algoritmo BMH é uma simplificação do Algoritmo de Boyer-Moore
- O Algoritmo BMH funciona deslizando uma janela de comparação pelo texto de entrada.
- O Algoritmo BMH usa uma tabela de saltos para decidir em quantos símbolos a janela deslizante deve ser deslocada.
- O Algoritmo BMH necessita de espaço auxiliar de memória para funcionar.
- O desempenho do Algoritmo BMH é afetado pelo comprimento do padrão buscado.

## Qual é o Algoritmo BMH?

1. Crie uma tabela de saltos com `R` entradas, sendo `R` o número de símbolos no alfabeto considerado (por exemplo letras, números e símbolos especiais). Cada entrada nessa tabela armazena o número de símbolos que a janela deslizante deve ser deslocada adiante, quando um descasamento ocorre. Para símbolos do alfabeto que não estão no padrão de busca, esse valor deve ser o comprimento do padrão de busca. Para símbolos do alfabeto que estão no padrão de busca, esse valor deve ser o deslocamento entre a última ocorrência daquele símbolo no padrão de busca ao último símbolo no padrão de busca.
2. Posicione a janela deslizante de comparação no primeiro símbolo do texto de entrada e inicie a busca:
   1. Compare o trecho de texto na janela deslizante com o padrão buscado, começado pelo último símbolo do padrão em direção ao primeiro.
   2. Caso algum símbolo seja diferente, use a tabela de saltos para avançar no texto de entrada.
   3. Caso o trecho de texto corresponda ao padrão buscado, adicione esse trecho ao conjunto de trechos encontrados e interrompa a busca.
3. Retorne o conjunto de trechos que correspondem ao padrão buscado. Se nenhuma correspondência foi encontrada, esse conjunto está vazio.

## Qual o desempenho do Algoritmo BMH?

### Caso Médio

O caso médio para o Algoritmo BMH ocorre quando o padrão buscado está no texto de entrada e descasamentos com o trecho de texto na janela deslizante implicam em deslocamentos significantes no texto de entrada. Nesse cenário, o desempenho do algoritmo é linear no número de comparações, em função do comprimento `n` do padrão buscado:

- `O(n)` comparações

### Pior Caso

O pior caso para o Algoritmo BMH acontece quando o padrão buscado não está no texto de entrada e descasamentos com o trecho de texto na janela deslizante implicam em deslocamentos insignificantes no texto de entrada. Nesse cenário, o desempenho do algoritmo é quadrático no número de comparações, em função do comprimento `m` do texto de entrada e do comprimento `n` do padrão buscado:

- `O(mn)` comparações
