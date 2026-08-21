/* Giovanni Cadau © */

#ifndef GRUPPO_H
#define GRUPPO_H

typedef struct gruppo_s* gruppo;

void creaGruppo(gruppo* g);
void impostaGruppo(gruppo g, cella* cel, int q);
int getFase(gruppo g);
int getMaxFase(gruppo g);
void aggiornaFase(gruppo g);
void resetFase(gruppo g);
topologia getTopologia(gruppo g);
coordinata posizioneMedia(gruppo g);
void liberaGruppo(gruppo g);
int GRUPPOleq(gruppo a, gruppo b); //Relazione d'ordine totale: criterio di cardinalità insieme decescente
int GRUPPOgt(gruppo a, gruppo b);  //Relazione d'ordine totale: criterio di cardinalità insieme decescente
void stampaGruppo(gruppo g, FILE *f);
double distanzaG(gruppo a, gruppo b);
int checkPresenzaCella(gruppo g, cella c);
void testGruppo(gruppo g);
void setGruppoNullo(gruppo* g);
void setGruppoVuoto(gruppo* g);
void setGruppoSuperfluo(gruppo* g);
int isGruppoNullo(gruppo g);
int isGruppoVuoto(gruppo g);
int isGruppoSuperfluo(gruppo g);
void estremiGruppo(float* e, gruppo g);
gruppo getPrec(gruppo vuoto);
void setPrec(gruppo vuoto, gruppo prec);
int getDimensione(gruppo g);

#endif //GRUPPO_H