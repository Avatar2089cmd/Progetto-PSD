#include "studente.h"

//costanti per la dimensione massima dei campi di uno studente
#define MAX_NOME 20
#define MAX_MATRICOLA 10
#define MAX_CORSO 30

//prototipi funzioni statiche per i setter
static void set_nome(Studente s, const char *nome);
static void set_matricola(Studente s, const char *matricola);
static void set_corso(Studente s, const char *corso);


typedef struct Studente{
    char nome[MAX_NOME];
    char matricola[MAX_MATRICOLA];
    char corso[MAX_CORSO];
}Studente;

//funzione costruttore:
Studente crea_studente(const char *nome, const char *matricola, const char *corso){
    Studente s = malloc(sizeof(struct Studente));
    if(s == NULL){
        return NULL; //gestione errore allocazione
    }
    set_matricola(s, matricola);
    set_nome(s, nome);
    set_corso(s, corso);
    return s;
}

//funzione distruttore:
void distruggi_studente(Studente s){
    free(s);
}

//static setter:

static void set_nome(Studente s, const char *nome){
    strncpy(s->nome, nome, MAX_NOME);
    s->nome[MAX_NOME - 1] = '\0'; //garantisce la terminazione della stringa
}

static void set_matricola(Studente s, const char *matricola){
    strncpy(s->matricola, matricola, MAX_MATRICOLA);
    s->matricola[MAX_MATRICOLA - 1] = '\0';
}

static void set_corso(Studente s, const char *corso){
    strncpy(s->corso, corso, MAX_CORSO);
    s->corso[MAX_CORSO - 1] = '\0';
}



//funzioni getter:

const char* get_nome(Studente s){return s->nome;}
const char* get_matricola(Studente s){return s->matricola;}
const char* get_corso(Studente s){return s->corso;}
