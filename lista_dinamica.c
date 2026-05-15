#include "lista_dinamica.h"

typedef struct NodeLista{
    Prenotazione p;
    struct NodeLista *next;
}NodeLista;

struct ListaPrenotazioni{
    NodeLista *head;
    int size;
};

static int confronta_prenotazione(Prenotazione p, const char *matricola, FasciaOraria fascia){
    return strcmp(prenotazione_get_matricola(p), matricola) == 0 &&
           prenotazione_get_fascia(p) == fascia;
}


ListaPrenotazioni crea_lista_prenotazioni(){
    ListaPrenotazioni lista = (ListaPrenotazioni)malloc(sizeof(struct ListaPrenotazioni));
    if(lista != NULL){
        lista->head = NULL;
        lista->size = 0;
    }
    return lista;
}

void distruggi_lista_prenotazioni(ListaPrenotazioni lista){
    NodeLista *current = NULL;
    NodeLista *temp = NULL;
    if(lista == NULL){
        return;
    } else{
        current = lista->head;
         while(current != NULL){
            temp = current;
            current = current->next;
            distruggi_prenotazione(temp->p);
            free(temp);
        }
        free(lista);
    }
}

int aggiungi_prenotazione(ListaPrenotazioni lista, Prenotazione p){
    NodeLista *newNode = NULL;
    if(lista == NULL || p == NULL) return -1; 
    newNode = malloc(sizeof(NodeLista));
    if(newNode == NULL){
        return -1;
    }
    newNode->p = p;
    newNode->next = lista->head;
    lista->head = newNode;
    lista->size++;
    return 0;
}

Prenotazione cerca_prenotazione(ListaPrenotazioni lista, const char *matricola, FasciaOraria fascia){
    NodeLista *current = NULL;
    if(lista == NULL || matricola == NULL) return NULL; 
    current = lista->head;
    while(current != NULL){
        if(confronta_prenotazione(current->p, matricola, fascia)){
            return current->p; 
        }
        current = current->next;
    }
    return NULL;
}

void aggiorna_stato_prenotazione(ListaPrenotazioni lista, const char *matricola, FasciaOraria fascia, StatoPrenotazione stato){
    NodeLista *current = NULL;
    if(lista == NULL || matricola == NULL) return; 
    current = lista->head;
    while(current != NULL){
        if(strcmp(prenotazione_get_matricola(current->p), matricola) == 0 &&
           prenotazione_get_fascia(current->p) == fascia){
            set_stato_prenotazione(current->p, stato);
            return;
        }
        current = current->next;
    }
}

int visualizza_per_stato(ListaPrenotazioni lista, StatoPrenotazione stato, char flag){
    NodeLista *current = NULL;
    int count = 0;
    if(lista == NULL) return -1; 
    current = lista->head;
    while(current != NULL){
        if(prenotazione_get_stato(current->p) == stato){
            if(flag == 'S'){ /*se flag è 'S' visualizzo solo la prenotazione, altrimenti visualizzo anche i dettagli*/
            visualizza_prenotazione(current->p);
            }
            count++;
        }
        current = current->next;
    }
    return count;
}

int rimuovi_prenotazione(ListaPrenotazioni lista, const char *matricola, FasciaOraria fascia){
    NodeLista *current = NULL;
    NodeLista *prev = NULL;
    if(lista == NULL || matricola == NULL) return -1; 
    current = lista->head;
    while(current != NULL){
        if(strcmp(prenotazione_get_matricola(current->p), matricola) == 0 &&
           prenotazione_get_fascia(current->p) == fascia){
            if(prev == NULL){ /*rimozione del primo nodo*/
                lista->head = current->next;
            } else{
                prev->next = current->next;
            }
            distruggi_prenotazione(current->p);
            free(current);
            lista->size--;
            return 0; /*prenotazione rimossa*/
        }
        prev = current;
        current = current->next;
    }
    return -1; /*prenotazione non trovata*/
}

void lista_aggiorna_no_show(ListaPrenotazioni lista){
    NodeLista *current = NULL;
    if(lista == NULL) return;
    current = lista->head;
    while(current != NULL){
        if(prenotazione_get_stato(current->p) == PRENOTATA){
            set_stato_prenotazione(current->p, NO_SHOW);
        }
        current = current->next;
    }
}