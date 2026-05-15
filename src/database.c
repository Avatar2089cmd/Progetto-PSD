/*
 * Nome file: database.c
 * Autore: Ranucci Simone, Scaldaferri Ilaria
 */

#include "database.h"

#define FILE_STUDENTI "studenti.bin"
static FILE *fp_studenti = NULL;

void database_init(void){
    fp_studenti = fopen(FILE_STUDENTI, "r+b");
    if(fp_studenti == NULL){
        fp_studenti = fopen(FILE_STUDENTI, "w+b");
        if(fp_studenti == NULL){
            fprintf(stderr, "Errore nella creazione del database\n");
            exit(1);
        }
    }
}
 
void database_chiudi(void){
    if(fp_studenti != NULL){
        fclose(fp_studenti);
        fp_studenti = NULL;
    }
}
 
void database_salva_studente(Studente s){
    if(fp_studenti == NULL){
        fprintf(stderr, "Database non inizializzato\n");
        return;
    }
    fseek(fp_studenti, 0, SEEK_END);
    scrivi_studente(s, fp_studenti);
    fflush(fp_studenti);
    fseek(fp_studenti, 0, SEEK_SET);
}
 
Studente database_cerca_studente(const char *matricola){
    Studente s;
    if(fp_studenti == NULL) return NULL;
    fseek(fp_studenti, 0, SEEK_SET);
    while((s = leggi_studente(fp_studenti)) != NULL){
        if(strcmp(get_matricola(s), matricola) == 0){
            return s;
        }
        distruggi_studente(s);
    }
    return NULL;
}
 
int database_studente_esiste(const char *matricola){
    Studente s;
    if(fp_studenti == NULL) return 0;
    fseek(fp_studenti, 0, SEEK_SET);
    while((s = leggi_studente(fp_studenti)) != NULL){
        if(strcmp(get_matricola(s), matricola) == 0){
            distruggi_studente(s);
            return 1;
        }
        distruggi_studente(s);
    }
    return 0;
}