#ifndef DATABASE_H
#define DATABASE_H

#include "studente.h"
#include "prenotazione.h"

void database_init(); //crea e inizializza il database con i dati di tutti gli studenti
void database_chiudi();

/* operazioni su studenti */
void database_salva_studente(Studente s);
Studente database_cerca_studente(const char *matricola);
int database_studente_esiste(const char *matricola);


#endif