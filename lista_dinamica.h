#ifndef LISTA_DINAMICA_H
#define LISTA_DINAMICA_H

#include "prenotazione.h"

typedef struct listaPrenotazioni *ListaPrenotazioni;

//funzioni per la gestione della lista di prenotazioni
ListaPrenotazioni crea_lista_prenotazioni();
void distruggi_lista_prenotazioni(ListaPrenotazioni lista);
int aggiungi_prenotazione(ListaPrenotazioni lista, Prenotazione p);
int rimuovi_prenotazione(ListaPrenotazioni lista, const char *matricola, Data data, FasciaOraria fascia);
Prenotazione cerca_prenotazione(ListaPrenotazioni lista, const char *matricola, FasciaOraria fascia);
void aggiorna_stato_prenotazione(ListaPrenotazioni lista, const char *matricola, FasciaOraria fascia, StatoPrenotazione stato);
void visualizza_per_stato(ListaPrenotazioni lista, StatoPrenotazione stato);


#endif // LISTA_DINAMICA_H