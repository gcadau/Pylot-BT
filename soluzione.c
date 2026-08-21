/* Giovanni Cadau © */

#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "coordinata.h"
#include "topologia.h"
#include "cella.h"
#include "gruppo.h"
#include "gruppi.h"
#include "movimento.h"
#include "soluzione.h"

struct soluzione_s
{
    movimento* movimenti;
    int dim;
};

void memorizza(soluzione* s, int dim)
{
    if((*s)!=NULL)
    {
        int i;
        for(i=0; i<(*s)->dim; i++)
            liberaMovimento((*s)->movimenti[i]);
        free(*s);
    }
    (*s) = malloc(sizeof(struct soluzione_s));
    (*s)->dim = dim;
    (*s)->movimenti = malloc(((*s)->dim) * sizeof(movimento));
}

void aggiungiMovimento(soluzione s, gruppo* gr, int dim, int n)
{
    movimento m;
    creaMovimento(&m, gr, dim, n);
    s->movimenti[n-1] = m;
}

void stampaSoluzione(soluzione s)
{
    FILE* f = fopen(FILE_OUTPUT_SOLUZIONI, "w");
    int i;
    for(i=0; i<s->dim; i++)
    {
        stampaMovimento(s->movimenti[i], f);
    }
    fclose(f);
}