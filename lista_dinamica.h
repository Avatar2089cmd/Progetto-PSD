/*
 * Nome file: lista_dinamica.h
 * Autore: Ranucci Simone, Scaldaferri Ilaria
 * Descrizione: Interfaccia dell'ADT Lista Dinamica di Prenotazioni. 
 * Il modulo gestisce una collezione ordinata o non ordinata di oggetti 
 * di tipo Prenotazione, permettendo l'inserimento, la cancellazione 
 * e la ricerca basata su criteri multipli.
 */

#ifndef LISTA_DINAMICA_H
#define LISTA_DINAMICA_H

#include "prenotazione.h"

/**
 * Definizione del tipo opaco ListaPrenotazioni.
 * L'implementazione (tipicamente una lista semplicemente o doppiamente 
 * collegata) è nascosta nel file lista_dinamica.c.
 */
typedef struct listaPrenotazioni *ListaPrenotazioni;

//OPERAZIONI SULLA LISTA DI PRENOTAZIONI
/**
 * Operazione: crea_lista_prenotazioni
 * Descrizione: Alloca e inizializza una nuova lista di prenotazioni vuota.
 * Post-condizioni: Restituisce un puntatore a ListaPrenotazioni valido. 
 * Se la memoria è esaurita, restituisce NULL.
 */
ListaPrenotazioni crea_lista_prenotazioni();

/**
 * Operazione: distruggi_lista_prenotazioni
 * Descrizione: Libera tutta la memoria occupata dalla lista e dai nodi che 
 * la compongono.
 * Parametri: lista - la lista da deallocare.
 * Pre-condizioni: lista non deve essere NULL.
 * Post-condizioni: La memoria è liberata. Nota: a seconda della logica del 
 * progetto, potrebbe deallocare anche gli oggetti Prenotazione contenuti.
 */
void distruggi_lista_prenotazioni(ListaPrenotazioni lista);

//OPERAZIONI DI MANIPOLAZIONE DEI DATI
/**
 * Operazione: aggiungi_prenotazione
 * Descrizione: Inserisce un nuovo oggetto Prenotazione all'interno della lista.
 * Parametri: lista - la lista di destinazione; p - l'oggetto da inserire.
 * Pre-condizioni: lista e p non NULL.
 * Post-condizioni: Restituisce 1 se l'inserimento è avvenuto con successo, 
 * 0 in caso di errore (es. memoria esaurita).
 */
int aggiungi_prenotazione(ListaPrenotazioni lista, Prenotazione p);

/**
 * Operazione: rimuovi_prenotazione
 * Descrizione: Ricerca ed elimina una prenotazione specifica basandosi su 
 * matricola, data e fascia oraria.
 * Parametri: matricola, data, fascia - criteri di identificazione univoca.
 * Pre-condizioni: lista non NULL, matricola valida.
 * Post-condizioni: Restituisce 1 se l'elemento è stato trovato e rimosso, 
 * 0 se non è stata trovata alcuna corrispondenza.
 */
int rimuovi_prenotazione(ListaPrenotazioni lista, const char *matricola, Data data, FasciaOraria fascia);

//OPERAZIONI DI RICERCA E VISUALIZZAZIONE
/**
 * Operazione: cerca_prenotazione
 * Descrizione: Cerca nella lista una prenotazione specifica.
 * Ritorno: Restituisce il puntatore all'oggetto Prenotazione se trovato, 
 * NULL altrimenti.
 * Pre-condizioni: lista e matricola non NULL.
 */
Prenotazione cerca_prenotazione(ListaPrenotazioni lista, const char *matricola, FasciaOraria fascia);

/**
 * Operazione: aggiorna_stato_prenotazione
 * Descrizione: Modifica lo stato di una prenotazione esistente (es. da 
 * PRENOTATA a CHECKED_IN).
 * Parametri: stato - il nuovo valore da assegnare.
 * Pre-condizioni: La prenotazione deve esistere nella lista.
 */
void aggiorna_stato_prenotazione(ListaPrenotazioni lista, const char *matricola, FasciaOraria fascia, StatoPrenotazione stato);

/**
 * Operazione: visualizza_per_stato
 * Descrizione: Filtra e stampa a video tutte le prenotazioni che si 
 * trovano in un determinato stato.
 * Parametri: stato - filtro di ricerca; flag - carattere opzionale per 
 * formattare l'output.
 * Ritorno: Numero di elementi trovati per quel determinato stato.
 */
int visualizza_per_stato(ListaPrenotazioni lista, StatoPrenotazione stato, char flag);


#endif // LISTA_DINAMICA_H