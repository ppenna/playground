# Algoritmo KMP

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o Algoritmo KMP?](#o-quê-é-o-algoritmo-kmp)
- [Quais são as características do Algoritmo KMP?](#quais-são-as-características-do-algoritmo-kmp)
- [Qual é o Algoritmo KMP?](#qual-é-o-algoritmo-kmp)
- [Qual o desempenho do Algoritmo KMP?](#qual-o-desempenho-do-algoritmo-kmp)

## O quê é o Algoritmo KMP?

O Algoritmo KMP (Knuth-Morris-Pratt) é um algoritmo de casamento de padrões criado por Donald Knuth, James Morris e Vaughan Pratt em 1970. O algoritmo possui um desempenho superior ao Algoritmo Força-Bruta, pois evita verificações redundantes ao longo da busca. Para isso, o Algoritmo KMP constrói um autômato finito determinístico capaz de reconhecer o padrão buscado e, então, simula a execução desse autômato ao longo do texto de entrada.

## Quais são as características do Algoritmo KMP?

- O Algoritmo KMP faz a busca exata de um padrão em um texto de entrada.
- O Algoritmo KMP usa um autômato finito determinístico para buscar um padrão em um texto.
- O Algoritmo KMP necessita de espaço de memória auxiliar para funcionar.
- O desempenho do algoritmo KMP é sensível ao padrão buscado.

## Qual é o Algoritmo KMP?

1. Denote `P` o padrão buscado com comprimento `k`, e `T` o texto de entrada com comprimento `m`.
2. Construa um autômato `DFA[i, j]` capaz de reconhecer o padrão buscado. Nessa estrutura auxiliar, as linhas codificam um "símbolo de entrada", colunas codificam o estado atual no autômato e os valores armazenados nas células da tabela codificam o próximo estado no autômato.
3. Inicialize como `0` o estado atual `x` no autômato `DFA`.
4. Para cada símbolo `T[i]` no texto de entrada `T` faça:
    1. Atualize o estado no autômato com base no símbolo lido: `x ← DFA[T[i], i]`
    2. Se o estado no autômato é o estado `k`, saia do laço.
5. Se o estado no autômato é o estado `k` o padrão foi encontrado. Caso contrário, o padrão não foi encontrado no texto de entrada.

### Qual é o algoritmo de construção do autômato?

1. Inicialize uma variável `x` que indica o estado de recomeço no autômato.
2. Crie uma tabela `DFA[R, k]`, que possui `R` linhas e `k` colunas, sendo `R` o número de símbolos alfabeto de busca (por exemplo letras, número e símbolos especiais para uma busca textual) e `k` o comprimento do padrão buscado.
3. Inicialize todas as entradas da tabela com `DFA[R, k]` com `x`, indicando que, qualquer descasamento entre um símbolo no padrão buscado e um símbolo no texto de entrada, o autômato recomeça de seu estado inicial.
4. Crie a transição inicial para quando o primeiro símbolo do padrão é lido:  `DFA[P[0], 0] ← 1`.
5. Para cada símbolo `P[i]` no padrão `P`, começando do segundo símbolo faça:
    1. Inicialize o estado `i` no autômato copiando a transições do estado anterior: `DFA[c, i] ← DFA[c, x]`, onde `c` são todos os símbolos em `R`.
    2. Atualize a transição do estado `i`, quando símbolo `P[i]` é lido: `DFA[P[i], i] ← i + 1`.
    3. Atualize o estado atual na construção do autômato: `x ← DFA[P[i], x]`.

## Qual o desempenho do Algoritmo KMP?

### Melhor Caso

O melhor caso para o algoritmo KMP acontece quando o padrão buscado encontra-se logo no início do texto de entrada. Nesse cenário o desempenho do algoritmo é linear no número de comparações, em função do comprimento `k` do padrão buscado:

- `O(k)` comparações

### Pior Caso

O pior caso para o Algoritmo KMP acontece quando o padrão buscado não está no texto de entrada. Nesse cenário, o desempenho do algoritmo é linear no número de comparações, em função do comprimento `k` do padrão buscado e do comprimento `m` do texto de entrada:

- `O(m + k)` comparações
