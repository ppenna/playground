# Algoritmo Rabin-Karp

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o Algoritmo Rabin-Karp?](#o-quê-é-o-algoritmo-rabin-karp)
- [Quais são as características do Algoritmo Rabin-Karp?](#quais-são-as-características-do-algoritmo-rabin-karp)
- [Qual é o Algoritmo Rabin-Karp?](#qual-é-o-algoritmo-rabin-karp)
- [Qual função de hash utilizar?](#qual-função-de-hash-utilizar)
- [Qual o desempenho do Algoritmo Rabin-Karp?](#qual-o-desempenho-do-algoritmo-rabin-karp)

## O quê é o Algoritmo Rabin-Karp?

O Algoritmo Rabin-Karp é um algoritmo de casamento de padrões criado por Richard Karp e Michael Rabin em 1987. Esse algoritmo funciona deslizando uma janela de comparação pelo texto de entrada e usando uma função de hash para decidir quando uma comparação entre o trecho de texto e o padrão buscado deve ser feita.

## Quais são as características do Algoritmo Rabin-Karp?

- O Algoritmo Rabin-Karp faz uma busca exata de um padrão em um texto de entrada.
- O Algoritmo Rabin-Karp funciona deslizando uma janela de comparação pelo texto de entrada.
- O Algoritmo Rabin-Karp usa uma função de hash para decidir quando comparar um trecho de texto com o padrão buscado.
- O Algoritmo Rabin-Karp não necessita de espaço de memória auxiliar para funcionar.
- O desempenho do algoritmo Rabin-Karp depende da função de hash utilizada.

## Qual é o Algoritmo Rabin-Karp?

1. Calcule o hash do padrão de buscado.
2. Divida o texto de entrada em vários trechos de texto, cada um com com o mesmo comprimento do tamanho do padrão buscado. Nessa divisão, o primeiro trecho começa no primeiro símbolo do texto de entrada, o segundo trecho no segundo símbolo, e assim por diante.
3. Para cada trecho de texto, faça:
   1. Calcule o hash do trecho de texto.
   2. Compare o hash do trecho de texto com hash do padrão buscado.
   3. Se o hash do trecho de texto e o hash do padrão buscado forem iguais, verifique se há uma correspondência real entre o trecho de texto com o padrão buscado.
   4. Em caso afirmativo, adicione o trecho de texto ao conjunto de trechos que correspondem ao padrão buscado.
4. Retorne o conjunto de trechos que correspondem ao padrão buscado. Se nenhuma correspondência foi encontrada, esse conjunto está vazio.

## Qual função de hash utilizar?

## Qual o desempenho do Algoritmo Rabin-Karp?

O desempenho do Algoritmo Rabin-Karp é impactado pela eficiência da função hash utilizada. O desejado é que essa função possua um curto de computação baixo ao mesmo tempo que gere poucas colisões, evitando assim a verificação de correspondências negativas entre o trechos de texto e o padrão buscado. Algumas funções hash para o Algoritmo Rabin-Karp popularmente usadas são:

- Função de Hash Simples: Esta função pode ser implementada como a soma dos valores ASCII dos símbolos no padrão buscado.

- Função de Hash Polinomial -- Esta função é baseada em polinômios e pode ser implementada como a soma dos produtos dos valores ASCII dos símbolos no padrão buscado por potências de uma base.

- Funções de Hash Padrão -- Funções de hash como SHA-1, SHA-256 e MD5.

### Caso Médio

O caso médio para o Algoritmo Rabin-Karp acontece quando o padrão buscado está no texto de entrada e a função de hash utilizada gera poucas colisões, evitando que verificações de correspondências falso positivas sejam feitas. Nesse cenário, o desempenho do algoritmo é linear no número de comparações, em função do comprimento `m` do texto de entrada e do comprimento `n` do padrão buscado:

- `O(m + n)` comparações

### Pior Caso

O pior caso para o Algoritmo Rabin-Karp acontece quando o padrão buscado não está no texto de entrada e a função de hash utilizada gera muitas colisões, fazendo com que uma verificação de correspondência seja feita a cada trecho de texto considerado. Nesse cenário, o desempenho do algoritmo é quadrático no número de comparações, em função do comprimento `m` do texto de entrada e do comprimento `n` do padrão buscado:

- `O(mn)` comparações
