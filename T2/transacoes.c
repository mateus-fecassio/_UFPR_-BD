/**
 * @file  transacoes.c
 * @brief Arquivo com as implementações da biblioteca transacoes.h
 * @date 22 Jul 2021
 * @author Mateus Felipe de Cássio Ferreira (GRR20176123)
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafos.h"
#include "transacoes.h"


int readTransacoes(FILE *input, transacoes *T)
{
    int max = 30;
    (*T) = (transacoes) malloc (sizeof(transacao) * max);
    int n = 0;

    while( fscanf(input,"%d %d %c %c\n",&(*T)[n].timeIn,
                                        &(*T)[n].id,
                                        &(*T)[n].op,
                                        &(*T)[n].atb) == 4 )
    {
        n++; //contagem de transações

        //se exceder do limite de transações, realoca a estrutura de dados de transações
        if( n >= max )
        {
            max+=10;
            (*T) = (transacoes) realloc ((*T), sizeof(transacao) * max);
        }
    }
    (*T) = (transacoes) realloc ((*T), sizeof(transacao) * n);

    return n;
} //FINALIZADA


grafo *constructGrafo(transacoes T, int n)
{
    grafo *S = (grafo *) malloc (sizeof(grafo));
    S->n = 0;

    for(int i=0; i<n; i++)
        if( T[i].id > S->n )
            S->n = T[i].id;

    S->mtxAdj = (int *) malloc (sizeof(int) * S->n * S->n);
    memset (S->mtxAdj, 0, sizeof(int) * S->n * S->n);

    for(int i=0; i < n; i++){ 
        for(int j=i+1; j < n; j++){
            if( (T[i].id != T[j].id) && (T[i].atb == T[j].atb) )            //se duas transações distintas operam sobre um mesmo atributo, devemos verificar o conflito
            {
                if( (T[i].op == 'R') && ( T[j].op == 'W' ) )                //Aresta Ti -> Tj para cada r(x) em Tj depois de w(x) em Ti
                    S->mtxAdj[(T[i].id-1) * S->n + (T[j].id-1)]++;
                
                if( (T[i].op == 'W') && ( T[j].op == 'R' ) )                //Aresta Ti -> Tj para cada w(x) em Tj depois de r(x) em Ti
                    S->mtxAdj[(T[i].id-1) * S->n + (T[j].id-1)]++;
                
                if( (T[i].op == 'W') && ( T[j].op == 'W' ) )                //Aresta Ti -> Tj para cada w(x) em Tj depois de w(x) em Ti
                    S->mtxAdj[(T[i].id-1) * S->n + (T[j].id-1)]++;
            }
        }
    }
    return S;
} //FINALIZADA


void printEscalonamento(int *LTid, int n)
{
    for(int i=0; i < n; i++)
        fprintf(stdout, "%d%c", LTid[i]+1, i+1 >= n ? ' ' : ',');
} //FINALIZADA


int read_before_write(transacoes T, int i)
{
    int validation = 0;
    for(int j=0; j<i && !validation; j++)
        if( (T[j].id == T[i].id) && (T[j].op == 'R') && (T[j].atb == T[i].atb))
            validation = 1;
    return validation;
} //FINALIZADA


int findChar(char *str, int n, char c)
{
    for(int i=0; i<n; i++)
        if(str[i]==c)
            return i;
    return -1;
} //FINALIZADA


int *countAtb(transacoes T, int n, char *atb)
{
    int *vcount = (int *) malloc (sizeof(int) * n);
    memset(vcount, 0, sizeof(int) * n);
    
    int k = 1;
    
    for(int i=0; i < n; i++)
    {
        if(T[i].op != 'C')
        {
            int achou = findChar(atb,n,T[i].atb);
            if( achou >= 0 )
            {
                vcount[achou]++;
            }
            else
            {
                atb[k] = T[i].atb;
                vcount[k++]++;
            }
        }
    }

    vcount[0]=k-1;

    vcount = (int *) realloc (vcount, sizeof(int) * (k));
    return vcount;
} //FINALIZADA


int equivalenciaPorVisao(transacoes *T, int n)
{
    char *atbs = (char *) malloc (sizeof(char) * n);
    int *nAtbs = countAtb((*T),n,atbs);


    int finalIdsWrite[nAtbs[0]];
    int finalTimeInWrite[nAtbs[0]];
    int fid = 0;
    int fti = 0;

    for(int atb=0; atb < nAtbs[0]; atb++)                               //para cada diferente atributo encontrado em todas as transações
    {
        int findFinal = 0;
        for(int i=nAtbs[atb+1]-1; i >= 0 && !findFinal; i--)
            if( T[atb][i].op == 'W' )                                   //verificar se existe alguma operação de escrita sobre determinado atributo
            {
                finalIdsWrite[fid++] = T[atb][i].id;                    //guardar o identificador da transação que tenha essa operação de escrita
                finalTimeInWrite[fti++] = T[atb][i].timeIn;             //guardar o tempo de chegada da transação que tenha essa operação de escrita
                findFinal = 1;                                          //quebra a repetição
            }
    }

    int finalW = 1;

    for(int atb=0; atb < nAtbs[0]; atb++)                               //iteração sobre a lista de atributos encontrados
        for(int t=nAtbs[atb+1]-1; t >= 0 && finalW; t--)
        {                                                               //encontrar duas transações (diferentes IDs), que operem uma escrita sobre um atributo e que não seja a última escrita de determinada transação
            if( (T[atb][t].timeIn > finalTimeInWrite[atb]) && (T[atb][t].op == 'W') && (T[atb][t].id != finalIdsWrite[atb]) )
                finalW = 0;
        }
    return finalW;
} //FINALIZADA


void printTransacoes(transacoes T, int n)
{
    for (int i = 0; i < n; i++)
    {
        fprintf(stdout, "%d %d %c %c\n", T[i].timeIn, T[i].id, T[i].op, T[i].atb);
    }
} //FINALIZADA