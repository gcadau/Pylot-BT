/* Giovanni Cadau © */

#include <stdio.h>
#include <stdlib.h>
#include "coordinata.h"
#include "topologia.h"
#include "cella.h"
#include "celle.h"
#include "gruppo.h"
#include "testa.h"
#include "teste.h"

#define START 4
#define CRESCITA 2

struct teste_s
{
    testa* insieme;
    int dim;
    int realDim;
};

void creaTeste(teste* t)
{
    *t = malloc(sizeof(struct teste_s));
    (*t)->dim = 0;
    (*t)->realDim = START;
    (*t)->insieme = malloc(((*t)->realDim) * sizeof(testa));
}

void liberaTeste(teste t)
{
    free(t->insieme);
    free(t);
}

void aggiungiTesta(teste t, testa tes)
{
    if((t->dim) + 1 > (t->realDim) )
    {
        (t->realDim) *= CRESCITA;
        t->insieme = realloc(t->insieme, (t->realDim) * sizeof(testa));
    }

    setCod(tes, t->dim);
    t->insieme[(t->dim)++] = tes;
}

void stampaTeste(teste t, FILE *f)
{
    int i;
    for(i=0; i<t->dim; i++)
    {
        stampaTesta(t->insieme[i], f);
        fprintf(f, "\n");
    }
}

int getDimT(teste t)
{
    return t->dim;
}

int checkCompatibilitaTeste(teste t, int cod1, int cod2, gruppo g1, gruppo g2)
{
    testa t1 = t->insieme[cod1];
    float sx1, dx1;
    getOffsetSxeDxSuperficieTotaleOccupata(t1, &sx1, &dx1);
    testa t2 = t->insieme[cod2];
    float sx2, dx2;
    getOffsetSxeDxSuperficieTotaleOccupata(t2, &sx2, &dx2);
    coordinata c1 = posizioneMedia(g1);
    coordinata c2 = posizioneMedia(g2);
    if(getAscissa(c1)>=getAscissa(c2))
    {
        if(getAscissa(c2)+dx2 >= getAscissa(c1)-sx1)
        {
            return 0;
        }
    }
    else
    {
            return 0;
    }

    return 1;
}

int gruppoCompatibile(teste t, gruppo g)
{
    int i;
    for(i=0; i<t->dim; i++)
    {
        testa tes = t->insieme[i];
        float sx, dx, alto, basso;
        getOffsetSxeDxSuperficieTopologiaCelle(tes, &sx, &dx);
        getOffsetAltoeBassoSuperficieTopologiaCelle(tes, &alto, &basso);
        coordinata c = posizioneMedia(g);
        float* estremi = malloc(4* sizeof(float));
        estremiGruppo(estremi, g);
        if( (getAscissa(c)+dx <= estremi[Destra]) || (getAscissa(c)-sx >= estremi[Sinistra]) || (getOrdinata(c)+alto <= estremi[Alto]) || (getOrdinata(c)-basso >= estremi[Basso]) )
        {
            free(estremi);
            return 0;
        }
        free(estremi);
    }

    return 1;
}