/*
 * Nome file: report.c
 * Autore: Ranucci Simone, Scaldaferri Ilaria
 */

#include "report.h"
#include "aula.h"
#include "lista_dinamica.h"


#ifdef _WIN32
#include <sys/stat.h>
#define CREA_DIR(p) mkdir(p)
#else
#include <sys/stat.h>
#define CREA_DIR(p) mkdir(p, 0755)
#endif
 
#define CARTELLA_STORICO "storico"
 
static FILE *fp_report = NULL;
 
/* Funzioni statiche per conversione enum -> stringa */
static const char* fascia_str(FasciaOraria f){
    switch(f){
        case MATTINA:    return "Mattina";
        case POMERIGGIO: return "Pomeriggio";
        case SERA:       return "Sera";
        default:         return "Sconosciuta";
    }
}
 
static const char* tipo_str(TipoAccesso t){
    return t == WALK_IN ? "Walk-in" : "Prenotato";
}
 
static const char* stato_str(StatoPrenotazione s){
    switch(s){
        case CHECKED_IN:  return "Check-in";
        case CHECKED_OUT: return "Check-out";
        case ANNULLATA:   return "Annullata";
        case NO_SHOW:     return "No-show";
        default:          return "Prenotata";
    }
}
 
void report_init(Data data){
    char nome_file[64];
    /* Crea la cartella storico se non esiste */
    CREA_DIR(CARTELLA_STORICO);
    sprintf(nome_file, "%s/report_%02d_%02d_%04d.txt",
            CARTELLA_STORICO, data.giorno, data.mese, data.anno);
    /* Apre in scrittura — sovrascrive il file precedente della stessa data */
    fp_report = fopen(nome_file, "w");
    if(fp_report == NULL){
        fprintf(stderr, "Errore nella creazione del file report\n");
        exit(1);
    }
}
 
void registra_accesso(const char* matricola, FasciaOraria fascia,
                      TipoAccesso tipo, StatoPrenotazione stato){
    if(fp_report == NULL){
        fprintf(stderr, "Report non inizializzato\n");
        return;
    }
    fprintf(fp_report, "Matricola: %s | Fascia: %s | Tipo: %s | Stato: %s\n",
            matricola, fascia_str(fascia), tipo_str(tipo), stato_str(stato));
    fflush(fp_report);
}
 
void genera_report(ListaPrenotazioni lista, Queue coda_attesa, Data data){
    int tot_prenotazioni;
    int accessi_effettivi;
    int no_show;
    int annullate;
    int in_attesa;
    int occ_mattina;
    int occ_pomeriggio;
    int occ_sera;
    int max_posti;
 
    if(fp_report == NULL){
        fprintf(stderr, "Report non inizializzato\n");
        return;
    }
 
    /* Calcolo contatori dalla lista prenotazioni */
    accessi_effettivi = visualizza_per_stato(lista, CHECKED_IN,  'N')
                      + visualizza_per_stato(lista, CHECKED_OUT, 'N');
    no_show           = visualizza_per_stato(lista, NO_SHOW,     'N');
    annullate         = visualizza_per_stato(lista, ANNULLATA,   'N');
    in_attesa         = get_dimensione(coda_attesa);
    tot_prenotazioni  = accessi_effettivi + no_show + annullate
                      + visualizza_per_stato(lista, PRENOTATA,   'N');
 
    /*
     * Occupazione per fascia: contiamo quante prenotazioni hanno avuto
     * accesso effettivo (CHECKED_IN o CHECKED_OUT) per fascia.
     * Usiamo conta_per_stato_e_fascia per non dipendere dalla matrice
     * aula (che viene liberata durante il checkout).
     */
    occ_mattina    = conta_per_stato_e_fascia(lista, CHECKED_IN,  MATTINA)
                   + conta_per_stato_e_fascia(lista, CHECKED_OUT, MATTINA);
    occ_pomeriggio = conta_per_stato_e_fascia(lista, CHECKED_IN,  POMERIGGIO)
                   + conta_per_stato_e_fascia(lista, CHECKED_OUT, POMERIGGIO);
    occ_sera       = conta_per_stato_e_fascia(lista, CHECKED_IN,  SERA)
                   + conta_per_stato_e_fascia(lista, CHECKED_OUT, SERA);
 
    max_posti = aula_get_max_posti();
 
    /* Scrittura report */
    fprintf(fp_report, "\n=== REPORT GIORNATA %02d/%02d/%04d ===\n\n",
            data.giorno, data.mese, data.anno);
    fprintf(fp_report, "Totale Prenotazioni:  %d\n", tot_prenotazioni);
    fprintf(fp_report, "Accessi Effettivi:    %d\n", accessi_effettivi);
    fprintf(fp_report, "No-show:              %d\n", no_show);
    fprintf(fp_report, "Annullate:            %d\n", annullate);
    fprintf(fp_report, "Studenti in attesa:   %d\n", in_attesa);
    fprintf(fp_report, "\n--- OCCUPAZIONE PER FASCIA ---\n");
    fprintf(fp_report, "Mattina:    %d/%d posti occupati\n", occ_mattina,    max_posti);
    fprintf(fp_report, "Pomeriggio: %d/%d posti occupati\n", occ_pomeriggio, max_posti);
    fprintf(fp_report, "Sera:       %d/%d posti occupati\n", occ_sera,       max_posti);
    fprintf(fp_report, "\n==============================\n");
    fflush(fp_report);
}
 
void chiudi_report(void){
    if(fp_report != NULL){
        fclose(fp_report);
        fp_report = NULL;
    }
}