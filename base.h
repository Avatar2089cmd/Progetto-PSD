#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string>

#define MAX_NUM 20 // numero massimo di posti
#define NAME_SIZE 20 // dimensione massima del nome di uno studente
#define MATRICOLA_SIZE 10 // dimensione massima della matricola di uno studente

typedef enum { 
    MATTINA, 
    POMERIGGIO, 
    SERA,
    NUM_FASCE_ORARIE // numero totale di fasce orarie per facilitare l'implementazione 
}FasciaOraria;

typedef struct {
    int giorno;
    int mese;
    int anno;
} data;

#endif // BASE_H