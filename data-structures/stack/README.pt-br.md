# Pilha

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é uma pilha?](#o-quê-é-uma-pilha)
- [Onde pilhas são usadas?](#onde-pilhas-são-usadas)
- [Qual é a estrutura de uma pilha?](#qual-é-a-estrutura-de-uma-pilha)
- [Quais são as operações básicas de uma pilha?](#quais-são-as-operações-básicas-de-uma-pilha)

## O quê é uma pilha?

Uma pilha é uma estrutura de dados linear em que elementos são adicionados e retirados de uma mesma extremidade. Por essa característica, pilhas também são conhecidas como estruturas LIFO (_Last-In First-Out_, Último a Entrar Primeiro a Sair).

Uma analogia para essa estrutura de dados é uma pilha de livros. Livros são sempre colocados e retirados do topo da pilha.

## Onde pilhas são usadas?

- Desfazer e Refazer -- Pilhas são usadas em editores de texto para armazenar as ações do usuário, permitindo desfazer e refazer ações.
- Navegação de Histórico -- Pilhas são usadas para armazenar as páginas visitadas pelo usuário em um navegador web, permitindo que o usuário volte para a página anterior ao pressionar o botão "voltar".
- Algoritmos de Busca -- Pilhas são usadas em algoritmos de busca para armazenar os estados pendentes de serem explorados.
- Pilhas de Execução -- Quando uma função é chamada, os parâmetros e o endereço de retorno são empilhados na pilha. Quando a função retorna, o endereço de retorno é desempilhado e o controle é transferido de volta para a chamada anterior.

## Qual é a estrutura de uma pilha?

Um pilha `p` pode ser construída com os seguintes componentes:

- `p.celulas[]`: células que armazenam os elementos da pilha.
- `p.topo`: um ponteiro que referencia o elemento do topo da pilha.
- `p.tamanho`: um inteiro que conta o número de elementos na pilha.

## Quais são as operações básicas de uma pilha?

- [`tamanho()` retorna o número de elementos em uma pilha.](#operação-tamanho)
- [`empilhar()` insere um elemento no topo de uma pilha.](#operação-empilhar)
- [`desempilhar()` remove o elemento do topo de uma pilha.](#operação-desempilhar)

### Operação Tamanho

1. Retorne o valor de `p.tamanho`.

### Operação Empilhar

1. Atualize o ponteiro de topo da pilha `p.topo` para referenciar uma nova célula.
2. Armazene o elemento `x` na célula referenciada pelo ponteiro de topo da pilha `p.topo`.
3. Incremente em uma unidade o contador de tamanho da pilha `p.tamanho`.

### Operação Desempilhar

1. Verifique se a pilha `p` está vazia. Em caso afirmativo, vá para o Passo 2. Caso contrário, vá para o Passo 3.
2. A pilha está vazia, então retorne `"pilha vazia"`.
3. Salve em `x` o elemento referenciado pelo ponteiro de topo da pilha `p.topo`.
4. Atualize o ponteiro de topo da pilha `p.topo` para referenciar a célula abaixo do topo atual.
5. Decremente em uma unidade o contador de tamanho da pilha `p.tamanho`.
6. Retorne o elemento `x`.
