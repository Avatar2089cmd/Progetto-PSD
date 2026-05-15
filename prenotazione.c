#include "prenotazione.h"


struct Prenotazione{
    char matricola[MAX_MATRICOLA];
    Data data;
    FasciaOraria fascia;
    int posto;
    StatoPrenotazione stato;
};

/*funzione costruttore:*/
Prenotazione crea_prenotazione(const char *matricola, Data data, FasciaOraria fascia){
    Prenotazione p = malloc(sizeof(struct Prenotazione));
    if(p == NULL){
        return NULL; /*gestione errore allocazione*/
    }
    strncpy(p->matricola, matricola, MAX_MATRICOLA);
    p->matricola[MAX_MATRICOLA - 1] = '\0';
    p->data = data;
    p->fascia = fascia;
    p->posto = -1; /*posto non assegnato*/
    p->stato = PRENOTATA; /*stato iniziale*/
    return p;
}

/*funzione distruttore:*/
void distruggi_prenotazione(Prenotazione p){
    free(p);
}

/*funzioni setter: modificano lo stato della prenotazione*/

void set_posto_prenotazione(Prenotazione p, int posto){p->posto = posto;}
void annulla_prenotazione(Prenotazione p){p->stato = ANNULLATA;}
void set_stato_prenotazione(Prenotazione p, StatoPrenotazione stato){p->stato = stato;}

/*funzioni getter:*/
int prenotazione_get_posto(const Prenotazione p){return p->posto;}
char* prenotazione_get_matricola(const Prenotazione p){return p->matricola;}
Data prenotazione_get_data(const Prenotazione p){return p->data;}
FasciaOraria prenotazione_get_fascia(const Prenotazione p){return p->fascia;}
StatoPrenotazione prenotazione_get_stato(const Prenotazione p){return p->stato;}

void visualizza_prenotazione(Prenotazione p){
    printf("Matricola: %s\n", p->matricola);
    printf("Data: %02d/%02d/%04d\n", p->data.giorno, p->data.mese, p->data.anno);
    printf("Fascia Oraria: ");
    switch(p->fascia){
        case MATTINA: printf("Mattina\n"); break;
        case POMERIGGIO: printf("Pomeriggio\n"); break;
        case SERA: printf("Sera\n"); break;
        default: printf("Sconosciuta\n"); break;
    }
    printf("Posto: %d\n", p->posto);
    printf("Stato: ");
    switch(p->stato){
        case PRENOTATA: printf("Prenotata\n"); break;
        case CHECKED_IN: printf("Checked-in\n"); break;
        case CHECKED_OUT: printf("Checked-out\n"); break;
        case ANNULLATA: printf("Annullata\n"); break;
        case NO_SHOW: printf("No-show\n"); break;
        default: printf("Sconosciuto\n"); break;
    }
}