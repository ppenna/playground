# Fila

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é uma fila?](#o-quê-é-uma-fila)
- [Onde filas são usadas?](#onde-filas-são-usadas)
- [Qual é a estrutura de uma fila?](#qual-é-a-estrutura-de-uma-fila)
- [Quais são as operações básicas de uma fila?](#quais-são-as-operações-básicas-de-uma-fila)

## O quê é uma fila?

Uma fila é uma estrutura de dados linear em que elementos são inseridos em uma extremidade (final da fila) e retirados da outra (início da fila). Por essa característica, filas também são conhecidas como estruturas FIFO (_First-In First-Out_, Primeiro a Entrar Primeiro a Sair).

Uma analogia para essa estrutura de dados são as filas de supermercado. Pessoas entram no final da fila e aguardam sua vez, enquanto pessoas do início da fila a deixam e são atendidas.

## Onde filas são usadas?

- Gerenciamento de processos em sistemas operacionais. Tarefas são adicionadas a uma fila para serem executadas e as tarefas são removidas da fila quando são concluídas.
- Transmissão de pacotes em redes de computadores. Pacotes são adicionados a uma fila para serem transmitidos e são removidos da fila quando são entregues.
- Algoritmos de busca em inteligência artificial. Estados são adicionados à fila para serem explorados e são removidos da fila quando são processados.

## Qual é a estrutura de uma fila?

Um fila `f` pode ser construída com os seguintes componentes:

- `f.celulas[]`: células que armazenam os elementos da fila.
- `f.primeiro`: um ponteiro que referencia o primeiro elemento da fila.
- `f.ultimo`: um ponteiro que referencia o último elemento da fila.
- `f.comprimento`: um inteiro que conta o número de elementos na fila.

## Quais são as operações básicas de uma fila?

- [`comprimento()` retorna o comprimento de uma fila.](#operação-comprimento)
- [`enfileirar()` insere um elemento no final de uma fila.](#operação-enfileirar)
- [`desenfileirar()` remove o elemento do início de uma fila.](#operação-desenfileirar)

### Operação Comprimento

1. Retorne o valor de `f.comprimento`.

### Operação Enfileirar

1. Atualize o ponteiro de último da fila `f.ultimo` para referenciar uma nova célula.
2. Armazene o elemento `x` na célula referenciada pelo ponteiro de último da fila `f.ultimo`.
3. Incremente em uma unidade o contador de comprimento da fila `f.comprimento`.

### Operação Desenfileirar

1. Verifique se a fila `f` está vazia. Em caso afirmativo, vá para o passo 2. Caso contrário, vá para o passo 3.
2. A fila está vazia, então retorne`"fila vazia"`.
3. Salve em `x` o elemento referenciado pelo ponteiro de primeiro da fila `f.primeiro`.
4. Atualize o ponteiro de topo da fila `f.primeiro` para referenciar a célula anterior à primeira atual da fila.
5. Decremente em uma unidade o contador de comprimento da fila `f.comprimento`.
6. Retorne o elemento `x`.
