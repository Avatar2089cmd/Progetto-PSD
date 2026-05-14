#include "report.h"

static FILE *fp_report = NULL;

void report_init(Data data){
    char nome_file[30];
    sprintf(nome_file, "report_%02d_%02d_%04d.txt", data.giorno, data.mese, data.anno);
    fp_report = fopen(nome_file, "a");
    if(fp_report == NULL){
        fprintf(stderr, "Errore nella creazione del file report\n");
        exit(1);
    }
}

void registra_accesso(const char* matricola, FasciaOraria fascia, TipoAccesso tipo, StatoPrenotazione stato) {
    if(fp_report == NULL){
        fprintf(stderr, "Report non inizializzato\n");
        return;
    }
    fprintf(fp_report, "Matricola: %s | Fascia: %s | Tipo: %s | Stato: %s\n",
    matricola,
    fascia == MATTINA ? "Mattina" : fascia == POMERIGGIO ? "Pomeriggio" : "Sera",
    tipo == WALK_IN ? "Walk-in" : "Prenotato",
    stato == CHECKED_IN ? "Check-in" : stato == CHECKED_OUT ? "Check-out" : 
    stato == ANNULLATA ? "Annullata" : stato == NO_SHOW ? "No-show" : "Prenotata"
    );
    fflush(fp_report); //assicuro che i dati vengano scritti su disco
}

void genera_report(ListaPrenotazioni lista, Queue coda_attesa, Data data) {
    int tot_prenotazioni = 0;
    int accessi_effettivi = 0;
    int no_show = 0, annullate = 0, in_attesa = 0;
    int occ_mattina = 0, occ_pomeriggio = 0, occ_sera = 0;
    
    if(fp_report == NULL){
        fprintf(stderr, "Report non inizializzato\n");
        return;
    }
    accessi_effettivi = visualizza_per_stato(lista, CHECKED_IN, 'N') +
                        visualizza_per_stato(lista, CHECKED_OUT, 'N');
    
    no_show = visualizza_per_stato(lista, NO_SHOW, 'N');
    annullate = visualizza_per_stato(lista, ANNULLATA, 'N');
    in_attesa = get_dimensione(coda_attesa);
    tot_prenotazioni = accessi_effettivi + no_show + annullate +
                       visualizza_per_stato(lista, PRENOTATA, 'N');
    
    fprintf(fp_report, "=== REPORT GIORNATA %02d/%02d/%04d ===\n\n",
            data.giorno, data.mese, data.anno);
    
    fprintf(fp_report, "Totale Prenotazioni: %d\n", tot_prenotazioni);
    fprintf(fp_report, "Accessi Effettivi: %d\n", accessi_effettivi);
    fprintf(fp_report, "No-show: %d\n", no_show);
    fprintf(fp_report, "Annullate: %d\n", annullate);
    fprintf(fp_report, "Studenti in attesa: %d\n", in_attesa);

    fprintf(fp_report, "\n--- OCCUPAZIONE PER FASCIA ---\n");
    occ_mattina = aula_get_max_posti() - get_posti_liberi_aula(MATTINA);
    occ_pomeriggio = aula_get_max_posti() - get_posti_liberi_aula(POMERIGGIO);
    occ_sera = aula_get_max_posti() - get_posti_liberi_aula(SERA);

    fprintf(fp_report, "Mattina: %d/%d posti occupati\n", occ_mattina, aula_get_max_posti());
    fprintf(fp_report, "Pomeriggio: %d/%d posti occupati\n", occ_pomeriggio, aula_get_max_posti());
    fprintf(fp_report, "Sera: %d/%d posti occupati\n", occ_sera, aula_get_max_posti());

    fflush(fp_report); //assicuro che i dati vengano scritti su disco
}

void chiudi_report() {
    if(fp_report != NULL){
        fclose(fp_report);
        fp_report = NULL;
    }
}