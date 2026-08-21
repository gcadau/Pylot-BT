/* Giovanni Cadau © */

#include <stdlib.h>
#include "partitore.h"

void powerset(int* val, int k, int* sol, Partitore p);
int powersetRic(int* val, int k, int* sol, int n, int pos, int start, int count, Partitore p);
int fattoriale(int n);
int coefficienteBinomiale(int n, int k);

void creaPartitore(Partitore* p, int dim)
{
    int d = 0;
    int i;
    for(i=dim; i>0; i--)    d += coefficienteBinomiale(dim, i);


    (*p) = malloc(sizeof(struct partitore_s));
    (*p)->dim = d;
    (*p)->dimInterna = dim;
    (*p)->v = malloc(((*p)->dim)*sizeof(int*));

    int* val = malloc(dim*sizeof(int));
    for(i=0; i<dim; i++)    val[i] = i;
    int* sol = malloc(dim* sizeof(int));
    powerset(val, dim, sol, *p);
    free(sol);
}

void liberaPartitore(Partitore p)
{
    int i;
    for(i=0; i<p->dim; i++)
    {
        free(p->v[i]);
    }

    free(p->v);
    free(p);
}

void powerset(int* val, int k, int* sol, Partitore p)
{
    int count = 0;
    int n;
    for(n=k; n>=1; n--)
        count = powersetRic(val, k, sol, n, 0, 0, count, p);
}

int powersetRic(int* val, int k, int* sol, int n, int pos, int start, int count, Partitore p)
{
    int i;
    if (pos==n)
    {
        p->v[count] = malloc(n*sizeof(int));
        for(i=0; i<p->dimInterna; i++)  p->v[count][i] = 0;
        for(i=0; i<n; i++)  p->v[count][sol[i]] = 1;
        return count+1;
    }

    for (i=start; i<k; i++)
    {
        sol[pos] = val[i];
        count = powersetRic(val, k, sol, n, pos+1, i+1, count, p);
    }

    return count;
}

int fattoriale(int n)
{
    int r = 1;
    while(n>=2)
    {
        r*=n;
        n--;
    }

    return r;
}

int coefficienteBinomiale(int n, int k)
{
    return fattoriale(n)/(fattoriale(k)*fattoriale(n-k));
}