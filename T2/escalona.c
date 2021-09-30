/**
 * @file  escalona.c
 * @brief Programa principal, que será utilizado para detecção de conflitos de escalonamento de transações concorrentes.
 * @date 22 Jul 2021
 * @author Mateus Felipe de Cássio Ferreira (GRR20176123)
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafos.h"
#include "transacoes.h"

/**
 * @brief Função principal que faz a detecção de conflitos de escalonamento de transações concorrentes.
 * A entrada deve ser feita pela entrada padrão (stdin). O arquivo é formado por uma sequência de linhas, onde cada linha representa uma transação chegando. Cada linha tem 4 campos: o primeiro é o tempo de chegada, o segundo é o identificador da transação, o terceiro é a operação (R=read, W=write, C=commit) e o quarto o atributo que será lido/escrito. Estas linhas estão ordenadas pelo primeiro campo (tempos menores no início indicando a linha do tempo).
 * @return A saída deve ser feita pela saída padrão (stdout). O arquivo será composto por uma sequência de linhas. Uma linha para cada escalonamento. Cada linha tem 4 campos separados por espaço (um único espaço entre cada par de campos). O primeiro campo é o identificador do escalonamento. O segundo campo é a lista de transações. E o terceiro apresenta o resultado do algoritmo da garantia da seriabilidade, onde SS e NS significam respectivamente serial (SS) ou não serial (NS). O quarto campo é o resultado do algoritmo de teste de equivalência de visão, onde SV e NV significam respectivamente equivalente (SV) ou não equivalente (NV).
 **/
int main()
{
    transacoes T = NULL;
    
    int n = readTransacoes(stdin,&T);
    
    grafo *S = constructGrafo(T,n);
    
    int *ciclos = findCiclos(S);                                                // ciclos = [x1,x2...S->n-1], onde xi = 1 se xi é um vértice de uma aresta de retorno (forma um ciclo) ou x1 = 0 (não forma um ciclo)
    int nciclos = countCiclos(ciclos, S->n);                                    //contagem de quantos ciclos foram formados com as transações passadas
    int *conflitos = verticesComConflito(ciclos, S->n, nciclos);                //identificar os vértices que possuem algum conflito (formaram um ciclo entre si)
    int *serializaveis = verticesSemConflito(ciclos, S->n, S->n - nciclos);     //identificar os vértices que NÃO possuem algum conflito (NÃO formaram um ciclo entre si). Ou seja, são os restantes das transações que não formaram um conflito.

    int id_escal = 1;

    if( nciclos == 0 )                                                          //se o grafo NÃO possui ciclos, então ele é serializável por conflito e por visão  
    {                         
        fprintf(stdout, "%d ", id_escal);
        printEscalonamento(S->topologic, S->n);
        fprintf(stdout, "SS SV\n");
    }
    else                                                                        //se o grafo possuir ciclos
    {                            
        fprintf(stdout, "%d ", id_escal);
        printEscalonamento(conflitos, nciclos);                                 //imprimir as transações que tiveram conflito, e, portanto, não são serializáveis (NS)
        fprintf(stdout, "NS ");
        int fim = 0;
        int validation = 0;
        for(int i=0; i<n && !fim; i++)                                          //procura alguma transação que tenha sido realizada uma operação de escrita
        {             
            if( T[i].op == 'W' )
            {
                validation = read_before_write(T,i);                            //nessa transação encontrada, determinar se houve uma operação de leitura, em uma mesma transação e em um mesmo atributo, antes da operação dessa operação de escrita
                if(!validation)                                                 //CASO 0: caso não tenha sido realizado essa operação de leitura, testamos a equivalência do escalonamento por visão
                {                    
                    if(equivalenciaPorVisao(&T,n))
                        fprintf(stdout, "SV\n");                                //SV se o retorno da função for 1
                    else
                        fprintf(stdout, "NV\n");                                //NV se o retorno da função for 0
                }
                fim = 1;
            }
        }
        if(validation)                                                          //caso encontre alguma transação que tenha sido realizado uma operação de leitura (antes uma operação de escrita), o escalonamento impresso na linha 45, conceitualmente, não é equivalente por visão (NV)
            fprintf(stdout, "NV\n");
            
        if( (S->n - nciclos) > 0)                                               //impressão das transações que não apresentaram nenhum conflito, e são, por tanto, serializáveis
        {
            id_escal++;
            fprintf(stdout, "%d ",id_escal);
            printEscalonamento(serializaveis, S->n-nciclos);
            fprintf(stdout, "SS SV\n");
        }
    }
    //printTransacoes(T,n);
    return 0;
};