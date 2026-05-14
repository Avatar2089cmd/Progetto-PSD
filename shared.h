#ifndef SHARED_H
#define SHARED_H

#include "base.h"
//tipi condivisi tra più moduli del progetto 

#define MAX_MATRICOLA 11 // 10 caratteri + terminatore "\0"

typedef enum { 
    MATTINA, 
    POMERIGGIO, 
    SERA,
    NUM_FASCE // numero totale di fasce orarie per facilitare l'implementazione 
}FasciaOraria;

typedef struct {
    int giorno;
    int mese;
    int anno;
}Data;

typedef enum {
    PRENOTATA,
    CHECKED_IN,
    CHECKED_OUT,
    ANNULLATA,
    NO_SHOW
}StatoPrenotazione;

typedef enum{
    WALK_IN,
    PRENOTAZIONE
}TipoAccesso;

#endif // SHARED_H