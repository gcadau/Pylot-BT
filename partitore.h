/* Giovanni Cadau © */

#ifndef PARTITORE_H
#define PARTITORE_H

struct partitore_s
{
    int** v;
    int dim;
    int dimInterna;
};

typedef struct partitore_s* Partitore;

void creaPartitore(Partitore * p, int dim);
void liberaPartitore(Partitore p);

#endif //PARTITORE_H
