#include "queue.h"
#include "shared.h"

typedef struct QueueNode {
    char matricola[MAX_MATRICOLA];
    FasciaOraria fascia;
    TipoAccesso tipo;
    struct QueueNode *next;
} QueueNode;

struct Queue {
    QueueNode *head;
    QueueNode *tail;
    int size;
};

Queue crea_queue(){
    Queue q = malloc(sizeof(struct Queue));
    if(q==NULL) return NULL; 

    q->head = NULL; 
    q->tail = NULL; 
    q->size = 0; 

    return q;
}

void distruggi_queue(Queue q){
    QueueNode *current = NULL;
    QueueNode *prox = NULL;
    
    if(q == NULL) return;
    current = q->head;
    prox = NULL;
    while(current != NULL){
        prox = current->next;
        free(current);
        current = prox;
    }
    free(q);
}

/* Implementazione delle funzioni dichiarate in queue.h*/

int is_empty(Queue q){return q->size == 0;}
int get_dimensione(Queue q){return q->size;}

FasciaOraria queue_peek_fascia(Queue q){
    if(is_empty(q)) return -1; 
    return q->head->fascia;
}
char* queue_peek_matricola(Queue q){
    if(is_empty(q)) return NULL; 
    return q->head->matricola;
}
TipoAccesso queue_peek_tipo(Queue q){
    if(is_empty(q)) return -1; 
    return q->head->tipo;
}    

void enqueue(Queue q, const char *matricola, FasciaOraria fascia, TipoAccesso tipo){
    QueueNode *new_node = malloc(sizeof(QueueNode));
    if (new_node == NULL) return; 
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
    QueueNode *temp = NULL;
    if(is_empty(q)) return;
    temp = q->head;
    q->head = q->head->next;
    if(q->head == NULL){
        q->tail = NULL;
    }
    free(temp);
    q->size--;
}
