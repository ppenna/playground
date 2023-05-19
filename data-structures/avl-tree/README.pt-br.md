# Árvore AVL

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é uma Árvore AVL?](#o-quê-é-uma-árvore-avl)
- [Onde Árvores AVL são usadas?](#onde-árvores-avl-são-usadas)
- [Qual é a estrutura de uma Árvore AVL?](#qual-é-a-estrutura-de-uma-árvore-avl)
- [Quais são as operações básicas de uma Árvore AVL?](#quais-são-as-operações-básicas-de-uma-árvore-avl)

## O quê é uma Árvore AVL?

Uma Árvore AVL é estrutura de dados não linear em forma de uma árvore binária de busca auto-balanceável. Ela mantém as alturas das subárvores da esquerda e da direita equilibradas re-organizando os nós da árvore após inserções e remoções, caso necessário. Essa estrutura de dados foi criada por Georgy Adelson-Velsky e Evgenii Landis em 1962 e suporta de forma eficiente operações de busca, inserção e remoção.

## Onde Árvores AVL são usadas?

- **Bancos de Dados** - Árvores AVL podem usadas na implementação de índices em bancos de dados, permitindo uma busca rápida e eficiente pelos registros.

- **Sistemas de Busca** - Árvores AVL podem ser usadas para organizar e buscar informações de maneira eficiente, em motores de busca e sistemas de indexação.

- **Sistemas de Arquivos** - Árvores AVL podem ser usadas para indexar e localizar arquivos de maneira eficiente, em sistemas de arquivos que exigem rápida busca e recuperação de informações.

## Qual é a estrutura de uma Árvore AVL?

Uma Árvore AVL `t` pode ser construída recursivamente com os seguintes componentes:

- `t.elemento`: uma célula que armazena o elemento em um nó da árvore.
- `t.esquerda`: um ponteiro para a subárvore AVL da esquerda.
- `t.direita`: um ponteiro para a subárvore AVL da direita.

## Quais são as operações básicas de uma Árvore AVL?

- `inserir()` insere um novo elemento na Árvore AVL.
- `remover()` remove um elemento da Árvore AVL.
- `buscar()` procura um elemento específico na Árvore AVL.
- `rotacionar()` rebalanceia elementos de uma Árvore AVL.

### Operação Inserir

1. Realize uma inserção padrão de um novo nó na posição adequada da árvore, de acordo com a chave do nó a ser inserido, como em uma árvore binária de busca.
2. Percorra a árvore a partir do ponto de inserção até o nó raiz, atualizando as alturas dos nós e verificando se algum nó se tornou desbalanceado.
4. Se um nó desbalanceado for encontrado durante o caminho de volta, realize as rotações necessárias para reequilibrar a árvore.
5. Ao finalizar o processo, a árvore estará balanceada.

### Operação Remover

1. Realize a remoção padrão do nó desejado da árvore.
2. Percorra a árvore a partir do ponto de remoção até o nó raiz, atualizando as alturas dos nós e verificando se algum nó se tornou desbalanceado.
3. Se um nó desbalanceado for encontrado durante o caminho de volta, realize as rotações necessárias para reequilibrar a árvore.
4. Ao finalizar o processo, a árvore estará balanceada.

### Operação Buscar

1. Comece pela raiz da árvore.
2. Compare a chave do nó atual com a chave que está sendo buscada.
3. Se a chave do nó atual for igual à chave buscada, o nó foi encontrado e a busca é concluída.
4. Se a chave buscada for menor que a chave do nó atual, vá para a subárvore esquerda e repita o passo 2.
5. Se a chave buscada for maior que a chave do nó atual, vá para a subárvore direita e repita o passo 2.
6. Se não houver mais nós para explorar (chegar a uma folha) e a chave buscada não for encontrada, a busca é concluída e a chave não está presente na árvore.

### Operação Rotacionar

1. Identifique o tipo de desbalanceamento na árvore AVL.

2. Realize a rotação necessária para reequilibrar a árvore de acordo com o tipo de desbalanceamento identificado:

   - Rotação Simples á Esquerda: a altura da subárvore esquerda é maior que a altura da subárvore direita, e o novo nó é inserido na subárvore esquerda dessa subárvore.

   - Rotação Simples à Direita: a altura da subárvore direita é maior que a altura da subárvore esquerda, e o novo nó é inserido na subárvore direita dessa subárvore.

   - Rotação Dupla à Esquerda: a altura da subárvore esquerda é maior que a altura da subárvore direita, e o novo nó é inserido na subárvore direita dessa subárvore.

   - Rotação Dupla à Direita: a altura da subárvore direita é maior que a altura da subárvore esquerda, e o novo nó é inserido na subárvore esquerda dessa subárvore.

#### Rotação Simples à Esquerda

1. Identifique como "A" o nó desbalanceado que precisa ser rotacionado.
2. Identifique como "B" o nó filho à direita de "A".
3. Identifique como "C" o filho à esquerda de "B".
4. Faça a rotação simples à esquerda:
   1. Faça o filho à direita de "A" apontar para "C".
   2. Faça o filho à esquerda de "B" apontar para "A".
   3. Faça "B" se tornar o novo nó raiz da subárvore onde "A" estava localizado.

#### Rotação Simples à Direita

1. Identifique como "A" o nó desbalanceado que precisa ser rotacionado.
2. Identifique como "B" o nó filho à esquerda de "A".
3. Identifique como "C" o filho à direita de "B".
4. Faça a rotação simples à esquerda:
   1. Faça o filho à esquerda de "A" apontar para "C".
   2. Faça o filho à direita de "B" apontar para "A".
   3. Faça "B" se tornar o novo nó raiz da subárvore onde "A" estava localizado.

#### Rotação Dupla à Esquerda

1. Identifique como "A" o nó desbalanceado que precisa ser rotacionado.
2. Identifique como "B" o nó filho à direita de "A".
3. Faça uma rotação simples à direita em "B".
4. Faça uma rotação simples à esquerda em "A".

#### Rotação Dupla à Direita

1. Identifique como "A" o nó desbalanceado que precisa ser rotacionado.
2. Identifique como "B" o nó filho à direita de "A".
3. Faça uma rotação simples à esquerda em "B".
4. Faça uma rotação simples à direita em "A".
