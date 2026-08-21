/* Giovanni Cadau © */

#ifndef TOPOLOGIA_H
#define TOPOLOGIA_H

typedef struct topologia_s* topologia;

void creaTopologia(topologia* t, int dim, coordinata* c);
void liberaTopologia(topologia t);
int equalTopologia(topologia t, topologia s);

#endif //TOPOLOGIA_H