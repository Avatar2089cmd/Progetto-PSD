#include "database.h"

#define FILE_STUDENTI "studenti.bin"
static FILE *fp_studenti = NULL;

void database_init(){
    fp_studenti = fopen(FILE_STUDENTI, "rb");
    if(fp_studenti == NULL){
        //file non esiste, creo il database
        fp_studenti = fopen(FILE_STUDENTI, "wb");
        if(fp_studenti == NULL){
            fprintf(stderr, "Errore nella creazione del database\n");
            exit(1);
        }
    } 
}

void database_chiudi(){
    if(fp_studenti != NULL){ //controllo difensivo anti-crash qualora venga richiamata più volte
        fclose(fp_studenti); //chiudo il file
        fp_studenti = NULL;
    }
}

void database_salva_studente(Studente s){
    if(fp_studenti == NULL){
        fprintf(stderr, "Database non inizializzato\n");
        return;
    }
    fseek(fp_studenti, 0, SEEK_END); //posiziono il puntatore alla fine del file
    scrivi_studente(s, fp_studenti); //scrivo lo studente
    fflush(fp_studenti); //assicuro che i dati vengano scritti su disco
}

int database_studente_esiste(const char *matricola){
    Studente s;
    if(fp_studenti == NULL) return 0;
    fseek(fp_studenti, 0, SEEK_SET); //posiziono il puntatore all'inizio del file
    while((s = leggi_studente(fp_studenti)) != NULL){
        if(strcmp(get_matricola(s),matricola) == 0){
            distruggi_studente(s); 
            return 1; //studente trovato
        }
        distruggi_studente(s); 
    }
    return 0; //studente non trovato
}