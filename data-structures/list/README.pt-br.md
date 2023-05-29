# Lista Singularmente Encadeada

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O Quê São Listas Singularmente Encadeadas?](#o-quê-são-listas-singularmente-encadeadas)
- [Como Implementar Uma Lista Singularmente Encadeada?](#como-implementar-uma-lista-singularmente-encadeada)
- [Quais São As Operações Básicas de Uma Lista Singularmente Encadeadas?](#quais-são-as-operações-básicas-de-uma-lista-singularmente-encadeadas)

## O Quê São Listas Singularmente Encadeadas?

Uma lista singularmente encadeada, ou lista encadeada simples, é um tipo de [lista encadeada](/estruturas-de-dados/listas-encadeadas.html) onde suas células são encadeadas em apenas um sentido. Consequentemente, esse tipo de lista não suporta de forma eficiente a navegabilidade reversa, nem a inserção e remoção de elementos antecessores a um outro na lista.

## Como Implementar Uma Lista Singularmente Encadeada?

- `l.celulas[]`: células que armazenam os elementos da lista singularmente encadeada.
- `l.ultimo`: um ponteiro que referencia o último elemento da lista singularmente encadeada.
- `l.comprimento`: um inteiro que conta o número de elementos na lista singularmente encadeada.

## Quais São As Operações Básicas de Uma Lista Singularmente Encadeadas?

- [`inserir-sucessor()` insere um elemento como sucessor de outro em uma lista singularmente encadeada.](#operação-inserir-sucessor)
- [`remover-sucessor()` remove o sucessor de um elemento em uma lista singularmente encadeada.](#operação-remover-sucessor)

### Operação Inserir Sucessor

1. Crie uma nova célula `q` na lista `l`.
2. Armazene o elemento `e` na célula `q`.
3. Encadeie o sucessor de `p` como o sucessor de `q`.
4. Encadeie `q` como o sucessor de `p`.
5. Incremente em uma unidade o contador de comprimento da lista `l.comprimento`.
6. Se `q` é a última célula da lista `l`, atualize `l.ultimo` para referenciar `q`.

### Operação Remover Sucessor

1. Verifique se a lista `l` está vazia. Em caso afirmativo, vá para o passo 2. Caso contrário, vá para o passo 3.
2. A lista está vazia, então retorne `"lista vazia"`.
3. Salve em `q` uma referência para o sucessor de `p`.
4. Salve em `e` o elemento armazenado em `q`.
5. Encadeie o sucessor de `q` como sucessor de `p`.
6. Decremente em uma unidade o contador de comprimento da lista `l.comprimento`.
7. Se `p` é a última célula da lista `l`, atualize `l.ultimo` para referenciar `p`.
8. Retorne o elemento `e`.
