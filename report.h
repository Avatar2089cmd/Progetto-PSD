/*
 * Nome file: report.h
 * Autore: Ranucci Simone, Scaldaferri Ilaria
 * Descrizione: Interfaccia per la generazione della reportistica del sistema.
 * Il modulo si occupa di aggregare i dati storici e correnti per produrre
 * statistiche sull'utilizzo dell'aula e registrare i flussi di accesso.
 */

#ifndef REPORT_H
#define REPORT_H

#include "shared.h"
#include "lista_dinamica.h"
#include "queue.h"

//OPERAZIONI DI GENERAZIONE E REGISTRAZIONE DEI REPORT
/**
 * Operazione: genera_report
 * Descrizione: Analizza lo stato della lista prenotazioni e della coda 
 * di attesa per produrre un riepilogo testuale delle attività.
 * Parametri: 
 * - lista: lo storico delle prenotazioni da analizzare.
 * - coda_report: la situazione attuale degli studenti in attesa.
 * - data: il giorno specifico di cui si vuole generare il report.
 * Pre-condizioni: lista e coda_report devono essere inizializzate (non NULL).
 * Post-condizioni: Produce un file o una stampa a video contenente il numero 
 * di accessi totali, no-show, e media di occupazione.
 */
void genera_report(ListaPrenotazioni lista, Queue coda_report, Data data);

/**
 * Operazione: registra_accesso
 * Descrizione: Scrive in tempo reale un log degli ingressi e delle uscite 
 * su un supporto di persistenza.
 * Parametri: 
 * - matricola: identificativo dello studente.
 * - fascia: turno di accesso.
 * - tipo: modalità (WALK_IN o PRENOTAZIONE).
 * - stato: esito dell'accesso (es. CHECKED_IN).
 * Pre-condizioni: matricola non NULL, parametri coerenti con i tipi definiti.
 * Post-condizioni: Una nuova riga viene aggiunta al registro degli accessi.
 */
void registra_accesso(const char* matricola, FasciaOraria fascia, TipoAccesso tipo, StatoPrenotazione stato); 

/**
 * Operazione: chiudi_report
 * Descrizione: Finalizza le operazioni di scrittura e chiude eventuali file 
 * aperti dal modulo report.
 * Pre-condizioni: Il modulo deve aver effettuato almeno una registrazione.
 * Post-condizioni: Risorse liberate e file salvati correttamente.
 */
void chiudi_report();

#endif // REPORT_H