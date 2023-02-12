# Busca em Largura

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é a Busca em Largura?](#o-quê-é-a-busca-em-largura)
- [Quais são as características da Busca em Largura?](#quais-são-as-características-da-busca-em-largura)
- [Quais as aplicações da Busca em Largura?](#quais-as-aplicações-da-busca-em-largura)
- [Qual é o algoritmo de Busca em Largura?](#qual-é-o-algoritmo-de-busca-em-largura)
- [Qual o desempenho da Busca em Largura?](#qual-o-desempenho-da-busca-em-largura)

## O quê é a Busca em Largura?

A Busca em Largura (BFS -- _Breadth-First Search_) é um algoritmo de busca em grafos. Esse algoritmo funciona explorando o grafo em níveis, a partir de um nó inicial, usando uma fila do tipo primeiro a entrar, primeiro a sair.

## Quais são as características da Busca em Largura?

- A Busca em Largura possibilita encontrar a menor distância, em número de arestas, entre dois nós de um grafo.
- A Busca em Largura é um algoritmo de busca não informada, uma vez que não usa nenhuma informação para direcionar a busca.
- Busca em Largura é ineficiente em grafos grandes ou profundos.

## Quais as aplicações da Busca em Largura?

- **Encontrar a menor Rota em Um Grafo** -- A Busca em Largura pode ser usada para encontrar a rota mais curta entre dois nós de um grafo.

- **Verificar Conexão em Grafos**: A Busca em Largura pode ser usada para verificar se dois nós estão conectados em um grafo e, se estiverem, encontrar o caminho de conexão.

- **Encontrar Componentes Conectados em Um Grafo** -- A Busca em Largura pode ser usada para encontrar todas os componentes conectados em um grafo não direcionado.

- **Resolução de Problemas** -- A Busca em Largura é usada como uma técnica de busca para resolver problemas, como encontrar a solução para um quebra-cabeça ou encontrar o objetivo em um jogo.

## Qual é o algoritmo de Busca em Largura?

1. Inicialize uma fila com o nó inicial e marque-o como visitado.
2. Enquanto a fila não estiver vazia:
   1. Remova o nó da frente da fila e verifique se ele é o objetivo.
   2. Em caso afirmativo, retorne o caminho até ele.
   3. Caso contrário, adicione todos os seus nós não visitados adjacentes na fila e marque-os como visitados.
3. Se a fila estiver vazia e o objetivo não tiver sido encontrado, retorne `"sem solução"`.

## Qual o desempenho da Busca em Largura?

A Busca em Largura possui uma complexidade linear de tempo e espaço, em função do seu número de nós `|V|`  e arestas `|E|`:

- Complexidade de Tempo: `O(|V| + |E|)`
- Complexidade de Espaço: `O(|V|)`

Alternativamente, quando o grafo de busca é muito grande, a complexidade de tempo e espaço da Busca em Largura é escrita em função do número do fator de ramificação do grafo `b` (_branch factor_) e a distância `d` do nó inicial ao nó objetivo, e possui uma complexidade exponencial:

- Complexidade de Tempo: `O(bᵈ)`
- Complexidade de Espaço: `O(bᵈ)`
