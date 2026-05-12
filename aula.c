#include "aula.h"

#define POSTI_PER_FASCIA 20

//struttura dati per rappresentare l'aula
char aula[NUM_FASCE][POSTI_PER_FASCIA]; //L = libero, O = occupato

int get_posti_liberi_aula(FasciaOraria fascia){
    int count = 0, i=0;
    for(i = 0; i < POSTI_PER_FASCIA; i++){
        if(aula[fascia][i] == 'L'){
            count++;
        }
    }
    return count;
}

int blocca_posto_aula(FasciaOraria fascia){
    for(int i = 0; i < POSTI_PER_FASCIA; i++){
        if(aula[fascia][i] == 'L'){
            aula[fascia][i] = 'O'; //blocca il posto
            return i; //restituisce l'indice del posto bloccato
        }
    }
    return -1; //nessun posto disponibile
}

void libera_posto_aula(FasciaOraria fascia, int posto){
    if(posto >= 0 && posto < POSTI_PER_FASCIA){
        aula[fascia][posto] = 'L'; //libera il posto
    }
}

void libera_fascia_aula(FasciaOraria fascia){
    int i=0;
    for(i = 0; i < POSTI_PER_FASCIA; i++){
        aula[fascia][i] = 'L'; //libera tutti i posti della fascia
    }
}