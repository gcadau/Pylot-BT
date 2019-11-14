#include <stdio.h>
#include <stdlib.h>
#include "coordinata.h"
#include "topologia.h"
#include "cella.h"
#include "gruppo.h"
#include "gruppi.h"

#define START 4
#define CRESCITA 2

struct gruppi_s
{
    gruppo* insieme;
    int dim;
    int realDim;

    gruppi* raggruppamentiPerTopologia;
    int dimRaggruppamentiPerTopologia;
};

void creaGruppi(gruppi* g)
{
    *g = malloc(sizeof(struct gruppi_s));
    (*g)->dim = 0;
    (*g)->realDim = START;
    (*g)->insieme = malloc(((*g)->realDim) * sizeof(gruppo));
    (*g)->dimRaggruppamentiPerTopologia = -1;
    (*g)->raggruppamentiPerTopologia = NULL;
}

void liberaGruppi(gruppi g)
{
    free(g->insieme);

    int pres = 0;
    int i;
    for(i=0; i<g->dimRaggruppamentiPerTopologia; i++)
    {
        liberaGruppi(g->raggruppamentiPerTopologia[i]);
        pres = 1;
    }
    if(pres)
        free(g->raggruppamentiPerTopologia);

    free(g);
}

void aggiungiGruppo(gruppi g, gruppo gr)
{
    if((g->dim) + 1 > (g->realDim) )
    {
        (g->realDim) *= CRESCITA;
        g->insieme = realloc(g->insieme, (g->realDim) * sizeof(gruppo));
    }

    g->insieme[(g->dim)++] = gr;
}

void stampaGruppi(gruppi g)
{
    int i;
    for(i=0; i<g->dim; i++)
    {
        stampaGruppo(g->insieme[i]);
        printf("\n");
    }
}

void raggruppaPerTopologia(gruppi g, topologia* t, int dimT)
{
    g->dimRaggruppamentiPerTopologia = dimT;
    g->raggruppamentiPerTopologia = malloc((g->dimRaggruppamentiPerTopologia)*sizeof(gruppi));
    int k;
    for(k=0; k<g->dimRaggruppamentiPerTopologia; k++)
    {
        creaGruppi(&(g->raggruppamentiPerTopologia[k]));
    }

    int i, j;
    for(i=0; i<g->dim; i++)
    {
        topologia top = getTopologia(g->insieme[i]);
        for(j=0; j<dimT; j++)
        {
            if(equalTopologia(top, t[j]))
            {
                aggiungiGruppo(g->raggruppamentiPerTopologia[j], g->insieme[i]);
            }
        }
    }
}

int getDimG(gruppi g)
{
    return g->dim;
}

gruppo* getGruppi(gruppi g)
{
    return g->insieme;
}

int getDimRaggruppamentiPerTopologia(gruppi g)
{
    return g->dimRaggruppamentiPerTopologia;
}

gruppi* getRaggruppamentiPerTopologia(gruppi g)
{
    return g->raggruppamentiPerTopologia;
}