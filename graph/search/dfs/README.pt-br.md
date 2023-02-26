# Busca em Profundidade

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é a Busca em Profundidade?](#o-quê-é-a-busca-em-profundidade)
- [Quais são as características da Busca em Profundidade?](#quais-são-as-características-da-busca-em-profundidade)
- [Quais as aplicações da Busca em Profundidade?](#quais-as-aplicações-da-busca-em-profundidade)
- [Qual é o algoritmo de Busca em Profundidade?](#qual-é-o-algoritmo-de-busca-em-profundidade)
- [Qual o desempenho da Busca em Profundidade?](#qual-o-desempenho-da-busca-em-profundidade)

## O quê é a Busca em Profundidade?

A Busca em Profundidade (DFS -- _Depth-First Search_) é um algoritmo de busca em grafos. Esse algoritmo explora um grafo a partir de um nó inicial, usando uma pilha para processar os nós não visitados.

## Quais são as características da Busca em Profundidade?

- A Busca em Profundidade é um algoritmo de busca não informada, uma vez que não usa nenhuma informação para direcionar a busca.
- A Busca em Profundidade não garante que a solução encontrada seja a melhor possível.
- A Busca em Profundidade utiliza uma pilha para rastrear o nós que precisam ser visitados.
- A Busca em Profundidade pode ser mais eficiente em termos de espaço de memória do que outros algoritmos de busca, como a Busca em Largura.

## Quais as aplicações da Busca em Profundidade?

- **Realizar a Ordenação Topológica de Grafos** -- A Busca em Profundidade pode ser usada para realizar a ordenação topológica de um grafo direcionado e acíclico, isto é listar os nós do grafo de forma que suas dependências sejam respeitadas.

- **Verificar Conexão em Grafos** -- A Busca em Profundidade pode ser usada para verificar se dois nós de um grafo estão conectados e, caso estejam, encontrar o caminho que os conecta.

- **Encontrar Componentes Conectados em Grafos** -- A Busca em Profundidade pode ser usada para encontrar todas os componentes conectados em um grafo não direcionado.

- **Detectar Ciclos em Grafos** -- A Busca em Profundidade pode ser usada detectar ciclos em um grafo direcionado.

## Qual é o algoritmo de Busca em Profundidade?

1. Inicialize uma pilha com o nó inicial e marque-o como visitado.
2. Enquanto a pilha não estiver vazia:
   1. Remova o nó do topo da pilha e verifique se ele é o objetivo.
   2. Em caso afirmativo, retorne o caminho até ele.
   3. Caso contrário, adicione todos os nós não visitados adjacentes na pilha e marque-os como visitados.
3. Se a pilha estiver vazia e o objetivo não tiver sido encontrado, retorne `"sem solução"`.

## Qual o desempenho da Busca em Profundidade?

A Busca em Profundidade possui uma complexidade linear de tempo e espaço, em função do número de nós `|V|` e arestas `E` do grafo:

- Complexidade de Tempo: `O(|V| + |E|)`
- Complexidade de Espaço: `O(|V|)`

Alternativamente, quando o grafo de busca é muito grande, a complexidade de tempo e espaço da BUsca em Profundidade é escrita em função do número do fator de ramificação do grafo `b` (_branch factor_) e a distância `d` do nó inicial ao nó objetivo, e possui uma complexidade exponencial:

- Complexidade de Tempo: `O(bᵈ)`
- Complexidade de Espaço: `O(bd)`
