/* Giovanni Cadau © */

#ifndef TESTA_H
#define TESTA_H

typedef struct testa_s* testa;

void creaTesta(testa* t, char* nome, float d11, float d12, float d21, float d22, char* line, float offset);
void liberaTesta(testa t);
void stampaTesta(testa t, FILE *f);
int getCod(testa t);
void setCod(testa t, int id);
void getOffsetSxeDxSuperficieTopologiaCelle(testa t, float* sx, float* dx);
void getOffsetAltoeBassoSuperficieTopologiaCelle(testa t, float* alto, float* basso);
void getOffsetSxeDxSuperficieTotaleOccupata(testa t, float* sx, float* dx);
void getOffsetAltoeBassoSuperficieTotaleOccupata(testa t, float* sx, float* dx);

#endif //TESTA_H