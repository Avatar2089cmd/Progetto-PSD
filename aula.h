/*
 * Nome file: aula.h
 * Autore: Ranucci Simone, Scaldaferri Ilaria
 * Descrizione: Interfaccia per la gestione fisica dell'aula studio. 
 * Il modulo si occupa di monitorare la disponibilità dei posti, 
 * gestire le occupazioni e il ripristino delle fasce orarie.
 */

#ifndef AULA_H
#define AULA_H

#include "shared.h"

void aula_init();

//OPERAZIONI DI GESTIONE DELL'AULA
/**
 * Operazione: get_posti_liberi_aula
 * Descrizione: Calcola e restituisce il numero di postazioni attualmente 
 * non occupate per una specifica fascia oraria.
 * Parametri: fascia - Il turno (MATTINA, POMERIGGIO, SERA) da controllare.
 * Pre-condizioni: fascia deve essere un valore valido dell'enum FasciaOraria.
 * Ritorno: Numero intero di posti disponibili (>= 0).
 */
int get_posti_liberi_aula(FasciaOraria fascia); 

/**
 * Operazione: blocca_posto_aula
 * Descrizione: Ricerca il primo posto disponibile nella fascia indicata 
 * e lo contrassegna come occupato.
 * Parametri: fascia - Il turno in cui effettuare l'occupazione.
 * Pre-condizioni: Deve esserci almeno un posto libero nella fascia indicata.
 * Post-condizioni: Restituisce l'indice del posto bloccato (0-indexed). 
 * Se l'aula è piena, restituisce -1.
 */
int blocca_posto_aula(FasciaOraria fascia); 

//OPERAZIONI DI RIPRISTINO POSTI E FASCE
/**
 * Operazione: libera_posto_aula
 * Descrizione: Rende nuovamente disponibile una singola postazione specifica.
 * Parametri: fascia - Il turno di riferimento; posto - L'indice numerico del posto.
 * Pre-condizioni: fascia valida, posto compreso tra 0 e MAX_NUM-1.
 * Post-condizioni: Il posto indicato viene resettato allo stato "libero".
 */
void libera_posto_aula(FasciaOraria fascia, int posto); 

/**
 * Operazione: libera_fascia_aula
 * Descrizione: Esegue il reset completo di tutti i posti per una data fascia.
 * Viene utilizzata tipicamente per il check-out di massa al termine di un turno.
 * Parametri: fascia - Il turno da ripristinare.
 * Pre-condizioni: fascia valida.
 * Post-condizioni: Tutti i posti della fascia tornano disponibili; 
 * eventuali dati temporanei della sessione vengono cancellati.
 */
void libera_fascia_aula(FasciaOraria fascia); 

int aula_get_max_posti();

#endif // AULA_H