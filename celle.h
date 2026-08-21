/* Giovanni Cadau © */

#ifndef CELLE_H
#define CELLE_H

typedef enum estremo_s
{
    Alto,
    Basso,
    Destra,
    Sinistra
} estremo ;

enum orientamento_s
{
    ASx,
    ADx,
    BDx,
    BSx
} ;
typedef enum orientamento_s orientamento ;

typedef struct celle_s* celle;

void creaCelle(celle* c);
void liberaCelle(celle c);
void aggiungiCella(celle c, cella cel);
int checkEsistenzaCella(celle c, cella cel);
void stampaCelle(celle c, FILE *f);
void ordinaCelle(celle c, criterio crit);
void generaDistanze(celle c, double ***m);
void getNCellePiuVicine(celle c, cella a, int N, cella* vic);
cella getCellaPiuVicina(celle c, coordinata coor);
int getDimC(celle c);
cella* getInsieme(celle c);
int batteriaTestata(celle c);
void resetBatteria(celle c);
void calcolaDimensioniBatteria(celle c, float* base, float* altezza);
void calcolaEstremiBatteria(celle c, coordinata* coord, orientamento* start);
void estremiCelle(float* estremi, celle c);

#endif //CELLE_H