/* Giovanni Cadau © */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "coordinata.h"
#include "distanza.h"
#include "cella.h"

struct cella_s
{
    char* nome;
    coordinata coordinata;
    int test;
    int id;
};

void creaCella(cella* c, char* nome, float x, float y)
{
    *c = malloc(sizeof(struct cella_s));
    (*c)->nome = strdup(nome);
    creaCoordinata(&((*c)->coordinata), x, y);
    (*c)->test = 0;
    (*c)->id = -1;
}

void liberaCella(cella c)
{
    free(c->nome);
    liberaCoordinata(c->coordinata);
    free(c);
}

void stampaCella(cella c, FILE *f)
{
    fprintf(f, "Cella denominata: %s, con coordinate: ", c->nome);
    stampaCoordinata(c->coordinata, f);
}

int CELLAleq(cella a, cella b, criterio c)
{
    switch(c)
    {
        case ascissa:
            return ( getAscissa(a->coordinata) <= getAscissa(b->coordinata) );
            break;
        case ordinata:
            return ( getOrdinata(a->coordinata) <= getOrdinata(b->coordinata) );
            break;
        case matrice:
            if( getOrdinata(a->coordinata) == getOrdinata(b->coordinata) )
            {
                return ( getAscissa(a->coordinata) <= getAscissa(b->coordinata) );
            }
            else
            {
                return ( getOrdinata(a->coordinata) <= getOrdinata(b->coordinata) );
            }
            break;
        case altro:
            return 1;
            break;
        default:
            return 1;
            break;
    }
}

int CELLAgt(cella a, cella b, criterio c)
{
    switch(c)
    {
        case ascissa:
            return ( getAscissa(a->coordinata) > getAscissa(b->coordinata) );
            break;
        case ordinata:
            return ( getOrdinata(a->coordinata) > getOrdinata(b->coordinata) );
            break;
        case matrice:
            if( getOrdinata(a->coordinata) == getOrdinata(b->coordinata) )
            {
                return ( getAscissa(a->coordinata) > getAscissa(b->coordinata) );
            }
            else
            {
                return ( getOrdinata(a->coordinata) > getOrdinata(b->coordinata) );
            }
            break;
        case altro:
            return -1;
            break;
        default:
            return -1;
            break;
    }
}

double distanzaC(cella a, cella b)
{
    return distanza(getCoordinata(a), getCoordinata(b));
}

int getId(cella c)
{
    return c->id;
}

void setId(cella c, int cod)
{
    c->id = cod;
}

int isTest(cella c)
{
    return (c->test == 1);
}

void test(cella c)
{
    c->test = 1;
}

void reset(cella c)
{
    c->test = 0;
}

coordinata getCoordinata(cella c)
{
    return c->coordinata;
}

int equalCella(cella a, cella b)
{
    return (strcmp(a->nome, b->nome)==0);
}