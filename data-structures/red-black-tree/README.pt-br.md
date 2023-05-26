# Árvore Vermelha-Preta

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é uma Árvore AVL?](#o-quê-é-uma-árvore-avl)
- [Onde Árvores AVL são usadas?](#onde-árvores-avl-são-usadas)
- [Qual é a estrutura de uma Árvore AVL?](#qual-é-a-estrutura-de-uma-árvore-avl)
- [Quais são as operações básicas de uma Árvore AVL?](#quais-são-as-operações-básicas-de-uma-árvore-avl)

## O quê é uma Árvore Vermelha-Preta?

Uma Árvore Vermelha-Preta (_Red-Black Tree_), também conhecida como Árvore RB, é uma estrutura de dados não linear em forma de árvore binária auto-balanceável. Essa estrutura assinala uma cor (vermelha ou preta) e garante que um conjunto de propriedades seja mantido a cada operação na árvore. Árvores Vermelha-Preta foram propostas por Rudolf Bayer em 1972 e suportam de forma eficiente as operações de busca, inserção e remoção.

## Onde Árvores Vermelha-Preta são usadas?

- **Implementações de Mapas e Dicionários** - As árvores vermelha-preta podem ser usadas para implementar estruturas de dados de mapas e dicionários, onde pares chave-valor são armazenados e recuperados de forma eficiente. Essas estruturas permitem a busca rápida de elementos com base em uma chave e fornecem operações eficientes de inserção e remoção.

- **Bancos de Dados** - As árvores vermelha-preta podem ser usadas em índices de bancos de dados para acelerar a busca e recuperação de informações. Elas permitem que as consultas sejam otimizadas e reduzem o número de operações de acesso a disco necessárias para recuperar dados específicos.

- **Sistemas de Arquivos** - As árvores vermelha-preta podem ser usadas em sistemas de arquivos para organizar e indexar a estrutura de diretórios e arquivos. Isso permite uma busca eficiente de arquivos e diretórios com base em seus nomes ou outros atributos.

- **Compiladores e Interpretadores** - As árvores vermelha-preta podem ser usadas em compiladores e interpretadores para otimizar a pesquisa e recuperação de símbolos, como variáveis, funções e classes, durante o processo de análise e execução de código.

- **Gerenciamento de Memória** - As árvores vermelha-preta podem ser utilizadas em sistemas de gerenciamento de memória para alocar e liberar blocos de memória de forma eficiente. Elas permitem a busca rápida de blocos de memória disponíveis para alocação e mantêm uma estrutura balanceada para evitar fragmentação excessiva.

## Quais são as propriedades de uma Árvore Vermelha-Preta?

- **Propriedade de coloração**: todo nó é vermelho ou preto.
- **Propriedade de raiz**: A raiz é sempre preta.
- **Propriedade de folhas nulas**: todas as folhas nulas são consideradas pretas.
- **Propriedade de corredor**: se um nó é vermelho, então seus filhos são pretos.
- **Propriedade de caminho**: todos os caminhos da raiz até as folhas nulas têm o mesmo número de nós pretos.

## Qual é a estrutura de uma Árvore Vermelha-Preta?

Uma Árvore Vermelha-Preta `t` pode ser construída recursivamente com os seguintes componentes:

- `t.elemento`: uma célula que armazena o elemento em um nó da árvore.
- `t.esquerda`: um ponteiro para a subárvore da esquerda.
- `t.direita`: um ponteiro para a subárvore da direita.
- `t.cor`: armazena a cor do nó da árvore.

## Quais são as operações básicas de uma Árvore Vermelha-Preta?

- `inserir()` insere um novo elemento à Árvore Vermelha-Preta, mantendo as propriedades da árvore, incluindo o balanceamento.

- `remover()` remove um elemento específico da Árvore Vermelha-Preta, garantindo que as propriedades da árvore sejam preservadas.

- `buscar()`  procura por um elemento específico na Árvore Vermelha-Preta com base em uma chave ou valor..

### Operação Inserir

1. Insira o nó como em uma árvore de busca binária:
   - Percorra a árvore a partir da raiz até encontrar a posição adequada para inserir o novo nó, levando em consideração as chaves:
   - Se a chave já estiver presente na árvore, a inserção não é permitida (a menos que a árvore permita chaves duplicadas) e o algoritmo é encerrado.
   - Insira o novo nó na posição adequada, mantendo a propriedade de árvore de busca binária.

2. Recolora e rotacione para manter as propriedades da árvore vermelha-preta:
   - Verifique e corrija as violações das propriedades da árvore vermelha-preta que podem ter surgido após a inserção do novo nó.
   - Caso 1: O novo nó é a raiz da árvore. Nesse caso, apenas marque o nó como preto.
   - Caso 2: O pai do novo nó é preto. Nesse caso, não há violação, e a árvore continua válida.
   - Caso 3: O pai do novo nó é vermelho, e o tio do novo nó também é vermelho. Nesse caso, ocorre uma violação da propriedade de cor, e é necessário realizar recolorir e rotacionar para corrigir a violação.
   - Caso 4: O pai do novo nó é vermelho, e o tio do novo nó é preto (ou ausente). Nesse caso, ocorre uma violação da propriedade de cor, e é necessário realizar recolorir e rotacionar para corrigir a violação.

3. Atualizar a raiz. Após as correções, certifique-se de que a raiz da árvore seja preta. Se necessário, atualize a cor da raiz para preto.

### Operações Remover

1. Encontre o nó a ser removido:
   - Percorra a árvore a partir da raiz até encontrar o nó que contém a chave a ser removida.
   - Se o nó não for encontrado, a remoção não é possível, e o algoritmo é encerrado.

2. Remova o nó como em uma árvore de busca binária:
   - Se o nó a ser removido não possui filhos ou possui apenas um filho, remova o nó e ajuste os ponteiros para manter a estrutura correta da árvore.
   - Se o nó a ser removido possui dois filhos, encontre o seu sucessor ou predecessor (o menor elemento maior que o nó ou o maior elemento menor que o nó, respectivamente).
   - Substitua o valor do nó a ser removido pelo valor do sucessor ou predecessor.
   - Remova recursivamente o sucessor ou predecessor de sua posição original na árvore.

3. Corrija violações das propriedades da árvore vermelha-preta:
   - Se o nó removido for preto e seu filho (ou sucessor/predecessor) também for preto, ocorrerá uma violação das propriedades da árvore vermelha-preta.
   - Caso 1: O nó removido era a raiz da árvore. Nesse caso, simplesmente marque a nova raiz como preta.
   - Caso 2: O irmão do nó removido é vermelho. Nesse caso, realize uma rotação para corrigir a violação.
   - Caso 3: O irmão do nó removido é preto e seus filhos também são pretos. Nesse caso, recoloque a cor do irmão para vermelho e mova o problema para o pai do nó removido.
   - Caso 4: O irmão do nó removido é preto, o filho esquerdo do irmão é vermelho e o filho direito do irmão é preto. Nesse caso, realize uma rotação para corrigir a violação.
   - Caso 5: O irmão do nó removido é preto e o filho direito do irmão é vermelho. Nesse caso, realize uma rotação para corrigir a violação.

4. Atualize a raiz. Após as correções, certifique-se de que a raiz da árvore seja preta. Se necessário, atualize a cor da raiz para preto.

### Operação Buscar

1. Comece na raiz da árvore.

2. Compare a chave de busca com a chave do nó atual:
   - Se forem iguais, o nó foi encontrado. A busca é concluída.
   - Se a chave de busca for menor que a chave do nó atual, vá para o filho esquerdo.
   - Se a chave de busca for maior que a chave do nó atual, vá para o filho direito.

4. Se o filho correspondente for um nó nulo, a busca termina sem encontrar o nó desejado.

5. Se ainda não encontrou o nó, repita os passos 2 e 3 a partir do filho correspondente até encontrar o nó desejado ou chegar a um nó nulo.
