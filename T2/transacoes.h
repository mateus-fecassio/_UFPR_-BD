#ifndef __TRANSACOES__
#define __TRANSACOES_
/**
 * @file  transacoes.h
 * @brief Arquivo que define as estruturas de dados que serão utilizadas para montar uma transação, bem como as funções utilizadas para a manipulação das transações contidas no arquivo transacoes.c.
 * @date 22 Jul 2021
 * @author Mateus Felipe de Cássio Ferreira (GRR20176123)
 **/

// ----------------------------------------------------------- ESTRUTURAS DE DADOS
/** @struct transacao
 *  @brief Estrutura para manter os dados de uma transação.
 *  @var transacao::timeIn
 *      Tempo de entrada da transação;
 *  @var transacao::id
 *      Identificador da transação;
 *  @var transacao::op
 *      Tipo de operação realizada durante a transação;
 *  @var transacao::atb
 *      Atributo que será operado durante a transação.
 */
typedef struct 
{
    int timeIn;
    int id;
    char op;
    char atb;
} transacao;

/**
 *@brief Definição de um vetor de transações.
 */
typedef transacao * transacoes;

// -----------------------------------------------------------


// ----------------------------------------------------------- FUNÇÕES
/**
 * @brief Realiza a leitura do arquivo de transações, nesse caso passado pela entrada padrão, e aloca em um vetor de transações T
 * @param input Parâmetro para definir qual a entrada de dados que será lida pelo fscanf. Nesse caso, será a stdin.
 * @param T Vetor com as transações.
 * @return Retorna o número de transações lidas.
*/
int readTransacoes(FILE *input, transacoes *T);


/**
 * @brief Implementa um algoritmo de teste de conflito de seriabilidade, criando um grafo que utiliza uma matriz de adjacência para colocar uma aresta e ligar as transações de acordo com as condicões do algoritmo.
 * @param T Vetor com as transações.
 * @param n Tamanho do vetor de transações.
 * @return Retorna um ponteiro para o grafo criado.
*/
grafo *constructGrafo(transacoes T, int n);


/**
 * @brief Imprime uma lista de transações na saida padrão (stdout) que pertencem a um determinado escalonamento.
 * @param LTid Lista com os IDs(transacao->id) das transações que foram escalonadas;
 * @param n Tamanho da lista;
*/
void printEscalonamento(int *LTid, int n);


/**
 * @brief Essa função realiza um teste se foi realizado uma operação de leitura antes de uma operação de escrita em uma mesma transação e em um mesmo atributo.
 * Isso é importante para determinar a execução do algoritmo de equivalência por visão. Ela é uma parte do algotimo para deteção de equivalência por visão.
 * @param T Lista de transações;
 * @param i Quantidade de transações a serem avaliadas.
 * @return A função retorna 1 se foi realizado uma operação de leitura antes de uma operação de escrita em uma mesma transação. Caso contrário, retorna 0.
*/
int read_before_write(transacoes T, int i);


/**
 * @brief Essa função faz uma conferência se um caractere está no contido em um vetor de caracteres.
 * @param str Vetor de caracteres;
 * @param n Tamanho do vetor;
 * @param c Caractere a ser buscado.
 * @return A função retorna o primeiro índice em que o caractere se encontra. Caso essa função não encontre, ela retorna -1.
*/
int findChar(char *str, int n, char c);


/**
 * @brief Percorre as transações contando repetições de atributos e os coloca em um vetor de inteiros, onde cada posição é um atributo com índice correlacionado com o vetor de atributos.
 * @param T Lista de transações;
 * @param n Tamanho da lista;
 * @param atb Lista que receberá os diferentes atributos.
 * @return O retorno da função é um vetor de inteiros contendo na primeira posição (V[0]) a quantidade de atributos diferentes. Nas demais posições, o vetor contém a quantidade do atributo encontrado.
*/
int *countAtb(transacoes T, int n, char *atb);


/**
 * @brief Essa função implementa o algoritmo de equivalência por visão. Ela realiza o último teste proposto
 * (Se o operador w(y) em Tk é a ultima escrita de y em S, então w(y) em Tk deve ser a última escrita em S')
 * para determinar se duas visões são equivalentes.
 * @param T Lista de transações;
 * @param n Quantidade de transações.
 * @return O retorno da função é 1 se é equivalente por visão. Caso contrátio, o retorno é 0.
*/
int equivalenciaPorVisao(transacoes *T, int n);


/**
 * @brief Faz a impressão, na saída padrão, das transações que foram lidas;
 * @param T Lista de transações;
 * @param n Quantidade de transações.
*/
void printTransacoes(transacoes T, int n);


#endif