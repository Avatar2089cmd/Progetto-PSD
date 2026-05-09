#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

#include "base.h"

typedef struct Prenotazione *Prenotazione; //puntatore opaco alla struttura Prenotazione

Prenotazione crea_prenotazione(const char *matricola, Data data, FasciaOraria fascia); //costruttore
void distruggi_prenotazione(Prenotazione p); //distruttore

//funzioni setter per modificare la prenotazione

void prenotazione_set_posto(Prenotazione p, int posto); 
void annulla_prenotazione(Prenotazione p);
void prenotazione_set_stato(Prenotazione p, StatoPrenotazione stato);

//funzioni getter per accedere ai dati della prenotazione

int prenotazione_get_posto(const Prenotazione p);
char* prenotazione_get_matricola(const Prenotazione p);
Data prenotazione_get_data(const Prenotazione p);
FasciaOraria prenotazione_get_fascia(const Prenotazione p);
int prenotazione_get_check_in(const Prenotazione p);
int prenotazione_get_check_out(const Prenotazione p);
StatoPrenotazione prenotazione_get_stato(const Prenotazione p);



#endif // PRENOTAZIONE_H