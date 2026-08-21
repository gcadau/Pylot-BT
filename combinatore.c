/* Giovanni Cadau © */

#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "combinatore.h"

typedef struct
{
    int *scelte;
    int num_scelte;
} Livello;

int princ_molt(int pos, Livello *val, int *sol, int n, int count, Combinatore c);

void creaCombinatore(Combinatore* c, int* valori, int dim)
{
    int d = 1;
    int i, j;
    for(i=0; i<dim; i++)    d *= valori[i];

    (*c) = malloc(sizeof(struct combinatore_s));
    (*c)->dim = d;
    (*c)->dimInterna = dim;
    (*c)->v = malloc(((*c)->dim)*sizeof(int*));

    Livello* l = malloc(dim*sizeof(Livello));
    for(i=0; i<dim; i++)
    {
        l[i].num_scelte = valori[i];
        l[i].scelte = malloc((l[i].num_scelte)* sizeof(int));
        for(j=0; j<valori[i]; j++)
        {
            l[i].scelte[j] = j;
        }
    }

    int* sol = malloc(dim* sizeof(int));
    princ_molt(0, l, sol, dim, 0, *c);
    free(sol);
    free(l);
}

void liberaCombinatore(Combinatore c)
{
    int i;
    for(i=0; i<c->dim; i++)
    {
        free(c->v[i]);
    }

    free(c->v);
    free(c);
}

int princ_molt(int pos, Livello *val, int *sol, int n, int count, Combinatore c)
{
    int i;
    if(pos>=n)
    {
        c->v[count] = malloc(n*sizeof(int));
        for(i=0; i<n; i++)
        {
            c->v[count][i] = sol[i];
        }
        return count+1;
    }

    for(i=0; i<val[pos].num_scelte; i++)
    {
        sol[pos] = val[pos].scelte[i];
        count = princ_molt(pos+1, val, sol, n, count, c);
    }
    return count;
}