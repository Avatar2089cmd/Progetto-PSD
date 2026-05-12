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

//funzioni setter: modificano lo stato della prenotazione

void set_posto_prenotazione(Prenotazione p, int posto){p->posto = posto;}
void annulla_prenotazione(Prenotazione p){p->stato = ANNULLATA;}
void set_stato_prenotazione(Prenotazione p, StatoPrenotazione stato){p->stato = stato;}

//funzioni getter:
int prenotazione_get_posto(const Prenotazione p){return p->posto;}
char* prenotazione_get_matricola(const Prenotazione p){return p->matricola;}
Data prenotazione_get_data(const Prenotazione p){return p->data;}
FasciaOraria prenotazione_get_fascia(const Prenotazione p){return p->fascia;}
StatoPrenotazione prenotazione_get_stato(const Prenotazione p){return p->stato;}

