/* Giovanni Cadau © */

#include <stdio.h>
#include <stdlib.h>
#include "coordinata.h"
#include "topologia.h"
#include "cella.h"
#include "gruppo.h"
#include "gruppi.h"
#include "movimento.h"

struct movimento_s
{
    gruppi g;
    int numero;
};

void creaMovimento(movimento* m, gruppo* gr, int dim, int n)
{
    *m = malloc(sizeof(struct movimento_s));
    (*m)->numero = n;
    creaGruppi(&((*m)->g));
    int i;
    for(i=0; i<dim; i++)
    {
        aggiungiGruppo((*m)->g, gr[i]);
    }
}

void liberaMovimento(movimento m)
{
    liberaGruppi(m->g);
    free(m);
}

void stampaMovimento(movimento m, FILE *f)
{
    fprintf(f, "Movimento %d\n", m->numero);
    gruppo* gr = getGruppi(m->g);
    int dim = getDimG(m->g);
    int i;
    for(i=0; i<dim; i++)
    {
        stampaGruppo(gr[i], f);
        fprintf(f, "\n");
    }
    fprintf(f, "\n\n");
}