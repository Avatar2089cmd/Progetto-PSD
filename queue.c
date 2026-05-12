#include "queue.h"

void enqueue(Queue q, const char *matricola, FasciaOraria fascia, TipoAccesso tipo){
    // Implementazione dell'aggiunta di una prenotazione alla coda
}

void dequeue(Queue q){
    // Implementazione della rimozione della prenotazione in testa alla coda
}

int is_empty(Queue q){
    // Implementazione del controllo se la coda è vuota
}

int get_dimensione(Queue q){
    // Implementazione del conteggio del numero di studenti in coda di attesa
}

char* queue_peek_matricola(Queue q){
    // Implementazione del getter per la matricola in testa alla coda
}

FasciaOraria queue_peek_fascia(Queue q){
    // Implementazione del getter per la fascia oraria in testa alla coda
}

TipoAccesso queue_peek_tipo(Queue q){
    // Implementazione del getter per il tipo di accesso in testa alla coda
}
