/* Giovanni Cadau © */

#ifndef COORDINATA_H
#define COORDINATA_H

typedef struct coordinata_s* coordinata;

void creaCoordinata(coordinata* c, float x, float y);
void liberaCoordinata(coordinata c);
void stampaCoordinata(coordinata c, FILE *f);
float getAscissa(coordinata c);
float getOrdinata(coordinata c);
int equalCoordinata(coordinata c, coordinata d);

#endif //COORDINATA_H