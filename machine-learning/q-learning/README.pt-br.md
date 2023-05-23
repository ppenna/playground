# Q-Learning

## O quê é o Q-Learning?

O Q-Learning é um algoritmo de aprendizado por reforço (_reinforcement learning_) proposto por Christopher Watkins em 1989. Esse algoritmo aprende a tomar decisões interagindo diretamente com o ambiente, sem a necessidade de conhecimento prévio ou de supervisão humana. Por esse motivo, o Q-Learning é amplamente aplicado na resolução de problemas complexos e dinâmicos.

O algoritmo Q-Learning funciona mantendo uma tabela chamada de tabela `Q`, onde cada entrada representa um par estado-ação e contém um valor chamado de Q-valor, que indica a qualidade (ou utilidade) esperada de escolher uma ação em um determinado estado. Durante o treinamento, o agente explora o ambiente, atualiza a tabela `Q` e ajusta os valores com base nas recompensas recebidas.

O processo de aprendizado do Q-Learning é iterativo e segue uma fórmula de atualização conhecida como a equação de Bellman. Essa equação permite ao agente atualizar os Q-valores com base nas recompensas imediatas e nas estimativas de Q-valor do próximo estado. Gradualmente, o agente aprende a melhor ação a ser tomada em cada estado, maximizando a recompensa cumulativa ao longo do tempo.

## Quais as principais características do algoritmo Q-Learning?

- **Aprendizado off-policy** - O Q-learning é um algoritmo off-policy, o que significa que o agente aprende uma política ótima enquanto explora o ambiente de maneira aleatória ou seguindo uma política diferente da política atual. Isso permite que o agente aprenda uma política ótima mesmo durante a exploração inicial.

- **Estratégia de exploração e explotação** - O Q-learning utiliza uma estratégia epsilon-greedy para equilibrar a exploração (realizar ações aleatórias para descobrir o ambiente) e a explotação (selecionar ações com base nos Q-valores aprendidos). Isso permite que o agente descubra novas ações e, ao mesmo tempo, maximize suas recompensas de acordo com o conhecimento atual.

- **Aprendizado baseado em Q-valores** - O Q-learning é um algoritmo baseado em valores. Um Q-valor é atribuído a cada par estado-ação e ele representa a "qualidade" ou a "utilidade" esperada de executar uma determinada ação em um determinado estado.

- **Atualização iterativa dos Q-valores** - O algoritmo Q-learning atualiza iterativamente os Q-valores com base nas recompensas recebidas e nas transições de estado. Ele utiliza a equação de atualização do Q-valor, que combina a recompensa imediata, o Q-valor do próximo estado e um fator de desconto para ponderar as recompensas futuras.

- **Armazenamento da Q-função** - O Q-learning requer o armazenamento da Q-função, que pode ser representada em uma tabela ou em uma estrutura de dados equivalente. No entanto, em problemas com espaços de estados e ações grandes, técnicas de aproximação de função, como redes neurais, são frequentemente utilizadas para lidar com a complexidade computacional e espacial.

## Quais são as aplicações do algoritmo Q-Learning?

- **Jogos** - O Q-Learning pode ser aplicado em jogos para treinar agentes de inteligência artificial capazes de aprender a tomar decisões e melhorar seu desempenho ao longo do tempo.

- **Robótica** - O Q-Learning é usado em robótica para ensinar robôs a aprender comportamentos e tarefas complexas, como manipulação de objetos, navegação em ambientes desconhecidos ou até mesmo interação social com humanos.

- **Otimização de Rotas** - O Q-Learning pode ser aplicado para otimizar rotas em problemas de planejamento de trajetória, como encontrar o caminho mais eficiente para um veículo percorrer em um ambiente com obstáculos.

- **Controle de Processos** - O Q-Learning é utilizado em sistemas de controle para aprender políticas de controle ótimas em processos dinâmicos. Isso pode incluir ações como ajustar a temperatura de um sistema de refrigeração e otimizar o consumo de energia em uma planta industrial.

## Quais são os passos do algoritmo Q-Learning?

1. **Inicialização**. Inicialize a tabela `Q` com valores arbitrários para todos os pares estado-ação possíveis. Esses valores representam as estimativas iniciais dos Q-valores.

2. **Seleção de ação**. Escolha uma ação para ser executada no estado atual. Isso pode ser feito usando uma estratégia como a escolha aleatória (exploração - _exploration_) ou a escolha da ação com o maior Q-valor (explotação - _exploitation_). Alternativamente, é possível usar uma estratégia híbrida de exploração como o epsilon-greedy.

3. **Execução da ação e observação do próximo estado e recompensa**. Execute a ação selecionada no ambiente e observe o próximo estado em que o agente se encontra e a recompensa associada a essa transição.

4. **Atualização da tabela Q**. Com base na observação do próximo estado e da recompensa, atualize o Q-valor do par estado-ação atual usando a equação de atualização do Q-Learning (equação de Bellman).

5. **Atualização do estado atual**. Defina o estado atual como o próximo estado observado na etapa anterior.

6. **Iteração**. Repita os passos Passos de 2 a 5, até que o agente alcance um estado final ou um critério de parada seja atingido.

7.  **Convergência**. À medida que o agente interage mais com o ambiente e atualiza repetidamente a tabela `Q`, os Q-valores começam a convergir para os valores ótimos, refletindo a melhor política de ações em cada estado.

### Como funciona a equação de atualização do Q-Learning (Equação de Bellman)?

A equação de atualização do Q-Learning, também conhecida como a equação de Bellman, é usada para atualizar o Q-valor de um par estado-ação com base nas informações do próximo estado e na recompensa imediata. A equação de atualização é a seguinte:

`Q(s, a) = Q(s, a) + α * (r + γ * max[Q(s', a')] - Q(s, a))`

Nesta equação:

- `Q(s, a)` é o Q-valor atual do par estado-ação `(s, a)`.
- `α` (alfa) é o fator de aprendizado que controla a taxa de aprendizado do agente. Ele determina o quanto os novos Q-valores afetam os valores existentes. Um valor entre 0 e 1 é usado, onde 0 significa que o agente não aprende nada e 1 significa que o agente substitui completamente os valores antigos pelos novos.
- `r` é a recompensa imediata recebida após executar a ação a no estado `s`.
- `γ` (gama) é o fator de desconto que controla o peso dado às recompensas futuras. Ele varia de 0 a 1, onde 0 significa que apenas as recompensas imediatas são consideradas, e 1 significa que todas as recompensas futuras são consideradas igualmente importantes.
- `max[Q(s', a')]` é o valor máximo dos Q-valores para todas as ações possíveis `a'` no próximo estado `s'`.
- `s'` é o próximo estado alcançado após executar a ação a no estado `s`.

Essa equação de atualização do Q-Learning permite ao agente ajustar progressivamente os Q-valores com base nas recompensas recebidas e nas estimativas dos Q-valores do próximo estado. Com o tempo, os Q-valores convergem para os valores ótimos, refletindo a melhor política de ações para maximizar a recompensa cumulativa.

## Como funciona a estratégia de exploração epsilon-greedy?

O epsilon-greedy é uma estratégia usada para equilibrar a exploração (realizar ações aleatórias para descobrir o ambiente) e a explotação (selecionar ações com base nos Q-valores aprendidos) durante o processo de aprendizado do algoritmo Q-Learning.

Essa estratégia funciona introduzindo uma taxa de exploração, representada como epsilon (`ε`). O agente seleciona um número aleatório entre 0 e 1, e se esse número for menor que `ε`, o agente explora escolhendo uma ação aleatória. Caso contrário, se o número aleatório for maior ou igual a `ε`, o agente explora o conhecimento atual selecionando a ação com o maior Q-valor.

Em outras palavras, com probabilidade `ε`, o agente explora realizando uma ação aleatória, e com probabilidade (1 - `ε`), ele explota seu conhecimento atual selecionando a ação com o maior Q-valor.

Encontrar o equilíbrio adequado entre exploração e explotação é crucial no aprendizado por reforço para garantir que o agente explore o suficiente para descobrir boas políticas, ao mesmo tempo em que explora o conhecimento existente para maximizar as recompensas.

## O que é a estratégia de exploração epsilon-greedy com decaimento?

O epsilon-greedy com decaimento (_epsilon-greedy decay_) consiste em uma melhoria na estratégia de exploração epsilon-greedy, que reduz gradativamente o valor de epsilon `ε` ao longo do tempo. Isso permite que o agente explore o ambiente inicialmente para descobrir ações potencialmente boas, e depois explote o conhecimento aprendido para maximizar suas recompensas.

Existem várias maneiras de se implementar a estratégia epsilon-greedy com decaimento. Uma abordagem comum é definir um valor inicial de epsilon, como `1.0`, o que significa que o agente inicialmente explora com alta probabilidade. Em seguida, a cada passo de tempo ou episódio, epsilon é reduzido por um certo fator de decaimento. O fator de decaimento determina a rapidez com que epsilon diminui ao longo do tempo.

Usando um esquema de decaimento linear simples, o valor de epsilon poderia ser atualizado da seguinte forma:

`ε = max(ε₀ - a*i, εₘᵢₙ)`

Nesta fórmula:
- `ε₀` é o valor inicial de epsilon.
- `a` é uma constante que determina a taxa de decaída.
- `i` é o número atual da iteração do algoritmo Q-Learning.
- `εₘᵢₙ` é o valor mínimo que epsilon pode alcançar.
- A função `max` garante que epsilon não fique abaixo de `εₘᵢₙ`.


## Qual a complexidade computacional do algoritmo Q-Learning?

A complexidade computacional do algoritmo Q-learning depende de vários fatores, como o tamanho do espaço de estados e ação, a representação da Q-função o número de iterações.

Além disso, a complexidade espacial do Q-learning é determinada pela necessidade de armazenar a Q-função, que normalmente é representada em uma tabela ou em uma estrutura de dados equivalente. O espaço necessário para armazenar a Q-função cresce com o tamanho do espaço de estados e ações.

Em problemas com um espaço de estados e ações muito grande, a tabela `Q` pode se tornar impraticável devido ao tamanho excessivo. Nesses casos, são utilizadas técnicas de aproximação de função, como redes neurais, para representar a Q-função de forma mais compacta.
