# Heap Binária

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é uma Heap Binária?](#o-quê-é-uma-heap-binária)
- [Onde Heaps Binárias são usadas?](#onde-heaps-binárias-são-usadas)
- [Qual é a estrutura de uma Heap Binária?](#qual-é-a-estrutura-de-uma-heap-binária)
- [Quais são as operações básicas de uma Heap Binária?](#quais-são-as-operações-básicas-de-uma-heap-binária)

## O quê é uma Heap Binária?

Uma Heap Binária é uma estrutura de dados não linear que implementa uma fila de prioridades usando uma árvore binária completa. Nessa estrutura, cada elemento possui no máximo dois elementos filhos, e o elemento raiz da heap é o maior ou menor elemento de todos, no caso de uma heap de máximo ou de mínimo, respectivamente.

## Onde Heaps Binárias são usadas?

- **Algoritmos de de Ordenação** -- Uma Heap Binária é usada para implementar o algoritmo de ordenação Heapsort.
- **Roteamento em Grafos** -- Uma Heap Binária é usada para encontrar o caminho mais curto entre dois nós em um grafo, como no Algoritmo de Dijkstra.
- **Gerenciamento de Recursos** -- Heaps Binários podem ser usados para gerenciar recursos, como memória ou processos, garantindo que as solicitações com a maior prioridade sejam atendidas primeiro.
- **Bancos de Dados** -- Heaps Binários são usados em bancos de dados para implementar índices, otimizar consultas de busca e garantir a consistência de dados em operações de atualização.

## Qual é a estrutura de uma Heap Binária?

Uma Heap Binária `h` pode ser construída com os seguintes componentes:

- `h.celulas[]`: células que armazenam os elementos da heap binária.
- `h.comprimento`: um inteiro que conta o número de elementos na heap binária.

## Quais são as operações básicas de uma Heap Binária?

- [`comprimento()` retorna o comprimento de uma heap binária.](#operação-comprimento)
- [`inserir()` insere um elemento na heap binária.](#operação-inserir)
- [`remover-raiz()` remove o maior/menor elemento da heap binária.](#operação-remover-raiz)

### Operação Comprimento

1. Retorne o valor de `h.comprimento`.

### Operação Inserir

1. Adicionar o novo elemento na folha mais à direita na última camada da árvore.
2. Comparar o valor do novo elemento com o valor do seu pai. Se o valor do novo elemento é menor que o valor do pai em uma heap de mínimo, ou se o valor do novo elemento é maior que o valor do pai em uma heap de máximo, troque os dois valores.
3. Repita o Passo 2 com o novo elemento até que ele esteja na posição correta na árvore, satisfazendo as propriedades de uma heap binária.

### Operação Remover Raiz

> O algoritmo para remover o elemento raiz também é conhecido como "extrair o mínimo" ou "extrair o máximo", em uma heap binária de mínimo ou de máximo, respectivamente.

1. Armazene o valor da raiz em uma variável `x`.
2. Substitua o valor da raiz com o valor da folha mais à direita na última camada da árvore.
3. Compare o valor do nó com os valores de seus filhos. Se o valor do nó é maior que o valor de algum de seus filhos em uma heap de mínimo, ou se o valor do nó é menor que o valor de algum de seus filhos em uma heap de máximo, troque o valor do nó com o valor do filho de maior prioridade.
4. Repita o Passo 3 até que o nó esteja na posição correta na árvore, satisfazendo as propriedades de uma heap binária.
5. Retorne o valor armazenado em `x`.

#### Heap Mediana

> Segue o seguinte problema para ilustrar uma aplicação de Heaps Binárias:
> Crie um tipo de dado que ofereça operações de inserção em tempo logarítmico, encontrar-a-mediana em tempo constante, e remover-a-mediana em tempo logarítmico. Se o número de chaves no tipo de dado for par, encontre/remova a menor mediana.
> Como solução, mantenha duas Heaps Binárias, uma que retorna o maior elemento, e outra que retorna o menor elemento. Se o elemento a inserir for maior do que a mediana, insira no Min Heap. Caso contrário, insira no Max Heap. Se o tamanho do Min Heap for maior do que o Max Heap, remova um elemento do Min Heap e insira no Max Heap. Se o tamnho do Max Heap for maior do que o do Min Heap + 1, remova um elemento do Max Heap e insira no Min Heap.
