/*
 * Nome file: sistema.h
 * Autore: Ranucci Simone, Scaldaferri Ilaria
 * Descrizione: Interfaccia principale del sistema. Coordina tutti i moduli
 * (database, aula, lista prenotazioni, coda attesa, report) ed espone
 * i due menu operativi: studente e amministratore.
 */

#ifndef SISTEMA_H
#define SISTEMA_H

#include "database.h"
#include "report.h"
#include "aula.h"
#include "lista_dinamica.h"
#include "queue.h"

/* Inizializza tutti i moduli (database, aula, lista, coda, report).
 * Deve essere chiamata prima di sistema_esegui().
 * data: la data della sessione corrente, usata anche per il file report. */
void sistema_init(Data data);

/* Avvia il loop principale: chiede il ruolo (studente/admin) e
 * instrada verso il menu corretto. */
void sistema_esegui();

/* Chiude tutti i moduli e libera la memoria. */
void sistema_chiudi();

#endif /* SISTEMA_H */