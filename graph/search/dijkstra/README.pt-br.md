# Algoritmo de Dijkstra

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o Algoritmo de Dijkstra?](#o-quê-é-o-algoritmo-de-dijkstra)
- [Quais são as características do Algoritmo de Dijkstra?](#quais-são-as-características-do-algoritmo-de-dijkstra)
- [Quais as aplicações do Algoritmo de Dijkstra?](#quais-as-aplicações-do-algoritmo-de-dijkstra)
- [Qual é o Algoritmo de Dijkstra?](#qual-é-o-algoritmo-de-dijkstra)
- [Qual o desempenho do Algoritmo de Dijkstra?](#qual-o-desempenho-do-algoritmo-de-dijkstra)

## O quê é o Algoritmo de Dijkstra?

O Algoritmo de Dijkstra é um algoritmo criado por Edsger Dijkstra em 1956, que encontra o caminho mais curto entre dois vértices em um grafo ponderado. O algoritmo funciona mantendo um conjunto de vértices não visitados e suas respectivas distâncias estimadas até o vértice de origem. Em cada passo, o algoritmo escolhe o vértice não visitado com a menor distância estimada e marca-o como visitado. Em seguida, ele atualiza as distâncias estimadas dos vértices adjacentes ao vértice atual, se a distância estimada até esses vértices através do vértice atual for menor do que a distância atualmente estimada. O algoritmo continua até que o vértice de destino seja encontrado, ou até que todos os vértices tenham sido visitados.

## Quais são as características do Algoritmo de Dijkstra?

- O Algoritmo de Dijkstra é um algoritmo guloso.
- O Algoritmo de Dijkstra usa uma Heap como estrutura auxiliar.

## Quais as aplicações do Algoritmo de Dijkstra?

- **Roteamento em Redes de Computadores** -- O Algoritmo de Dijkstra pode ser usado para encontrar o caminho mais curto entre dois pontos em uma rede, permitindo que os pacotes de dados sejam encaminhados de forma eficiente.

- **Navegação em Mapas** - O Algoritmo de Dijkstra pode ser usado para encontrar a rota mais curta entre dois pontos em um mapa, permitindo que os aplicativos de navegação forneçam direções precisas e eficientes.

- **Projeto de Circuitos Elétricos** -- O Algoritmo de Dijkstra é usado para encontrar a rota mais curta em circuitos elétricos, permitindo que os engenheiros projetem circuitos com a menor resistência possível.

- **Análise de Redes Sociais** -- O Algoritmo de Dijkstra pode ser usado para encontrar o caminho mais curto entre dois usuários em uma rede social, permitindo que as plataformas de mídia social sugiram amizades com base em interesses comuns.

## Qual é o Algoritmo de Dijkstra?

1. Inicialize todas as distâncias dos vértices como infinitas, exceto o vértice de origem, que terá distância zero. Inicialize a lista de vértices visitados como vazia.
2. Selecione o vértice não visitado com a menor distância estimada e marque-o como visitado.
3. Para cada vértice adjacente ao vértice atual, atualize a distância estimada se a distância estimada até esse vértice através do vértice atual for menor do que a distância atualmente estimada.
4. Repita o passo 2 e o passo 3 até que o vértice de destino seja visitado, ou até que todos os vértices tenham sido visitados.
5. Se o vértice de destino for visitado, o caminho mais curto é encontrado seguindo as distâncias estimadas dos vértices, a partir do destino até a origem.

## Qual o desempenho do Algoritmo de Dijkstra?

O desempenho do algoritmo de Dijkstra depende do número de vértices `|V|` e arestas `|E|` do grafo. Em uma implementação usando uma Heap Binária, o Algoritmo de Dijkstra possui uma complexidade de tempo super linear:

- `O((|V| + |E|) * log |V|)` comparações
