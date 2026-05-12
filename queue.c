#include "queue.h"
#include "shared.h"

typedef struct QueueNode {
    char matricola[MAX_MATRICOLA];
    FasciaOraria fascia;
    TipoAccesso tipo;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *head;
    QueueNode *tail;
    int size;
} Queue;


Queue crea_queue(Queue *q){
    q = malloc(sizeof(struct Queue));
    if(*q==NULL) return NULL; //gestione errore allocazione

    q->head = NULL; //inizializzazione puntatore alla testa della coda
    q->tail = NULL; //inizializzazione puntatore alla fine  della coda
    q->size = 0; //inizializzazione della dimensione della coda

    return *q;
}

void distruggi_queue(Queue q){
    if(q == NULL) return;
    QueueNode *current = q->head;
    QueueNode *prox = NULL;
    while(current != NULL){
        prox = current->next;
        free(current);
        current = prox;
    }
    free(q);
}

// Implementazione delle funzioni dichiarate in queue.h

int is_empty(Queue q){return q->size == 0;}
int get_dimensione(Queue q){return q->size;}

FasciaOraria queue_peek_fascia(Queue q){
    if(is_empty(q)) return -1; //gestione coda vuota
    return q->head->fascia;
}
char* queue_peek_matricola(Queue q){
    if(is_empty(q)) return NULL; //gestione coda vuota
    return q->head->matricola;
}
TipoAccesso queue_peek_tipo(Queue q){
    if(is_empty(q)) return -1; //gestione coda vuota
    return q->head->tipo;
}    

void enqueue(Queue q, const char *matricola, FasciaOraria fascia, TipoAccesso tipo){
    // Implementazione dell'aggiunta di una prenotazione alla coda
    QueueNode *new_node = malloc(sizeof(QueueNode));
    if (new_node == NULL) return; //gestione errore allocazione
        strncpy(new_node->matricola, matricola, MAX_MATRICOLA);
        new_node -> matricola[MAX_MATRICOLA -1] = '\0';
        new_node -> fascia = fascia;
        new_node -> tipo = tipo;
        new_node -> next = NULL; 
        if (is_empty(q)) {
            q->head = new_node;
            q->tail = new_node;
        } else {
            q->tail->next = new_node;
            q->tail = new_node;
        }
        q->size++;
}

void dequeue(Queue q){
    if(is_empty(q)) return;
    QueueNode *temp = q->head;
    q->head = q->head->next;
    if(q->head == NULL){
        q->tail = NULL;
    }
    free(temp);
    q->size--;
}
