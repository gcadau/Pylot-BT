/* Giovanni Cadau © */

#ifndef COMBINATORE_H
#define COMBINATORE_H

struct combinatore_s
{
    int** v;
    int dim;
    int dimInterna;
};

typedef struct combinatore_s* Combinatore;

void creaCombinatore(Combinatore* c, int* valori, int dim);
void liberaCombinatore(Combinatore c);

#endif //COMBINATORE_H