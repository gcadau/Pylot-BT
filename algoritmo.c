/* Giovanni Cadau © */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include "utility.h"
#include "combinatore.h"
#include "matrix.h"
#include "coordinata.h"
#include "topologia.h"
#include "cella.h"
#include "celle.h"
#include "gruppo.h"
#include "sortingGruppi.h"
#include "gruppi.h"
#include "movimento.h"
#include "soluzione.h"
#include "testa.h"
#include "teste.h"
#include "allocazione.h"
#include "algoritmo.h"

#define PIUVICINE 4

void definisciNumeroTeste(int* n);
void generaInsiemiDiCelle(celle c, gruppi* gr);
void definisciNumeroMaxCelle(int* n);
void path(celle c, int card, Matrice m);
void pathRic(cella u, celle c, int n, int card, int *coll, Matrice m);
bool movimentoTeste(teste t, celle c, gruppi g);
bool movimentoTesteRic(gruppo* attuale, int dim, teste t, celle c, gruppi g, int count, int* best, soluzione* s, movimento* movs);
void estraiGruppi(gruppo** start, teste t, celle c, gruppi g);
bool sceltaGruppi(gruppo* i, gruppo* scelte, int dim, teste tes, gruppi g);
void eseguiTest(gruppo* g, int dim, gruppi gr);
void resetTest(celle c, gruppi g);
void ordinaPerCardinalita(gruppo* g);
void salvaDatiPerBacktrack(celle c, gruppi g, int* test, int* fasi);
void BackTrack(celle c, gruppi g, int* testt, int* fasi);

void trovaPercorso()
{
    celle c;
    allocaCelle(&c);

    teste t; int nTeste;
    definisciNumeroTeste(&nTeste);
    allocaTeste(&t, nTeste);

    gruppi g;
    generaInsiemiDiCelle(c, &g);

    bool successo;
    successo = movimentoTeste(t, c, g);
}

void definisciNumeroTeste(int* n)
{
    FILE* f;
    if((f=fopen(FILE_INPUT_CONFIGURAZIONI, "r"))==NULL)
    {
        fprintf(stderr, "Errore nel caricamento del file di configurazione.\n");
        return;
    }

    *n=0;
    fscanf(f, "%*s %d", n);

    if(*n<=0)
    {
        fprintf(stderr, "Errore nel file di configurazione.\n");
        return;
    }
}

void generaInsiemiDiCelle(celle c, gruppi* gr)
{
    int card;

    definisciNumeroMaxCelle(&card);
    Matrice m;
    creaMatrice(&m);
    int i, j;
    for(i=1; i<=card; i++)
    {
        path(c, i, m);
    }

    creaGruppi(gr);
    for(i=0; i<m->dim; i++)
    {
        gruppo g;
        creaGruppo(&g);
        int a;
        j=0;
        cella ins[L];
        while((a=m->v[i][j++])!=-1)
        {
            cella cel = (getInsieme(c))[a];
            ins[j-1] = cel;
        }
        int quantita = j-1;
        impostaGruppo(g, ins, quantita);
        aggiungiGruppo(*gr, g);
    }

    raggruppaPerTopologia(*gr);
}

void definisciNumeroMaxCelle(int* n)
{
    FILE* f;
    if((f=fopen(FILE_INPUT_CONFIGURAZIONI, "r"))==NULL)
    {
        fprintf(stderr, "Errore nel caricamento del file di configurazione.\n");
        return;
    }

    fscanf(f, "%*s %*d\n%*s %*s %*s %*s %*s %d\n", n);

    if(*n<=0)
    {
        fprintf(stderr, "Errore nel file di configurazione.\n");
        return;
    }
}

void path(celle c, int card, Matrice m)
{
    cella* insieme = getInsieme(c);
    int dim = getDimC(c);

    int* coll = malloc(card*sizeof(int));
    int i;
    for(i=0; i<dim; i++)
    {
        cella u = insieme[i];
        int n = 0;

        pathRic(u, c, n, card, coll, m);
    }

    free(coll);
}

void pathRic(cella u, celle c, int n, int card, int *coll, Matrice m)
{
    coll[n++] = getId(u);
    if(n!=card)
    {
        cella* vicine = malloc(PIUVICINE*sizeof(cella));
        getNCellePiuVicine(c, u, PIUVICINE, vicine);
        int j;
        for(j=0; j<PIUVICINE; j++)
        {
            cella s = vicine[j];
            int k;
            int giaCons = 0;
            for(k=0; k<n; k++)
            {
                if(coll[k]==getId(s))
                {
                    giaCons = 1;
                    break;
                }
            }
            if(!giaCons) pathRic(s, c, n, card, coll, m);
        }
        free(vicine);
    }
    else
    {
        coll[n] = -1;
        if(!checkDuplicati(m, coll))
            aggiungiVettore(m, coll);
    }
}

bool movimentoTeste(teste t, celle c, gruppi g)
{
    bool successo = false;
    gruppo** estratti = malloc((getDimT(t))* sizeof(gruppo*));
    estraiGruppi(estratti, t, c, g);
    gruppo* start = malloc((getDimT(t))* sizeof(gruppo));

    Combinatore comb;
    int* val = malloc(getDimT(t)* sizeof(int));
    int i, j, k;
    for(i=0; i<getDimT(t); i++)
    {
        k = 0;
        while(!isGruppoNullo(estratti[i][k++]));
        k--;
        val[i] = k;
    }
    creaCombinatore(&comb, val, getDimT(t));
    free(val);

    int best = INT_MAX;
    soluzione s = NULL;
    int caso = 0;
    while(caso<comb->dim)
    {
        int acc = 1;
        for(i=0; i<getDimT(t); i++)
        {
            start[i] = estratti[i][comb->v[caso][i]];
            int ok = 1;
            for(j=0; j<i; j++)
            {
                if(!checkCompatibilitaTeste(t, i, j, start[i], start[j])) // + ottimizazzione al contrario
                {
                    ok = 0;
                    break;
                }
            }
            if(!ok)
            {
                acc = 0;
                break;
            }
        }

        if(acc)
        {
            movimento* movs = malloc(MAX_MOV_TOLLERATI* sizeof(movimento));
            eseguiTest(start, getDimT(t), g);
            int count = 1;
            movimento m; creaMovimento(&m, start, getDimT(t), count); movs[count-1] = m;
            if(movimentoTesteRic(start, getDimT(t), t, c, g, count + 1, &best, &s, movs))
                successo = true;
            resetTest(c, g);
            free(movs);
        }
        caso++;
    }

    if(successo)
        stampaSoluzione(s);

    return successo;
}

void estraiGruppi(gruppo** start, teste t, celle c, gruppi g)
{
    float base; float altezza;
    calcolaDimensioniBatteria(c, &base, &altezza);
    float porzioneX = base / (float) getDimT(t);
    float porzioneY = altezza / (float) getDimT(t);
    coordinata* coords = malloc(4*sizeof(coordinata));
    calcolaEstremiBatteria(c, coords, NULL);
    cella* cel = malloc(getDimT(t)* sizeof(cella));
    coordinata coor = coords[ASx];
    int i;
    for(i=0; i<getDimT(t); i++)
    {
        cel[i] = getCellaPiuVicina(c, coor);
        float asc = getAscissa(coor);
        float ord = getOrdinata(coor);
        liberaCoordinata(coor);
        creaCoordinata(&coor, asc+porzioneX, ord);
        getGruppiConCella(g, cel[i], &(start[i]));
        //ordinaPerCardinalita(start[i]);
    }
    liberaCoordinata(coor);

    for(i=0; i<4; i++)
    {
        if(i!=ASx)  liberaCoordinata(coords[i]);
    }
    free(coords);
    free(cel);
}

bool movimentoTesteRic(gruppo* attuale, int dim, teste t, celle c, gruppi g, int count, int* best, soluzione* s, movimento* movs)
{
    if(count-1 > *best)
        return false;

    if(batteriaTestata(c))
    {
        *best = count-1;
        memorizza(s, count-1, movs);
        return true;
    }


    gruppo* next = malloc(dim*sizeof(gruppo));
    int j;
    bool succ[4];
    gruppo vuoto; setGruppoVuoto(&vuoto);
    int* test = malloc(getDimC(c)*sizeof(int)); int* fasi = malloc(getDimG(g)*sizeof(int));

    for(j=0; j<dim; j++)    next[j] = NULL;
    if(!sceltaGruppi(attuale, next, dim, t, g))      return false;
    salvaDatiPerBacktrack(c, g, test, fasi);
    eseguiTest(next, dim, g);
    movimento m; creaMovimento(&m, next, getDimT(t), count); movs[count-1] = m;
    succ[0] = movimentoTesteRic(next, dim, t, c, g, count + 1, best, s, movs);
    BackTrack(c, g, test, fasi);

    for(j=0; j<dim; j++)    next[j] = NULL;
    next[0] = vuoto; setPrec(next[0], attuale[0]);
    if(!sceltaGruppi(attuale, next, dim, t, g))      return false;
    salvaDatiPerBacktrack(c, g, test, fasi);
    eseguiTest(next, dim, g);
    movimento mm; creaMovimento(&mm, next, getDimT(t), count); movs[count-1] = mm;
    succ[1] = movimentoTesteRic(next, dim, t, c, g, count + 1, best, s, movs);
    BackTrack(c, g, test, fasi);

    for(j=0; j<dim; j++)    next[j] = NULL;
    next[dim-1] = vuoto; setPrec(next[dim-1], attuale[dim-1]);
    if(!sceltaGruppi(attuale, next, dim, t, g))      return false;
    salvaDatiPerBacktrack(c, g, test, fasi);
    eseguiTest(next, dim, g);
    movimento mmm; creaMovimento(&mmm, next, getDimT(t), count); movs[count-1] = mmm;
    succ[2] = movimentoTesteRic(next, dim, t, c, g, count + 1, best, s, movs);
    BackTrack(c, g, test, fasi);

    for(j=0; j<dim; j++)    next[j] = NULL;
    next[0] = vuoto; setPrec(next[0], attuale[0]); next[dim-1] = vuoto; setPrec(next[dim-1], attuale[dim-1]);
    if(!sceltaGruppi(attuale, next, dim, t, g))      return false;
    salvaDatiPerBacktrack(c, g, test, fasi);
    eseguiTest(next, dim, g);
    movimento mmmm; creaMovimento(&mmmm, next, getDimT(t), count); movs[count-1] = mmmm;
    succ[3] = movimentoTesteRic(next, dim, t, c, g, count + 1, best, s, movs);
    BackTrack(c, g, test, fasi);


    free(test); free(fasi);
    for(j=0; j<4; j++)
    {
        if(succ[j])
            return true;
    }
    return false;
}

bool sceltaGruppi(gruppo* i, gruppo* scelte, int dim, teste tes, gruppi g)
{
    int l;
    for(l=0; l<dim; l++)
    {
        if(!isGruppoVuoto(scelte[l]))
        {
            int fase = -1;
            gruppo p = i[l];
            if(isGruppoVuoto(p))    p = getPrec(p);
            gruppi elementi = getRaggruppamentoPerTopologiaContenenteGruppo(g, p);
            gruppo* t = getGruppi(elementi);
            int dimT = getDimG(elementi);
            int j;
            double min = DBL_MAX;
            while(scelte[l] == NULL)
            {
                fase++;
                for(j=0; j<dimT; j++)
                {
                    if((getFase(t[j]))==fase)
                    {
                        double d = distanzaG(p, t[j]);
                        if(d<min && d!=0) // + comparazione e mediazione
                        {
                            int k;
                            int ok = 1;
                            for(k=0; k<l; k++)
                            {
                                if(!checkCompatibilitaTeste(tes, l, k, t[j], scelte[k])) // + ottimizazzione al contrario
                                {
                                    ok = 0;
                                    break;
                                }
                            }
                            if(ok)
                            {
                                min = distanzaG(p, t[j]);
                                scelte[l] = t[j];
                            }
                        }
                    }
                }
            }
            if(scelte[l]==NULL)
            {
                printf("Nessun movimento possibile.\n");
                return false;
            }
        }
    }

    return true;
}

void eseguiTest(gruppo* g, int dim, gruppi gr)
{
    int i;
    for(i=0; i<dim; i++)
    {
        testGruppo(g[i]);
    }
    aggiornaTest(gr);
}

void resetTest(celle c, gruppi g)
{
    resetBatteria(c);

    gruppo* grs = getGruppi(g);
    int dim = getDimG(g);
    int i;
    for(i=0; i<dim; i++)
    {
        resetFase(grs[i]);
    }
}

void ordinaPerCardinalita(gruppo* g)
{
    int dim = 0;
    while(!isGruppoNullo(g[dim++]));
    SortGruppi(g, --dim);
}

void salvaDatiPerBacktrack(celle c, gruppi g, int* test, int* fasi)
{
    int i;

    cella* cel = getInsieme(c);
    int dimC = getDimC(c);
    for(i=0; i<dimC; i++)
        test[i] = isTest(cel[i]);

    gruppo* gru = getGruppi(g);
    int dimG = getDimG(g);
    for(i=0; i<dimG; i++)
        fasi[i] = getFase(gru[i]);
}

void BackTrack(celle c, gruppi g, int* testt, int* fasi)
{
    int i;

    cella* cel = getInsieme(c);
    int dimC = getDimC(c);
    for(i=0; i<dimC; i++)
    {
        if(testt[i])
            test(cel[i]);
        else
            reset(cel[i]);
    }

    gruppo* gru = getGruppi(g);
    int dimG = getDimG(g);
    for(i=0; i<dimG; i++)
    {
        setFase(gru[i], fasi[i]);
    }
}