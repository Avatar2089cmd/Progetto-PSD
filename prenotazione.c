#include "base.h"
#include "prenotazione.h"
#include "shared.h"

typedef struct Prenotazione{
    char matricola[MAX_MATRICOLA];
    Data data;
    FasciaOraria fascia;
    int posto;
    StatoPrenotazione stato;
}Prenotazione;

//funzione costruttore:
Prenotazione crea_prenotazione(const char *matricola, Data data, FasciaOraria fascia){
    Prenotazione p = malloc(sizeof(struct Prenotazione));
    if(p == NULL){
        return NULL; //gestione errore allocazione
    }
    strncpy(p->matricola, matricola, MAX_MATRICOLA);
    p->matricola[MAX_MATRICOLA - 1] = '\0';
    p->data = data;
    p->fascia = fascia;
    p->posto = -1; //posto non assegnato
    p->stato = PRENOTATA; //stato iniziale
    return p;
}

//funzione distruttore:
void distruggi_prenotazione(Prenotazione p){
    free(p);
}
