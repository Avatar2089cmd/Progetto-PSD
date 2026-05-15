/*
 * Nome file: studente.h
 * Autore: Ranucci Simone, Scaldaferri Ilaria
 * Descrizione: Definizione dell'ADT Studente. Il modulo gestisce l'astrazione
 * dei dati anagrafici di uno studente universitario, fornendo
 * metodi per la creazione, distruzione e l'accesso ai dati.
 */

#ifndef STUDENTE_H
#define STUDENTE_H

#include "base.h"

/* * Definizione del tipo opaco Studente.
 * L'implementazione della struttura è nascosta nel file studente.c
 * per garantire l'incapsulamento dei dati (Information Hiding).
 */

typedef struct Studente *Studente; /*puntatore opaco alla struttura Studente*/

/*SPECIFICA SINTATTICA E SEMANTICA*/
/**
 * Operazione: crea_studente
 * Descrizione: Alloca dinamicamente memoria per un nuovo oggetto Studente 
 * e ne inizializza i campi con i valori forniti.
 * Parametri: nome - stringa contenente il nome dello studente.
 * matricola - stringa contenente la matricola univoca.
 * corso - stringa contenente il corso di laurea.
 * Pre-condizioni: nome, matricola e corso devono essere stringhe non nulle (!= NULL).
 * Post-condizioni: Restituisce un puntatore a Studente correttamente allocato.
 * In caso di fallimento della malloc, restituisce NULL.
 */

Studente crea_studente(const char *nome, const char *matricola, const char *corso); /*costruttore - alloca memoria per uno studente*/

/**
 * Operazione: distruggi_studente
 * Descrizione: Libera tutta la memoria associata all'oggetto Studente, 
 * inclusi i campi allocati internamente.
 * Parametri: s - il puntatore allo studente da deallocare.
 * Pre-condizioni: s deve essere un puntatore a uno Studente valido e non NULL.
 * Post-condizioni: La memoria occupata da s è resa nuovamente disponibile.
 * Il puntatore s non è più utilizzabile.
 */
void distruggi_studente(Studente s); /*distruttore - libera la memoria allocata per uno studente*/

/**
 * Operazione: scrivi_studente
 * Descrizione: Serializza i dati dello studente su un file o stream di output.
 * Parametri: s - studente da scrivere; fp - stream di output (es. file o stdout).
 * Pre-condizioni: s e fp non devono essere NULL.
 * Post-condizioni: I dati dello studente sono scritti sul supporto indicato.
 */
void scrivi_studente(Studente s, FILE *fp);

/**
 * Operazione: leggi_studente
 * Descrizione: Legge i dati da uno stream e ricostruisce un oggetto Studente.
 * Parametri: fp - stream di input da cui leggere i dati.
 * Pre-condizioni: fp deve essere uno stream aperto in lettura e non NULL.
 * Post-condizioni: Restituisce un nuovo Studente allocato con i dati letti, 
 * oppure NULL in caso di errore o fine file.
 */
Studente leggi_studente(FILE *fp);

/*FUNZIONI GETTER*/
/**
 * Operazione: get_nome / get_matricola / get_corso
 * Descrizione: Funzioni per l'accesso controllato ai campi della struttura opaca.
 * Parametri: s - puntatore allo studente.
 * Pre-condizioni: s non deve essere NULL.
 * Post-condizioni: Restituisce un puntatore costante al campo richiesto.
 */
const char* get_nome(Studente s);
const char* get_matricola(Studente s);
const char* get_corso(Studente s);

#endif