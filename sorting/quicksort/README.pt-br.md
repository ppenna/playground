# Quicksort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o _Quicksort_?](#o-quê-é-o-quicksort)
- [Quais são as características do _Quicksort_?](#quais-são-as-características-do-quicksort)
- [Qual é o algoritmo do _Quicksort_?](#qual-é-o-algoritmo-do-quicksort)
- [Qual é o desempenho do _Quicksort_?](#qual-é-o-desempenho-do-quicksort)
- [Como otimizar a implementação _Quicksort_?](#como-otimizar-a-implementação-quicksort)
- [Leitura Complementar](#leitura-complementar)

## O quê é o _Quicksort_?

O _Quicksort_ é um algoritmo de ordenação por comparação geral criado por Tony Hoare em 1959. Ele é um algoritmo de Divisão e Conquista que funciona particionando e reordenando recursivamente um arranjo de acordo com um elemento pivô.

O _Quicksort_ apresenta um desempenho marginalmente superiora outros algoritmos de ordenação por comparação, como o *Merge Sort* e o *Heap Sort*.

## Quais são as características do _Quicksort_?

- O _Quicksort_ é um algoritmo recursivo.
- O _Quicksort_ é um algoritmo de ordenação por comparação.
- O _Quicksort_ não é um algoritmo de ordenação estável.
- O desempenho do algoritmo _Quicksort_ é muito sensível aos dados de entrada.
- O _Quicksort_ não necessita de uma estrutura de dados auxiliar para funcionar.

## Qual é o algoritmo do _Quicksort_?

1. Caso o arranjo tiver menos que dois elementos, pare a recursão.
2. Selecione um elemento do arranjo e chame-o de elemento pivô.
3. Particione e reordene o arranjo em dois sub-arranjos, de forma que os elementos que forem menor do que o pivô fique antes do ponto de divisão e os elementos maiores que o pivô fiquem depois do ponto de divisão. Elementos que forem iguais ao pivô podem ser colocados em quaisquer uma das partições.
4. Recursivamente aplique os Passos 1 -- 3 nos sub-arranjos da esquerda e direita.
5. Quando a recursão parar, o arranjo está ordenado.

## Qual é o desempenho do _Quicksort_?

### Pior Caso

O pior caso do _Quicksort_ ocorre quando o arranjo de entrada já está ordenado. Nesse caso, ao fim do particionamento do particionamento os sub-arranjos podem ter tamanhos diferentes (estarem desbalanceados), fazendo com que a ordenação recursiva de um sub-arranjo leve mais tempo que a do outro. Nessa situação, o algoritmo tem um custo quadrático de comparações, em função do número de elementos a serem ordenados:

- `O(n²)` comparações

### Melhor Caso

O melhor caso do _Quicksort_ ocorre quando o arranjo de entrada está desordenado de forma randomizada. Nessa situação, o algoritmo tem um custo super-linear de comparações, em função do número de elementos a serem ordenados:

- `O(n log₂ n)` comparações

## Como otimizar a implementação _Quicksort_?

### Escolha do Elemento Pivô

O desempenho do _Quicksort_ é impactado pela forma como o elemento pivô é escolhido. Se uma escolha ruim é feita, ao fim do particionamento do particionamento os sub-arranjos podem ter tamanhos diferentes (estarem desbalanceados), fazendo com que a ordenação recursiva de um sub-arranjo leve mais tempo que a do outro. Existem três estratégias populares para a escolha do elemento pivô, cada uma com suas vantagens e desvantagens:

- Escolher o primeiro ou último elemento da partição: não adiciona nenhum sobrecusto no algoritmo, porém tende a gerar partições desbalanceadas, principalmente quando o arranjo de entrada está quase ordenado.
- Escolher o elemento do meio da partição: oferece melhor relação entre sobrecusto adicionado e melhor balanceamento entre partições.
- Escolher um elemento mediano entre três elementos quaisquer: incorre em um maior sobrecusto no algoritmo, adicionando três trocas a cada particionamento, porém produz um melhor balanceamento entre partições.

### Uso de Sentinelas

Durante o passo de particionamento é importante garantir que os elementos que estão sendo comparados estejam dentro do intervalo considerado. Caso contrário, o algoritmo não funcionará corretamente. Apesar desse detalhe de implementação poder ser resolvido com comparações adicionais na etapa de particionamento, isso incorre em um sobrecusto na execução do _Quicksort_.

Uma solução alternativa para atacar esse problema é inserir elementos sentinelas em ambos os extremos do arranjo, que por construção garantem que os elementos sempre estarão dentro do intervalo válido do arranjo. Para tanto, o elemento na extrema esquerda do arranjo pode ser substituído pelo elemento pivô, e na extrema direita pode-se adicionar um elemento que seja maior que todos os demais elementos no arranjo.

### Chamada Recursiva

Conforme o _Quicksort_ realiza chamadas recursivas, o tamanho do arranjo de trabalho diminui até ter apenas um elemento (caso base da recursão). Enquanto essa característica recursiva não é um problema em teoria, na prática ela incorre em um sobrecusto dominante no tempo de execução do algoritmo, quando o arranjo de trabalho é pequeno demais.

Uma forma de evitar esse problema é modificar a implementação original do _Quicksort_ de forma que, quando o arranjo de trabalho for pequeno, a recursão é interrompida e um algoritmo iterativo é usado. O limiar para a parada de recursão bem como algoritmo iterativo a ser utilizado dependem caso a caso. No entanto, vale considerar que popularmente utiliza-se o limiar de 10 a 20 elementos e o _Insertion Sort_ (Ordenação por Inserção) como algoritmo de ordenação.

## Leitura Complementar

- [Desenvolvendo Software | Quicksort](http://desenvolvendosoftware.com.br/algoritmos/ordenacao/quicksort.html)
