### Objetivo:

Implementar dois algoritmos de detecção de conflitos de escalonamento de transações concorrentes. Estes algoritmos permitem o aluno compreender gargalos no processamento de transações.

### Algoritmo de teste de seriabilidade quanto ao conflito:

*   Crie um nó para cada T do escalonamento S
*   Aresta T<sub>i</sub> -> T<sub>j</sub> para cada r(x) em T<sub>j</sub> depois de w(x) em T<sub>i</sub>
*   Aresta T<sub>i</sub> -> T<sub>j</sub> para cada w(x) em T<sub>j</sub> depois de r(x) em T<sub>i</sub>
*   Aresta T<sub>i</sub> -> T<sub>j</sub> para cada w(x) em T<sub>j</sub> depois de w(x) em T<sub>i</sub>
*   S é serial se não existe ciclo no grafo

### Algoritmo de teste de equivalencia por visão

Dois agendamentos S e S' são equivalentes por visão, se atenderem as seguintes condições:

*   O mesmo conjunto de transações e operações participam em S e S'
*   Para cada r(x) de T<sub>i</sub>, se o valor de x lido for escrito por w(x) de T<sub>j</sub>, o mesmo deve permanecer para r(x) de T<sub>i</sub> em S'
*   Se o operador w(y) em T<sub>k</sub> é a ultima escrita de y em S, então w(y) em T<sub>k</sub> deve ser a última escrita em S'

