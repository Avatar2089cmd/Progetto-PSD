#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
}Data;

#endif // BASE_H