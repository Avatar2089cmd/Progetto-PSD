#ifndef STUDENTE_H
#define STUDENTE_H

#include "base.h"

typedef struct Studente *Studente; //puntatore opaco alla struttura Studente

Studente crea_studente(const char *nome, const char *matricola, const char *corso); //costruttore - alloca memoria per uno studente
void distruggi_studente(Studente s); //distruttore - libera la memoria allocata per uno studente



//funzioni getter per accedere ai campi di uno studente
const char* get_nome(Studente s);
const char* get_matricola(Studente s);
const char* get_corso(Studente s);

#endif // STUDENTE_H