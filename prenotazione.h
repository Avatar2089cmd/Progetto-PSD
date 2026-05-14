/*
 * Nome file: prenotazione.h
 * Autore: Ranucci Simone, Scaldaferri Ilaria
 * Descrizione: Interfaccia dell'ADT Prenotazione. Gestisce le informazioni
 * relative alla riserva di un posto in aula, inclusi lo stato (PRENOTATA, 
 * CHECKED_IN, etc.) e il riferimento temporale (Data e Fascia).
 */

#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

#include "shared.h"

/**
 * Definizione del tipo opaco Prenotazione.
 * L'implementazione della struttura è nascosta nel file prenotazione.c.
 */
typedef struct Prenotazione *Prenotazione; 

//SPECIFICA SINTATTICA E SEMANTICA
/**
 * Operazione: crea_prenotazione
 * Descrizione: Alloca memoria per una nuova prenotazione e ne inizializza 
 * i campi. Lo stato iniziale è impostato automaticamente a PRENOTATA.
 * Parametri: matricola - ID studente; data - giorno della riserva; 
 * fascia - turno scelto.
 * Pre-condizioni: matricola non NULL, data valida, fascia valida.
 * Post-condizioni: Restituisce un oggetto Prenotazione inizializzato.
 */
Prenotazione crea_prenotazione(const char *matricola, Data data, FasciaOraria fascia); 

/*
 * Operazione: distruggi_prenotazione
 * Descrizione: Libera la memoria associata alla singola prenotazione.
 * Parametri: p - puntatore alla prenotazione da eliminare.
 * Pre-condizioni: p non deve essere NULL.
 * Post-condizioni: Memoria deallocata; p non è più utilizzabile.
 */
void distruggi_prenotazione(Prenotazione p); //distruttore

//FUNZIONI SETTER PER MODIFICARE LO STATO DELLA PRENOTAZIONE
/**
 * Operazione: set_posto_prenotazione
 * Descrizione: Assegna un numero di posto fisico alla prenotazione.
 * Parametri: p - la prenotazione; posto - intero indicante il posto assegnato.
 * Pre-condizioni: p non NULL, posto >= 0 e < MAX_NUM.
 * Post-condizioni: Il campo posto di p viene aggiornato.
 */
void set_posto_prenotazione(Prenotazione p, int posto); 

/**
 * Operazione: annulla_prenotazione
 * Descrizione: Cambia lo stato della prenotazione in ANNULLATA.
 * Parametri: p - la prenotazione da annullare.
 * Pre-condizioni: p non NULL.
 * Post-condizioni: Lo stato di p è impostato a ANNULLATA; il posto viene liberato.
 */
void annulla_prenotazione(Prenotazione p);

/**
 * Operazione: set_stato_prenotazione
 * Descrizione: Modifica manualmente lo stato della prenotazione (es. in NO_SHOW).
 * Parametri: p - la prenotazione; stato - il nuovo stato da assegnare.
 * Pre-condizioni: p non NULL, stato valore valido dell'enum StatoPrenotazione.
 */
void set_stato_prenotazione(Prenotazione p, StatoPrenotazione stato);

//FUNZIONI GETTER PER ACCEDERE AI CAMPI DELLA PRENOTAZIONE
/**
 * Operazione: prenotazione_get_*
 * Descrizione: Serie di selettori per recuperare i dati dall'oggetto opaco.
 * Parametri: p - puntatore alla prenotazione (costante, non modificabile).
 * Pre-condizioni: p non deve essere NULL.
 * Post-condizioni: Restituisce il valore del campo richiesto.
 */
int prenotazione_get_posto(const Prenotazione p);
char* prenotazione_get_matricola(const Prenotazione p);
Data prenotazione_get_data(const Prenotazione p);
FasciaOraria prenotazione_get_fascia(const Prenotazione p);
StatoPrenotazione prenotazione_get_stato(const Prenotazione p);

void visualizza_prenotazione(Prenotazione p);



#endif