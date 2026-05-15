#include "aula.h"

#define POSTI_PER_FASCIA 20

/*struttura dati per rappresentare l'aula*/
char aula[NUM_FASCE][POSTI_PER_FASCIA]; /*L = libero, O = occupato*/

void aula_init(){
    int i, j;
    for(i = 0; i < NUM_FASCE; i++){
        for(j = 0; j < POSTI_PER_FASCIA; j++){
            aula[i][j] = 'L';
        }
    }
}

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
    int i=0;
    for(i = 0; i < POSTI_PER_FASCIA; i++){
        if(aula[fascia][i] == 'L'){
            aula[fascia][i] = 'O'; 
            return i;
        }
    }
    return -1; 
}

void libera_posto_aula(FasciaOraria fascia, int posto){
    if(posto >= 0 && posto < POSTI_PER_FASCIA){
        aula[fascia][posto] = 'L'; 
    }
}

void libera_fascia_aula(FasciaOraria fascia){
    int i=0;
    for(i = 0; i < POSTI_PER_FASCIA; i++){
        aula[fascia][i] = 'L'; 
    }
}

int aula_get_max_posti(){return POSTI_PER_FASCIA;}