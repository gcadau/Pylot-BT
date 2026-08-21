/* Giovanni Cadau © */

#include <stdlib.h>
#include "utility.h"
#include "sortingInt.h"
#include "matrix.h"

#define START 4
#define CRESCITA 2

int equalVett(int* a, int* b);

void creaMatrice(Matrice* m)
{
    (*m) = malloc(sizeof(struct matrice_s));
    (*m)->dim = 0;
    (*m)->realDim = START;
    (*m)->v = malloc(((*m)->realDim)*sizeof(int*));
}

void liberaMatrice(Matrice m)
{
    int i;
    for(i=0; i<m->dim; i++)
    {
        free(m->v[i]);
    }
    free(m->v);

    free(m);
}

void aggiungiVettore(Matrice m, int* a)
{
    if( (m->dim)+1 > (m->realDim) )
    {
        (m->realDim) *= CRESCITA;
        m->v = realloc(m->v, (m->realDim)*sizeof(int*));
    }

    int i=0;
    while(a[i++]!=-1);
    int* vett = malloc(i* sizeof(int));

    int j;
    for(j=0; j<i; j++)
        vett[j] = a[j];

    m->v[(m->dim)++] = vett;
}

int checkDuplicati(Matrice m, int* v)
{
    int i;
    int vett[L];
    int a;
    for(i=0; i<m->dim; i++)
    {
        int j = 0;
        while((a=m->v[i][j++])!=-1)
        {
            vett[j] = a;
        }
        if(equalVett(vett, v))
            return 1;
    }

    return 0;
}

int equalVett(int* a, int* b)
{
    int i;

    i=0;
    while(a[i++]!=-1);
    int dimA = i-1;
    i=0;
    while(b[i++]!=-1);
    int dimB = i-1;

    if(dimA!=dimB)
        return 0;

    SortInt(a, dimA);
    SortInt(b, dimB);

    for(i=0; i<dimA; i++)
    {
        if(a[i]!=b[i])
            return 0;
    }

    return 1;
}