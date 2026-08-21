/* Giovanni Cadau © */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coordinata.h"
#include "forma.h"
#include "topologia.h"
#include "cella.h"
#include "gruppo.h"
#include "gruppi.h"
#include "testa.h"

struct testa_s
{
    gruppi accettabili;
    int fase;

    char* nome;
    topologia caratteristiche;

    forma superficieTopologiaCelle;
    forma superficieTotaleOccupata;
    float offset;

    int cod;
};

void creaTesta(testa* t, char* nome, float d11, float d12, float d21, float d22, char* line, float offset)
{
    *t = malloc(sizeof(struct testa_s));
    (*t)->nome = strdup(nome);
    int fase = 0;
    (*t)->caratteristiche = NULL;
    //creaTopologia(&((*t)->caratteristiche), dim, c);
    creaForma(&((*t)->superficieTopologiaCelle), d11, d12, line);
    creaForma(&((*t)->superficieTotaleOccupata), d21, d22, line);
    (*t)->offset = offset / (float) 100;
    (*t)->cod = -1;
}

void liberaTesta(testa t)
{
    free(t->nome);
    liberaTopologia(t->caratteristiche);
    liberaForma(t->superficieTopologiaCelle);
    liberaForma(t->superficieTotaleOccupata);
    free(t);
}

void stampaTesta(testa t, FILE *f)
{
    fprintf(f, "Testa denominata: %s, con superficie occupata: ", t->nome);
    stampaForma(t->superficieTotaleOccupata, f);
}

int getCod(testa t)
{
    return t->cod;
}

void setCod(testa t, int id)
{
    t->cod = id;
}

void getOffsetSxeDxSuperficieTopologiaCelle(testa t, float* sx, float* dx)
{
    getSxDx(t->superficieTopologiaCelle, sx, dx, t->offset);
}

void getOffsetAltoeBassoSuperficieTopologiaCelle(testa t, float* alto, float* basso)
{
    getAltoBasso(t->superficieTopologiaCelle, alto, basso);
}

void getOffsetSxeDxSuperficieTotaleOccupata(testa t, float* sx, float* dx)
{
    getSxDx(t->superficieTotaleOccupata, sx, dx, t->offset);
}

void getOffsetAltoeBassoSuperficieTotaleOccupata(testa t, float* sx, float* dx)
{
    getSxDx(t->superficieTotaleOccupata, sx, dx, t->offset);
}