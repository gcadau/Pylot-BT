/* Giovanni Cadau © */

#ifndef MATRIX_H
#define MATRIX_H

struct matrice_s
{
    int** v;
    int dim;
    int realDim;
};

typedef struct matrice_s* Matrice;

void creaMatrice(Matrice* m);
void liberaMatrice(Matrice m);
void aggiungiVettore(Matrice m, int* a);
int checkDuplicati(Matrice m, int* v);

#endif //MATRIX_H