/*
 * Nome file: queue.h
 * Autore: [Tuo Nome / Gruppo]
 * Data: 14/05/2026
 * Descrizione: Interfaccia dell'ADT Coda (Queue). Il modulo gestisce una 
 * struttura dati FIFO per la gestione della lista d'attesa degli studenti.
 * Implementa l'information hiding tramite puntatore opaco.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "shared.h"

/**
 * Definizione del tipo opaco Queue.
 * L'implementazione interna (basata su lista collegata o array) 
 * è nascosta nel file queue.c.
 */
typedef struct Queue *Queue; //puntatore opaco alla struttura Queue

//SPECIFICA SINTATTICA E SEMANTICA
/**
 * Operazione: crea_queue
 * Descrizione: Alloca e inizializza una nuova coda vuota.
 * Post-condizioni: Restituisce un puntatore a una Queue valida. 
 * In caso di errore di allocazione restituisce NULL.
 */
Queue crea_queue(); 

/**
 * Operazione: distruggi_queue
 * Descrizione: Libera tutta la memoria occupata dalla coda e dai suoi nodi.
 * Parametri: q - la coda da eliminare.
 * Pre-condizioni: q deve essere una coda valida (non NULL).
 * Post-condizioni: La memoria è liberata e q non è più utilizzabile.
 */
void distruggi_queue(Queue q); 

/**
 * Operazione: is_empty
 * Descrizione: Verifica se la coda contiene elementi.
 * Parametri: q - la coda da controllare.
 * Ritorno: 1 se la coda è vuota, 0 altrimenti.
 */
int is_empty(Queue q); 

/**
 * Operazione: get_dimensione
 * Descrizione: Restituisce il numero di elementi attualmente presenti in coda.
 * Parametri: q - la coda da interrogare.
 * Ritorno: Numero intero rappresentante la dimensione della coda.
 */
int get_dimensione(Queue q); 

/**
 * Operazione: enqueue
 * Descrizione: Inserisce una nuova richiesta (prenotazione) in fondo alla coda.
 * Parametri: q - la coda; matricola - id studente; 
 * fascia - turno richiesto; tipo - modalità accesso.
 * Pre-condizioni: q non NULL, matricola stringa valida.
 * Post-condizioni: La dimensione della coda aumenta di 1.
 */
void enqueue(Queue q, const char *matricola, FasciaOraria fascia, TipoAccesso tipo); 

/**
 * Operazione: dequeue
 * Descrizione: Rimuove l'elemento in testa alla coda (politica FIFO).
 * Parametri: q - la coda da cui estrarre.
 * Pre-condizioni: q non NULL e non vuota (is_empty(q) == 0).
 * Post-condizioni: L'elemento in testa viene rimosso, la dimensione diminuisce di 1.
 */
void dequeue(Queue q); 

//FUNZIONI PEEK
/* Queste funzioni permettono di leggere i dati dell'elemento che sta 
 * per essere estratto senza rimuoverlo effettivamente.
 */

/**
 * Operazione: queue_peek_matricola / fascia / tipo
 * Descrizione: Restituiscono i dati dell'elemento in testa alla coda.
 * Pre-condizioni: q non NULL e non vuota.
 * Post-condizioni: Restituisce il valore del campo richiesto del primo nodo.
 */
char* queue_peek_matricola(Queue q);
FasciaOraria queue_peek_fascia(Queue q);
TipoAccesso queue_peek_tipo(Queue q);



#endif // QUEUE_H