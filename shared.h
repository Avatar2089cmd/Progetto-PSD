/*
 * Nome file: shared.h
 * Autore: Ranucci Simone, Scaldaferri Ilaria
 * Descrizione: Definizione dei tipi di dato condivisi e delle costanti 
 * globali del progetto. Contiene le enumerazioni per fasce orarie, 
 * stati della prenotazione e tipi di accesso, oltre alla struttura Data.
 */

#ifndef SHARED_H
#define SHARED_H

#include "base.h"
 
//COSTANTI GLOBALI
#define MAX_MATRICOLA 11 // 10 caratteri alfanumerici+ terminatore "\0"

/*
 * Tipo: FasciaOraria
 * Descrizione: Rappresenta i turni disponibili nell'aula studio.
 * Note: NUM_FASCE_ORARIE viene utilizzato come "sentinella" per conoscere 
 * il numero totale di elementi, facilitando l'iterazione nei cicli e 
 * la definizione di dimensioni negli array (es. la matrice dei posti).
 */
typedef enum { 
    MATTINA, 
    POMERIGGIO, 
    SERA,
    NUM_FASCE // numero totale di fasce orarie per facilitare l'implementazione 
}FasciaOraria;

/*
 * Tipo: Data
 * Descrizione: Struttura per la memorizzazione di una data solare.
 * Campi: giorno, mese, anno (interi).
 */
typedef struct {
    int giorno;
    int mese;
    int anno;
}Data;

/*
 * Tipo: StatoPrenotazione
 * Descrizione: Rappresenta il ciclo di vita di una prenotazione.
 * Valori: 
 * - PRENOTATA: Posto riservato ma studente non ancora arrivato.
 * - CHECKED_IN: Studente attualmente presente in aula.
 * - CHECKED_OUT: Sessione terminata regolarmente.
 * - ANNULLATA: Cancellata dallo studente prima dell'inizio.
 * - NO_SHOW: Prenotazione scaduta senza presentazione dello studente.
 */
typedef enum {
    PRENOTATA,
    CHECKED_IN,
    CHECKED_OUT,
    ANNULLATA,
    NO_SHOW
}StatoPrenotazione;

/*
 * Tipo: TipoAccesso
 * Descrizione: Rappresenta i diversi modi in cui uno studente può accedere all'aula studio.
 * Valori:
 * - WALK_IN: Accesso diretto senza prenotazione.
 * - PRENOTAZIONE: Accesso tramite prenotazione.
 */
typedef enum{
    WALK_IN,
    PRENOTAZIONE
}TipoAccesso;

#endif // SHARED_H