/**
 * @file  grafos.c
 * @brief Arquivo com as implementações da biblioteca grafos.h
 * @date 22 Jul 2021
 * @author Mateus Felipe de Cássio Ferreira (GRR20176123)
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafos.h"

//DEFINIÇÃO DE VARIÁVEIS GLOBAIS
int ordemCount;
int topoIdx;


int *findCiclos(grafo *S)
{
    ordemCount = 0;
    topoIdx = 0;

    S->state = (state *) malloc (sizeof(state) * S->n);
    S->topologic = (int *) malloc (sizeof(int) * S->n);
    int *ciclos = (int *) malloc (sizeof(int) * S->n);              //vetor que indica se um vértice forma um ciclo

    //inicilizar o estado/ordem de todos os vértices do grafo
    for(int i=0; i < S->n; i++)
        S->state[i].pre = -1;

    //inicializar o vetor de ciclos com o valor 0
    memset(ciclos, 0, sizeof(int) * S->n);

    for(int i=0; i < S->n; i++)                                     //percorre todos os vértices do grafo S
        if( S->state[i].pre == -1 )                                 //que ainda não tiveram sido percorridos
            calculaPrePos(S,i);                                     //e faz uma busca de profundidade para setar as ordens pré e pós

    for(int i=0; i < S->n; i++)                                     //percorre os vértices do grafo
        for(int j=0; j < S->n; j++)                                 //percorre a matriz de adjacência
            if( S->mtxAdj[i * S->n + j] )                           //se encontrar algum vértice vizinho
            {
                if( S->state[i].pos < S->state[j].pos )             //e ele estiver ligado por uma aresta de retorno
                {
                    ciclos[i] = 1;
                    ciclos[j] = 1; 
                }                                                   //eles são parte de um ciclo
            }
    return ciclos;
} //FINALIZADA


void calculaPrePos(grafo *S, int i)
{
    S->state[i].pre = ordemCount++;                                 //ordem de entrada no vértice
    for(int j=0; j < S->n; j++)                                     //percorre a matriz de adjacência
    {                                     
        if( S->mtxAdj[i * S->n + j] )                               //se encontrar algum vértice vizinho
        {                                  
            if( S->state[j].pre == -1)                              //que não tenha sido percorrido                          
                calculaPrePos(S,j);                                 //entra em uma recursão nele
        }
    }
    if(topoIdx < S->n)
        S->topologic[topoIdx++] = i;                                 //o vetor de topologia recebe o valor que representa um vértice
        
    S->state[i].pos = ordemCount++;                                  //ordem de saída no vértice
} //FINALIZADA


int countCiclos(int *cicles, int n)
{
    int count = 0;
    for(int i=0; i < n; i++)
        if(cicles[i])
            count++;
    return count;
} //FINALIZADA


int *verticesComConflito(int *cicles, int n, int nc)
{
    int *v = (int *) malloc (sizeof(int) * nc);
    int j = 0;
    for(int i=0; i < n; i++)
        if(cicles[i])
            v[j++]=i;
    return v;
} //FINALIZADA


int *verticesSemConflito(int *cicles, int n, int nc)
{
    int *v = (int *) malloc (sizeof(int) * nc);
    int j = 0;
    for(int i=0; i < n; i++)
        if(!cicles[i])
            v[j++]=i;
    return v;
} //FINALIZADA