/* Giovanni Cadau © */

#ifndef CELLA_H
#define CELLA_H

typedef enum criterio_s
{
    ascissa,
    ordinata,
    matrice,
    altro
} criterio ;

typedef struct cella_s* cella;

void creaCella(cella* c, char* nome, float x, float y);
void liberaCella(cella c);
void stampaCella(cella c, FILE *f);
int CELLAleq(cella a, cella b, criterio c);
int CELLAgt(cella a, cella b, criterio c);
double distanzaC(cella a, cella b);
int getId(cella c);
void setId(cella c, int cod);
int isTest(cella c);
void test(cella c);
void reset(cella c);
coordinata getCoordinata(cella c);
int equalCella(cella a, cella b);

#endif //CELLA_H