/* Giovanni Cadau © */

#ifndef FORMA_H
#define FORMA_H

typedef struct forma_s* forma;

void creaForma(forma* f, float d1, float d2, char* line);
void liberaForma(forma f);
void stampaForma(forma f, FILE *ff);
void getSxDx(forma f, float* sx, float* dx, float offset);
void getAltoBasso(forma f, float* alto, float* basso);

#endif //FORMA_H