#ifndef __GRAFOS__
#define __GRAFOS_
/**
 * @file  grafos.h
 * @brief Arquivo que define as estruturas de dados que serão utilizadas para montar um grafo, bem como as funções utilizadas para a manipulação dessas estruturas contidas no arquivo grafos.c.
 * @date 22 Jul 2021
 * @author Mateus Felipe de Cássio Ferreira (GRR20176123)
 **/

// ----------------------------------------------------------- ESTRUTURAS DE DADOS
/** @struct state
 *  @brief Estrutura de dado para manter o pré e o pós de um vértice ligado ao grafo.
 *  @var state::pre
 *      Ordem de entrada no vértice em uma busca de profundidade;
 *  @var state::pos
 *      Ordem de saída no vértice em uma busca de profundidade.
 */
typedef struct
{
    int pre;
    int pos;
} state;


/** @struct grafo
 *  @brief Estrutura de um grafo usado com os vértices das transações.
 *  @var grafo::mtxAdj
 *      Matriz de Adjacência utilizada para inserir arcos no grafo, implementada como um vetor de inteiros.
 *  @var grafo::n
 *      Números de vértices;
 *  @var grafo::state
 *      Vetor de estado dos vértices;
 *  @var grafo::topologic
 *      Ordenação topológica que pode ser formada, APENAS no caso que não haja um ciclo formado no grafo.
 */
typedef struct
{
    int n;
    int *mtxAdj;
    int *topologic;
    state *state;
} grafo;
// -----------------------------------------------------------


// ----------------------------------------------------------- FUNÇÕES
/**
 * @brief Essa função realiza uma busca por ciclos em um grafo.
 * Ela calcula as ordens de pré e pós de cada vértice e
 * percorre os vértices e a matriz de adjacência, procurando por uma aresta de retorno.
 * Isso acontece quando pos[Vi] < pos[Vj].
 * @param *S Grafo criado pela função constructGrafo.
 * @return Retorna um vetor de ciclos. Se ciclos[vértice] = 1, então, o vértice possui um ciclo. Se ciclos[vértice] = 0, o vértice não possui um ciclo.
 * @see constructGrafo()
*/
int *findCiclos(grafo *S);


/**
 * @brief É uma função recursiva de busca de profundidade. Ao realizar essa busca, os valores de pré e pós são definidos.
 * @param *S Grafo criado pela função constructGrafo;
 * @param i Valor do vértice, nesse caso o ID, que está sendo iterado.
 * @see constructGrafo()
*/
void calculaPrePos(grafo *S, int i);


/**
 * @brief Conta os vértices que formaram ciclos.
 * @param *cicles Vetor de ciclos encontrado na função findCicles;
 * @param n Tamanho do vetor de ciclos;
 * @return Retorna o total de vértices que formaram um ciclo.
*/
int countCiclos(int *cicles, int n);


/**
 * @brief Cria vetor apenas com os vértices conflitantes (ou seja, aqueles que formaram um ciclo).
 * @param cicles Vetor que indica os ciclos formados;
 * @param n Tamanho do vetor de ciclos;
 * @param nc Quantidade de conflitos, ou seja, a quantidade de ciclos formados.
 * @return Vetor com os vértices conflitantes (que formaram um ciclo).
*/
int *verticesComConflito(int *cicles, int n, int nc);


/**
 * @brief Cria vetor apenas com os vértices NÃO conflitantes (ou seja, aqueles que NÃO formaram um ciclo).
 * @param cicles Vetor que indica os ciclos formados;
 * @param n Tamanho do vetor de ciclos;
 * @param nc Quantidade de conflitos, ou seja, a quantidade de ciclos formados.
 * @return Vetor com os vértices NÃO conflitantes (vetor serializável).
*/
int *verticesSemConflito(int *cicles, int n, int nc);


#endif