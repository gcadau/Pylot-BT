/* Giovanni Cadau © */

#include <stdio.h>
#include <stdlib.h>
#include "coordinata.h"
#include "topologia.h"
#include "cella.h"
#include "gruppo.h"
#include "sortingGruppi.h"
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

void stampaGruppi(gruppi g, FILE *f)
{
    int i;
    for(i=0; i<g->dim; i++)
    {
        stampaGruppo(g->insieme[i], f);
        fprintf(f, "\n");
    }
}

void ordinaGruppi(gruppi g)
{
    SortGruppi(g->insieme, g->dim);
}

void raggruppaPerTopologia(gruppi g)
{
    int realDimT = START;
    int dimT = 0;
    topologia* t = malloc(realDimT * sizeof(topologia));
    g->dimRaggruppamentiPerTopologia = START;
    g->raggruppamentiPerTopologia = malloc((g->dimRaggruppamentiPerTopologia)*sizeof(gruppi));
    int m;
    for(m=0; m<g->dimRaggruppamentiPerTopologia; m++)
    {
        creaGruppi(&(g->raggruppamentiPerTopologia[m]));
    }

    int i, j;
    for(i=0; i<g->dim; i++)
    {
        topologia top = getTopologia(g->insieme[i]);
        int trovato = 0;
        for(j=0; j<dimT && !trovato; j++)
        {
            if(equalTopologia(top, t[j]))
            {
                aggiungiGruppo(g->raggruppamentiPerTopologia[j], g->insieme[i]);
                trovato = 1;
            }
        }
        if(!trovato)
        {
            if(dimT+1 > realDimT)
            {
                realDimT *= CRESCITA;
                t = realloc(t, realDimT * sizeof(topologia));
                g->raggruppamentiPerTopologia = realloc(g->raggruppamentiPerTopologia, realDimT*sizeof(gruppi));
            }
            t[dimT] = top;
            creaGruppi(&(g->raggruppamentiPerTopologia[dimT]));
            aggiungiGruppo(g->raggruppamentiPerTopologia[dimT++], g->insieme[i]);
        }
    }
    g->dimRaggruppamentiPerTopologia = dimT;

    free(t);
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

void getGruppiConCella(gruppi g, cella c, gruppo** cont)
{
    *cont = malloc(g->dim*sizeof(gruppo));
    int dim = 0;
    int i;
    for(i=0; i<g->dim; i++)
    {
        if(checkPresenzaCella(g->insieme[i], c))
        {
            (*cont)[(dim)++] = g->insieme[i];
        }
    }
    setGruppoNullo(&((*cont)[(dim)++]));
    (*cont) = realloc((*cont), (dim* sizeof(gruppo)));
}

gruppi getRaggruppamentoPerTopologiaContenenteGruppo(gruppi gr, gruppo g)
{
    int i;
    for(i=0; i<gr->dimRaggruppamentiPerTopologia; i++)
    {
        gruppi grs = gr->raggruppamentiPerTopologia[i];
        int j;
        for(j=0; j<grs->dim; j++)
        {
            gruppo gs = grs->insieme[j];
            if(gs==g)
            {
                return grs;
            }
        }
    }

    return NULL;
}

void aggiornaTest(gruppi g)
{
    int i;
    for(i=0; i<g->dim; i++)
    {
        aggiornaFase(g->insieme[i]);
    }
}