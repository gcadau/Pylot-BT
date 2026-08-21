/* Giovanni Cadau © */

#include <stdio.h>
#include <stdlib.h>
#include "coordinata.h"
#include "topologia.h"

struct topologia_s
{
    //cella 0 in (a, b)
    coordinata* offSet;  //altre celle in (a+coordinata[i]->x, b+coordinata[i]->y)
    int dimensione;
};

void creaTopologia(topologia* t, int dim, coordinata* c)
{
    *t = malloc(sizeof(struct topologia_s));
    (*t)->dimensione = dim;

    (*t)->offSet = c;
}

void liberaTopologia(topologia t)
{
    int i;
    for(i=0; i<t->dimensione; i++)
    {
        liberaCoordinata(t->offSet[i]);
    }
    free(t->offSet);

    free(t);
}

int equalTopologia(topologia t, topologia s)
{
    int i;
    if(t->dimensione!=s->dimensione)
        return 0;
    for(i=0; i<t->dimensione; i++)
    {
        if(!equalCoordinata(t->offSet[i], s->offSet[i]))
            return 0;
    }

    return 1;
}