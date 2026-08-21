/* Giovanni Cadau © */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "coordinata.h"
#include "distanza.h"
#include "cella.h"
#include "sortingCelle.h"
#include "celle.h"

#define START 4
#define CRESCITA 2

float Estremo(celle c, estremo e);

struct celle_s
{
    cella* insieme;
    int dim;
    int realDim;
};

void creaCelle(celle* c)
{
    *c = malloc(sizeof(struct celle_s));
    (*c)->dim = 0;
    (*c)->realDim = START;
    (*c)->insieme = malloc(((*c)->realDim)*sizeof(cella));
}

void liberaCelle(celle c)
{
    free(c->insieme);
    free(c);
}

void aggiungiCella(celle c, cella cel)
{
    if( (c->dim)+1 > (c->realDim) )
    {
        (c->realDim) *= CRESCITA;
        c->insieme = realloc(c->insieme, (c->realDim)*sizeof(cella));
    }

    setId(cel, c->dim);
    c->insieme[(c->dim)++] = cel;
}

int checkEsistenzaCella(celle c, cella cel)
{
    int i;
    for(i=0; i<c->dim; i++)
    {
        if(equalCella(c->insieme[i], cel))
            return 1;
    }

    return 0;
}

void stampaCelle(celle c, FILE *f)
{
    int i;
    for(i=0; i<c->dim; i++)
    {
        stampaCella(c->insieme[i], f);
        fprintf(f, "\n");
    }
}

void ordinaCelle(celle c, criterio crit)
{
    switch(crit)
    {
        case ascissa:
            SortCelle(c->insieme, c->dim, ascissa);
            break;
        case ordinata:
            SortCelle(c->insieme, c->dim, ordinata);
            break;
        case matrice:
            SortCelle(c->insieme, c->dim, matrice);
            break;
        case altro:
            break;
        default:
            break;
    }
}

void generaDistanze(celle c, double*** m)
{
    int i, j;

    *m = malloc((c->dim) * sizeof(double*));
    for(i=0; i<c->dim; i++)
    {
        (*m)[i] = malloc((c->dim) * sizeof(double));
        for(j=0; j<c->dim; j++)
        {
            (*m)[i][j] = distanzaC(c->insieme[i], c->insieme[j]);
        }
    }
}

void getNCellePiuVicine(celle c, cella a, int N, cella* vic)
{
    int round=1;
    int index=0;
    double* mins = malloc(N* sizeof(double));
    mins[0] = 0;

    while(round<=N)
    {
        double min = DBL_MAX;
        int i;
        for(i=0; i<c->dim; i++)
        {
            double d = distanzaC(a, c->insieme[i]);
            if(d<min && d>mins[round-1])
            {
                min = d;
                index = i;
            }
        }

        mins[round] = min;
        vic[round-1] = c->insieme[index];
        round++;
    }

    free(mins);
}

cella getCellaPiuVicina(celle c, coordinata coor)
{
    double min = DBL_MAX;
    int index=0;

    int i;
    for(i=0; i<c->dim; i++)
    {
        double d = distanza(coor, getCoordinata(c->insieme[i]));
        if(d<min)
        {
            min = d;
            index = i;
        }
    }

    return c->insieme[index];
}

int getDimC(celle c)
{
    return c->dim;
}

cella* getInsieme(celle c)
{
    return c->insieme;
}

int batteriaTestata(celle c)
{
    int i;
    for(i=0; i<c->dim; i++)
    {
        if(!isTest(c->insieme[i]))
        {
            return 0;
        }
    }

    return 1;
}

void resetBatteria(celle c)
{
    int i;
    for(i=0; i<c->dim; i++)
    {
        reset(c->insieme[i]);
    }
}

void calcolaDimensioniBatteria(celle c, float* base, float* altezza)
{
    *base = Estremo(c, Alto) - Estremo(c, Basso);
    *altezza = Estremo(c, Destra) - Estremo(c, Sinistra);
}

void calcolaEstremiBatteria(celle c, coordinata* coord, orientamento* start)
{
    if(start!=NULL)     *start = ASx;
    coordinata c1; creaCoordinata(&c1, Estremo(c, Sinistra), Estremo(c, Alto));
    coord[0] = c1;
    coordinata c2; creaCoordinata(&c2, Estremo(c, Destra), Estremo(c, Alto));
    coord[1] = c2;
    coordinata c3; creaCoordinata(&c3, Estremo(c, Destra), Estremo(c, Basso));
    coord[2] = c3;
    coordinata c4; creaCoordinata(&c4, Estremo(c, Sinistra), Estremo(c, Basso));
    coord[3] = c4;
}

float Estremo(celle c, estremo e)
{
    int i;
    float m;
    float v;
    switch(e)
    {
        case Alto:
        {
            m = FLT_MIN;
            for(i=0; i<c->dim; i++)
            {
                if((v=getOrdinata(getCoordinata(c->insieme[i])))>m)
                {
                    m = v;
                }
            }
            break;
        }
        case Basso:
        {
            m = FLT_MAX;
            for(i=0; i<c->dim; i++)
            {
                if((v=getOrdinata(getCoordinata(c->insieme[i])))<m)
                {
                    m = v;
                }
            }
            break;
        }
        case Destra:
        {
            m = FLT_MIN;
            for(i=0; i<c->dim; i++)
            {
                if((v=getAscissa(getCoordinata(c->insieme[i])))>m)
                {
                    m = v;
                }
            }
            break;
        }
        case Sinistra:
        {
            m = FLT_MAX;
            for(i=0; i<c->dim; i++)
            {
                if((v=getAscissa(getCoordinata(c->insieme[i])))<m)
                {
                    m = v;
                }
            }
            break;
        }
        default:
            return 0;
    }

    return m;
}

void estremiCelle(float* estremi, celle c)
{
    estremi[Alto] = Estremo(c, Alto);
    estremi[Basso] = Estremo(c, Basso);
    estremi[Sinistra] = Estremo(c, Sinistra);
    estremi[Destra] = Estremo(c, Destra);
}