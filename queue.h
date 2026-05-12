#ifndef QUEUE_H
#define QUEUE_H

#include "shared.h"

typedef struct Queue *Queue; //puntatore opaco alla struttura Queue

Queue crea_queue(); //costruttore
void distruggi_queue(Queue q); //distruttore

int is_empty(Queue q); //controlla se la coda è vuota
int get_dimensione(Queue q); //restituisce il numero di studenti in coda di attesa
void enqueue(Queue q, const char *matricola, FasciaOraria fascia, TipoAccesso tipo); //aggiunge una prenotazione alla coda
void dequeue(Queue q); //rimuove e restituisce la prenotazione in testa alla coda

//getter dedicati all'uscita dei dati degli studenti in testa alla coda
char* queue_peek_matricola(Queue q);
FasciaOraria queue_peek_fascia(Queue q);
TipoAccesso queue_peek_tipo(Queue q);



#endif // QUEUE_H



/*
typedef struct {
    char matricola[20];
    Data data;
    FasciaOraria fascia;
    TipoAccesso tipo;
} Prenotazione;

*/