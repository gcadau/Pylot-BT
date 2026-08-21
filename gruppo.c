/* Giovanni Cadau © */

#include <stdio.h>
#include <stdlib.h>
#include "coordinata.h"
#include "distanza.h"
#include "topologia.h"
#include "cella.h"
#include "celle.h"
#include "gruppo.h"

struct gruppo_s
{
    celle insieme;
    int fase;
    topologia topologia;
    coordinata baricentro;

    gruppo prec;
};

void setBaricentro(gruppo g);
coordinata getBaricentro(gruppo g);
void setTopologia(gruppo g);
void setFase(gruppo g, int fase);

void creaGruppo(gruppo* g)
{
    *g = malloc(sizeof(struct gruppo_s));

    creaCelle(&(*g)->insieme);

    (*g)->fase = 0;

    (*g)->topologia = NULL;

    (*g)->baricentro = NULL;

    (*g)->prec = NULL;
}

void impostaGruppo(gruppo g, cella* cel, int q)
{
    int i;
    for(i=0; i<q; i++)
    {
        aggiungiCella(g->insieme, cel[i]);
    }

    setBaricentro(g);

    setTopologia(g);
}

void liberaGruppo(gruppo g)
{
    if(g->baricentro!=NULL)     liberaCoordinata(g->baricentro);
    if(g->topologia!=NULL)      liberaTopologia(g->topologia);

    free(g);
}

int GRUPPOleq(gruppo a, gruppo b)
{
    return getDimC(a->insieme)>=getDimC(b->insieme);
}

int GRUPPOgt(gruppo a, gruppo b)
{
    return getDimC(a->insieme)<getDimC(b->insieme);
}

void setBaricentro(gruppo g)
{
    cella* ins = getInsieme(g->insieme);
    int dim = getDimC(g->insieme);

    float x = 0;
    float y = 0;

    int i;
    for(i=0; i<dim; i++)
    {
        x += getAscissa(getCoordinata(ins[i]));
        y += getOrdinata(getCoordinata(ins[i]));
    }

    x /= (float) dim;
    y /= (float) dim;

    coordinata c;
    creaCoordinata(&c, x, y);

    g->baricentro = c;
}

coordinata getBaricentro(gruppo g)
{
    return g->baricentro;
}

coordinata posizioneMedia(gruppo g)
{
    return getBaricentro(g);
}

int getFase(gruppo g)
{
    return g->fase;
}

void setFase(gruppo g, int fase)
{
    g->fase = fase;
}

void aggiornaFase(gruppo g)
{
    int aggiornamento = 0;
    int i;
    for(i=0; i<getDimC(g->insieme); i++)
    {
         if(isTest((getInsieme(g->insieme))[i]))
         {
             aggiornamento++;
         }
    }

    setFase(g, aggiornamento);
}

void resetFase(gruppo g)
{
    g->fase = 0;
}

int getMaxFase(gruppo g)
{
    return getDimC(g->insieme);
}

topologia getTopologia(gruppo g)
{
    return g->topologia;
}

void setTopologia(gruppo g)
{
    celle c = g->insieme;
    ordinaCelle(c, matrice);
    cella* i = getInsieme(c);
    int dim = getDimC(c);
    cella c1 = i[0];
    coordinata* cc = malloc((dim-1)*sizeof(coordinata));
    int j;
    for(j=1; j<dim; j++)
    {
        float xOff = getAscissa(getCoordinata(i[j])) - getAscissa(getCoordinata(c1));
        float yOff = getOrdinata(getCoordinata(i[j])) - getOrdinata(getCoordinata(c1));
        coordinata coo; creaCoordinata(&coo, xOff, yOff);
        cc[j-1] = coo;
    }

    topologia t;
    creaTopologia(&t, dim-1, cc);
    g->topologia = t;
}

void stampaGruppo(gruppo g, FILE *f)
{
    if(!isGruppoVuoto(g)) stampaCelle(g->insieme, f);
    else    fprintf(f, "- Testa a riposo -\n");
}

double distanzaG(gruppo a, gruppo b)
{
    return distanza(getBaricentro(a), getBaricentro(b));
}

int checkPresenzaCella(gruppo g, cella c)
{
    return checkEsistenzaCella(g->insieme, c);
}

void testGruppo(gruppo g)
{
    int i;
    for(i=0; i<getDimC(g->insieme); i++)
        test((getInsieme(g->insieme))[i]);
}

void setGruppoNullo(gruppo* g)
{
    *g = malloc(sizeof(struct gruppo_s));

    (*g)->fase = -1;

    (*g)->topologia = NULL;

    (*g)->baricentro = NULL;

    (*g)->insieme = NULL;
}

void setGruppoVuoto(gruppo* g)
{
    *g = malloc(sizeof(struct gruppo_s));

    (*g)->fase = -2;

    (*g)->topologia = NULL;

    (*g)->baricentro = NULL;

    (*g)->insieme = NULL;
}

void setGruppoSuperfluo(gruppo* g)
{
    *g = malloc(sizeof(struct gruppo_s));

    (*g)->fase = -3;

    (*g)->topologia = NULL;

    (*g)->baricentro = NULL;

    (*g)->insieme = NULL;
}

int isGruppoNullo(gruppo g)
{
    return (g->fase==-1);
}

int isGruppoVuoto(gruppo g)
{
    return (g->fase==-2);
}

int isGruppoSuperfluo(gruppo g)
{
    return (g->fase==-3);
}

void estremiGruppo(float* e, gruppo g)
{
    estremiCelle(e, g->insieme);
}

gruppo getPrec(gruppo vuoto)
{
    gruppo g = vuoto->prec;
    if(!isGruppoVuoto(g))
        return g;
    else
        return getPrec(g);
}

void setPrec(gruppo vuoto, gruppo prec)
{
    vuoto->prec = prec;
}

int getDimensione(gruppo g)
{
    return getDimC(g->insieme);
}