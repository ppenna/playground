# Algoritmo de

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o Algoritmo de Prim?](#o-quê-é-o-algoritmo-de-prim)
- [Quais são as características do Algoritmo de Prim?](#quais-são-as-características-do-algoritmo-de-prim)
- [Quais as aplicações do Algoritmo de Prim?](#quais-as-aplicações-do-algoritmo-de-prim)
- [Qual é o Algoritmo de Prim?](#qual-é-o-algoritmo-de-prim)
- [Qual o desempenho do Algoritmo de Prim?](#qual-o-desempenho-do-algoritmo-de-prim)

## O quê é o Algoritmo de Prim?

O Algoritmo de Prim é um algoritmo para encontrar a árvore geradora mínima em um grafo não direcionado e ponderado -- uma sub-árvore conectada do grafo original que inclui todos os vértices e tem o menor peso possível. O algoritmo funciona adicionando vértices à árvore geradora mínima um a um, até que todos os possível vértices tenham sido incluídos na sub-árvore. Em cada iteração, o algoritmo adiciona o vértice com menor peso de aresta que está conectado a um vértice na sub-árvore.

O  Algoritmo de Prim foi criado inicialmente por Vojtěch Jarník em 1930 e posteriormente republicado por Robert Prim em 1957 e Edsger Dijkstra em 1959. Por esse motivo, o algoritmo também é conhecido como Algoritmo de Jarník, Algoritmo de Prim-Jarník, Algoritmo de Prim-Dijkstra ou então Algoritmo DJP.

## Quais são as características do Algoritmo de Prim?

- O Algoritmo de Prim é um algoritmo guloso.
- O Algoritmo de Prim usa uma Heap como estrutura auxiliar.

## Quais as aplicações do Algoritmo de Prim?

- **Sistemas de Roteamento em Redes de Computadores** -- o Algoritmo de Prim pode ser usado para encontrar o caminho mais curto entre dois nós de uma rede de computadores.
- **Análise de Dados de Distância Genética** -- O Algoritmo de Prim pode ser usado para construir uma árvore filogenética que representa a relação evolutiva entre diferentes espécies ou populações com base em sua distância genética.
- **Redes de distribuição de energia elétrica** -- O Algoritmo de Prim pode ser usado para encontrar a rede de distribuição de energia elétrica mais eficiente em termos de custo e perda de energia.

## Qual é o Algoritmo de Prim?

1. Selecione um vértice inicial, adicione-o na árvore geradora mínima e marque-o como visitado.
2. Encontre a aresta de menor peso que conecta um dos vértices da árvore geradora mínima com um vértice ainda não visitado.
3. Inclua a aresta encontrada na árvore geradora mínima e marque o vértice conectado pela aresta como visitado.
4. Repita os Passos 2 e 3 até que todos os vértices do grafo estejam na árvore geradora mínima.

## Qual o desempenho do Algoritmo de Prim?

O desempenho do algoritmo de Prim depende do número de vértices `|V|` e arestas `|E|` do grafo. Em uma implementação usando uma Heap Binária, o Algoritmo de Prim possui uma complexidade de tempo super linear:

- `O((|V| + |E|) * log |V|)` comparações
