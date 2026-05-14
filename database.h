/*
 * Nome file: database.h
 * Autore: Ranucci Simone, Scaldaferri Ilaria
 * Descrizione: Interfaccia del modulo Database. Gestisce la persistenza dei 
 * dati degli studenti e delle prenotazioni, permettendo il caricamento, 
 * il salvataggio e la ricerca rapida tramite matricola.
 */

#ifndef DATABASE_H
#define DATABASE_H

#include "studente.h"
#include "prenotazione.h"

//OPERAZIONI DI GESTIONE DEL SISTEMA
/**
 * Operazione: database_init
 * Descrizione: Inizializza il database caricando i dati degli studenti 
 * dai file di supporto. Deve essere chiamata prima di qualsiasi operazione.
 * Pre-condizioni: I file di dati ("studenti.txt" o simili) devono essere 
 * presenti e accessibili.
 * Post-condizioni: Le strutture dati interne del database sono allocate e 
 * popolate. In caso di errore, il programma potrebbe terminare o 
 * segnalare l'impossibilità di avvio.
 */
void database_init(); 

/**
 * Operazione: database_chiudi
 * Descrizione: Chiude le connessioni ai file e libera la memoria allocata 
 * dal modulo database. Da invocare al termine del programma.
 * Pre-condizioni: Il database deve essere stato precedentemente inizializzato.
 * Post-condizioni: Tutta la memoria dinamica è liberata e i file sono chiusi 
 * correttamente per evitare perdite di dati.
 */
void database_chiudi();

//OPERAZIONI SUGLI STUDENTI
/**
 * Operazione: database_salva_studente
 * Descrizione: Aggiunge un nuovo oggetto Studente al database e lo 
 * scrive sul supporto fisico.
 * Parametri: s - il puntatore allo studente da salvare.
 * Pre-condizioni: s non deve essere NULL e lo studente non deve essere 
 * già presente (evita duplicati).
 * Post-condizioni: I dati di s sono memorizzati permanentemente.
 */
void database_salva_studente(Studente s);

/**
 * Operazione: database_cerca_studente
 * Descrizione: Ricerca uno studente nel database partendo dalla sua matricola.
 * Parametri: matricola - stringa contenente il codice univoco dello studente.
 * Pre-condizioni: matricola non NULL.
 * Post-condizioni: Restituisce un oggetto Studente se trovato, NULL altrimenti.
 * Note: La funzione potrebbe restituire una copia dell'oggetto o un 
 * riferimento, a seconda della gestione della memoria interna.
 */
Studente database_cerca_studente(const char *matricola);

/**
 * Operazione: database_studente_esiste
 * Descrizione: Verifica rapida della presenza di una matricola nel database.
 * Parametri: matricola - la stringa da cercare.
 * Ritorno: 1 se lo studente esiste, 0 altrimenti.
 * Pre-condizioni: matricola non NULL.
 */
int database_studente_esiste(const char *matricola);


#endif