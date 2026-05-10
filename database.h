#ifndef DATABASE_H
#define DATABASE_H

#include "base.h"
#include "studente.h"
#include "prenotazione.h"

void database_init();
void database_chiudi();

/* operazioni su studenti */
void database_salva_studente(Studente s);
Studente database_cerca_studente(const char *matricola);
int database_studente_esiste(const char *matricola);

/* operazioni su prenotazioni */
void database_salva_prenotazione(Prenotazione p);
void database_aggiorna_prenotazione(const char *matricola, FasciaOraria fascia, StatoPrenotazione stato);

#endif