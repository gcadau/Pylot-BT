/* Giovanni Cadau © */

#ifndef MOVIMENTO_H
#define MOVIMENTO_H

typedef struct movimento_s* movimento;

void creaMovimento(movimento* m, gruppo* gr, int dim, int n);
void liberaMovimento(movimento m);
void stampaMovimento(movimento m, FILE *f);

#endif //MOVIMENTO_H