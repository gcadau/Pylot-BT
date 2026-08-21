/* Giovanni Cadau © */

#include <stdio.h>
#include <stdlib.h>
#include "coordinata.h"

struct coordinata_s
{
    float x;
    float y;
};

void creaCoordinata(coordinata* c, float x, float y)
{
    *c = malloc(sizeof(struct coordinata_s));
    (*c)->x = x;
    (*c)->y = y;
}

void liberaCoordinata(coordinata c)
{
    free(c);
}

void stampaCoordinata(coordinata c, FILE *f)
{
    fprintf(f, "(%f, %f)", c->x, c->y);
}

float getAscissa(coordinata c)
{
    return c->x;
}

float getOrdinata(coordinata c)
{
    return c->y;
}

int equalCoordinata(coordinata c, coordinata d)
{
    if(c->x==d->x && c->y==d->y)
        return 1;
    return 0;
}