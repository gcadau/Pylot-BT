/* Giovanni Cadau © */

#include <stdio.h>
#include <string.h>
#include "utility.h"
#include "coordinata.h"
#include "topologia.h"
#include "cella.h"
#include "celle.h"
#include "gruppo.h"
#include "gruppi.h"
#include "testa.h"
#include "teste.h"
#include "allocazione.h"

#define DAFILE 1
#define UFFICIALE 0
#define ALTRO 0

int acquisisciDatiCelle(void** gen, int* stop, char* nome, float* x, float* y);
int acquisisciDatiTeste(void** gen, char* nome, float* x1, float* y1, float* x2, float* y2, char* l, float* offset);

void allocaCelle(celle* cel)
{
    cella c;
    creaCelle(& (*cel));
    void* service = NULL;
    int stop = 0;
    char nome[L]; float x; float y;

    while(!stop)
    {
        if(acquisisciDatiCelle(&service, &stop, nome, &x, &y))
        {
            creaCella(&c, nome, x, y);
            aggiungiCella(*cel, c);
        }
        else
        {
            liberaCelle(*cel);
            fprintf(stderr, "Errore durante il caricamento dei dati, celle non allocate\n");
        }
    }
}

void allocaTeste(teste* tes, int n)
{
    testa t;
    creaTeste(& (*tes));
    void* service = NULL;
    char nome[L]; char line[L]; float x1; float y1; float x2; float y2; float offset;

    int i;
    for(i=0; i<n; i++)
    {
        if(acquisisciDatiTeste(&service, nome, &x1, &y1, &x2, &y2, line, &offset))
        {
            creaTesta(&t, nome, x1, y1, x2, y2, line, offset);
            aggiungiTesta(*tes, t);
        }
        else
        {
            liberaTeste(*tes);
            fprintf(stderr, "Errore durante il caricamento dei dati, celle non allocate\n");
        }
    }
}

int acquisisciDatiCelle(void** gen, int* stop, char* nome, float* x, float* y)
{

#if DAFILE

    if(*gen==NULL)
    {
        FILE* f = fopen(FILE_INPUT_CELLE, "r");
        if(f==NULL)     return 0;
        char line[LLENGTH];
        fgets(line, LLENGTH, f);
        if ( fscanf(f, "%s %f %f", nome, x, y)!=3 )
        {
            *stop=1;
            fclose(f);
        }

        *gen = (void*) f;
    }
    else
    {
        FILE* f = (FILE*) (*gen);
        if ( fscanf(f, "%s %f %f", nome, x, y)!=3 )
        {
            *stop=1;
            fclose(f);
        }
    }

#elif UFFICIALE

    #elif ALTRO

#else

#endif


    return 1;
}

int acquisisciDatiTeste(void** gen, char* nome, float* x1, float* y1, float* x2, float* y2, char* l, float* offset)
{

#if DAFILE

    if(*gen==NULL)
    {
        FILE* f = fopen(FILE_INPUT_TESTE, "r");
        if(f==NULL)     return 0;
        fgets(l, LLENGTH, f);

        if (fscanf(f, "%s %f (%f) %f (%f) %f", nome, x1, x2, y1, y2, offset) != 6 )
        {
            fclose(f);
        }

        *gen = (void*) f;
    }
    else
    {
        FILE* f = (FILE*) (*gen);
        if (fscanf(f, "%s %f (%f) %f (%f) %f", nome, x1, x2, y1, y2, offset) != 6 )
        {
            fclose(f);
        }
    }

#elif UFFICIALE

    #elif ALTRO

#else

#endif


    return 1;
}