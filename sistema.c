/*
 * Nome file: sistema.c
 * Autore: Ranucci Simone, Scaldaferri Ilaria
 * Descrizione: Implementazione del coordinatore centrale del sistema.
 * Gestisce i due menu (studente / amministratore), le operazioni di
 * prenotazione, check-in, check-out, lista d'attesa con promozione
 * automatica e generazione dei report.
 */

#include "sistema.h"
#include "studente.h"
#include "prenotazione.h"

/* ------------------------------------------------------------------ */
/*  STATO GLOBALE DELLA SESSIONE                                       */
/* ------------------------------------------------------------------ */

static ListaPrenotazioni lista_prenotazioni = NULL;
static Queue coda_attesa = NULL;
static Data data_sessione;

/* ------------------------------------------------------------------ */
/*  UTILITY LOCALI                                                     */
/* ------------------------------------------------------------------ */

static void svuota_buffer(void){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

static const char* fascia_to_str(FasciaOraria f){
    switch(f){
        case MATTINA:    return "Mattina    (08:00-13:00)";
        case POMERIGGIO: return "Pomeriggio (13:00-18:00)";
        case SERA:       return "Sera       (18:00-23:00)";
        default:         return "Sconosciuta";
    }
}

static FasciaOraria leggi_fascia(void){
    int scelta;
    printf("  1. Mattina    (08:00-13:00)\n");
    printf("  2. Pomeriggio (13:00-18:00)\n");
    printf("  3. Sera       (18:00-23:00)\n");
    printf("Scelta: ");
    if(scanf("%d", &scelta) != 1){ svuota_buffer(); return (FasciaOraria)-1; }
    svuota_buffer();
    if(scelta < 1 || scelta > 3) return (FasciaOraria)-1;
    return (FasciaOraria)(scelta - 1);
}

static void leggi_matricola(char *buf, int size){
    printf("Inserisci matricola: ");
    scanf("%10s", buf);
    buf[size - 1] = '\0';
    svuota_buffer();
}

/* ------------------------------------------------------------------ */
/*  PROMOZIONE AUTOMATICA DALLA CODA ATTESA                           */
/* ------------------------------------------------------------------ */

static void promuovi_dalla_coda(FasciaOraria fascia){
    Queue tmp;
    FasciaOraria f;
    const char *m;
    TipoAccesso t;
    Prenotazione p;
    int posto;

    tmp = crea_queue();
    if(tmp == NULL) return;

    while(!is_empty(coda_attesa)){
        f = queue_peek_fascia(coda_attesa);
        m = queue_peek_matricola(coda_attesa);
        t = queue_peek_tipo(coda_attesa);

        if(f == fascia && get_posti_liberi_aula(fascia) > 0){
            p = crea_prenotazione(m, data_sessione, fascia);
            if(p != NULL){
                posto = blocca_posto_aula(fascia);
                set_posto_prenotazione(p, posto);
                set_stato_prenotazione(p, CHECKED_IN);
                aggiungi_prenotazione(lista_prenotazioni, p);
                registra_accesso(m, fascia, t, CHECKED_IN);
                printf("[INFO] Studente %s promosso dalla lista d'attesa -> posto %d (%s)\n",
                       m, posto, fascia_to_str(fascia));
            }
            dequeue(coda_attesa);
        } else {
            enqueue(tmp, m, f, t);
            dequeue(coda_attesa);
        }
    }

    while(!is_empty(tmp)){
        enqueue(coda_attesa,
                queue_peek_matricola(tmp),
                queue_peek_fascia(tmp),
                queue_peek_tipo(tmp));
        dequeue(tmp);
    }
    distruggi_queue(tmp);
}

/* ------------------------------------------------------------------ */
/*  OPERAZIONI CONDIVISE                                               */
/* ------------------------------------------------------------------ */

static void mostra_disponibilita(void){
    printf("\n--- Disponibilita' posti ---\n");
    printf("  Mattina:    %d posti liberi\n", get_posti_liberi_aula(MATTINA));
    printf("  Pomeriggio: %d posti liberi\n", get_posti_liberi_aula(POMERIGGIO));
    printf("  Sera:       %d posti liberi\n", get_posti_liberi_aula(SERA));
    printf("----------------------------\n");
}

static void op_prenota(const char *matricola){
    FasciaOraria fascia;
    Prenotazione p;
    int posto;

    if(!database_studente_esiste(matricola)){
        printf("[ERRORE] Matricola %s non trovata nel database.\n", matricola);
        return;
    }

    printf("Seleziona fascia oraria:\n");
    fascia = leggi_fascia();
    if((int)fascia < 0){ printf("[ERRORE] Fascia non valida.\n"); return; }

    p = cerca_prenotazione(lista_prenotazioni, matricola, fascia);
    if(p != NULL && prenotazione_get_stato(p) != ANNULLATA){
        printf("[ERRORE] Esiste gia' una prenotazione per questa fascia.\n");
        return;
    }

    if(get_posti_liberi_aula(fascia) <= 0){
        enqueue(coda_attesa, matricola, fascia, PRENOTAZIONE);
        printf("[INFO] Aula piena. Sei stato aggiunto alla lista d'attesa per %s.\n",
               fascia_to_str(fascia));
        return;
    }

    posto = blocca_posto_aula(fascia);
    p = crea_prenotazione(matricola, data_sessione, fascia);
    if(p == NULL){ libera_posto_aula(fascia, posto); return; }
    set_posto_prenotazione(p, posto);
    aggiungi_prenotazione(lista_prenotazioni, p);
    registra_accesso(matricola, fascia, PRENOTAZIONE, PRENOTATA);
    printf("[OK] Prenotazione confermata: posto %d, %s\n", posto, fascia_to_str(fascia));
}

static void op_annulla_prenotazione(const char *matricola){
    FasciaOraria fascia;
    Prenotazione p;

    printf("Seleziona fascia da annullare:\n");
    fascia = leggi_fascia();
    if((int)fascia < 0){ printf("[ERRORE] Fascia non valida.\n"); return; }

    p = cerca_prenotazione(lista_prenotazioni, matricola, fascia);
    if(p == NULL){
        printf("[ERRORE] Nessuna prenotazione trovata.\n");
        return;
    }
    if(prenotazione_get_stato(p) == ANNULLATA){
        printf("[INFO] Prenotazione gia' annullata.\n");
        return;
    }

    libera_posto_aula(fascia, prenotazione_get_posto(p));
    aggiorna_stato_prenotazione(lista_prenotazioni, matricola, fascia, ANNULLATA);
    registra_accesso(matricola, fascia, PRENOTAZIONE, ANNULLATA);
    printf("[OK] Prenotazione annullata.\n");

    promuovi_dalla_coda(fascia);
}

/* ------------------------------------------------------------------ */
/*  MENU STUDENTE                                                      */
/* ------------------------------------------------------------------ */

static void menu_studente(void){
    int scelta;
    char matricola[MAX_MATRICOLA];
    char nome[20];
    char corso[30];
    FasciaOraria f;
    Prenotazione p;
    Studente s;

    printf("\n=== ACCESSO STUDENTE ===\n");
    leggi_matricola(matricola, MAX_MATRICOLA);

    if(!database_studente_esiste(matricola)){
        printf("[INFO] Matricola non trovata. Registrazione necessaria.\n");
        printf("Nome: "); scanf("%19s", nome); svuota_buffer();
        printf("Corso di laurea: "); scanf("%29s", corso); svuota_buffer();
        s = crea_studente(nome, matricola, corso);
        if(s != NULL){
            database_salva_studente(s);
            distruggi_studente(s);
            printf("[OK] Registrazione completata.\n");
        }
    }

    do {
        printf("\n--- Menu Studente (%s) ---\n", matricola);
        printf("  1. Visualizza disponibilita' posti\n");
        printf("  2. Prenota un posto\n");
        printf("  3. Annulla una prenotazione\n");
        printf("  4. Visualizza le mie prenotazioni\n");
        printf("  0. Esci\n");
        printf("Scelta: ");
        if(scanf("%d", &scelta) != 1){ svuota_buffer(); scelta = -1; }
        svuota_buffer();

        switch(scelta){
            case 1:
                mostra_disponibilita();
                break;

            case 2:
                op_prenota(matricola);
                break;

            case 3:
                op_annulla_prenotazione(matricola);
                break;

            case 4:
                printf("\n--- Le tue prenotazioni ---\n");
                for(f = MATTINA; f < NUM_FASCE; f++){
                    p = cerca_prenotazione(lista_prenotazioni, matricola, f);
                    if(p != NULL){
                        visualizza_prenotazione(p);
                        printf("---\n");
                    }
                }
                break;

            case 0:
                printf("Arrivederci!\n");
                break;

            default:
                printf("[ERRORE] Scelta non valida.\n");
                break;
        }
    } while(scelta != 0);
}

/* ------------------------------------------------------------------ */
/*  MENU AMMINISTRATORE                                                */
/* ------------------------------------------------------------------ */

static void menu_amministratore(void){
    int scelta;
    char matricola[MAX_MATRICOLA];
    char nome[20];
    char corso[30];
    FasciaOraria fascia;
    Prenotazione p;
    int posto;
    int n;
    int i;
    Queue tmp;
    Studente s;

    do {
        printf("\n=== MENU AMMINISTRATORE ===\n");
        printf("  1.  Registra nuovo studente\n");
        printf("  2.  Prenota posto per uno studente\n");
        printf("  3.  Annulla prenotazione\n");
        printf("  4.  Check-in studente prenotato\n");
        printf("  5.  Accesso diretto (walk-in)\n");
        printf("  6.  Check-out studente\n");
        printf("  7.  Visualizza prenotati per fascia\n");
        printf("  8.  Visualizza presenti (checked-in)\n");
        printf("  9.  Visualizza lista d'attesa\n");
        printf("  10. Disponibilita' posti\n");
        printf("  11. Genera report giornaliero\n");
        printf("  0.  Esci\n");
        printf("Scelta: ");
        if(scanf("%d", &scelta) != 1){ svuota_buffer(); scelta = -1; }
        svuota_buffer();

        switch(scelta){

            case 1:
                printf("Nome: "); scanf("%19s", nome); svuota_buffer();
                leggi_matricola(matricola, MAX_MATRICOLA);
                printf("Corso di laurea: "); scanf("%29s", corso); svuota_buffer();
                if(database_studente_esiste(matricola)){
                    printf("[ERRORE] Matricola gia' presente.\n");
                    break;
                }
                s = crea_studente(nome, matricola, corso);
                if(s == NULL){ printf("[ERRORE] Allocazione fallita.\n"); break; }
                database_salva_studente(s);
                distruggi_studente(s);
                printf("[OK] Studente registrato.\n");
                break;

            case 2:
                leggi_matricola(matricola, MAX_MATRICOLA);
                op_prenota(matricola);
                break;

            case 3:
                leggi_matricola(matricola, MAX_MATRICOLA);
                op_annulla_prenotazione(matricola);
                break;

            case 4:
                leggi_matricola(matricola, MAX_MATRICOLA);
                printf("Seleziona fascia:\n");
                fascia = leggi_fascia();
                if((int)fascia < 0){ printf("[ERRORE] Fascia non valida.\n"); break; }
                p = cerca_prenotazione(lista_prenotazioni, matricola, fascia);
                if(p == NULL || prenotazione_get_stato(p) != PRENOTATA){
                    printf("[ERRORE] Nessuna prenotazione attiva trovata.\n");
                    break;
                }
                aggiorna_stato_prenotazione(lista_prenotazioni, matricola, fascia, CHECKED_IN);
                registra_accesso(matricola, fascia, PRENOTAZIONE, CHECKED_IN);
                printf("[OK] Check-in effettuato: posto %d, %s\n",
                       prenotazione_get_posto(p), fascia_to_str(fascia));
                break;

            case 5:
                leggi_matricola(matricola, MAX_MATRICOLA);
                if(!database_studente_esiste(matricola)){
                    printf("[ERRORE] Matricola non registrata.\n");
                    break;
                }
                printf("Seleziona fascia:\n");
                fascia = leggi_fascia();
                if((int)fascia < 0){ printf("[ERRORE] Fascia non valida.\n"); break; }
                if(get_posti_liberi_aula(fascia) <= 0){
                    enqueue(coda_attesa, matricola, fascia, WALK_IN);
                    printf("[INFO] Aula piena. Studente aggiunto alla lista d'attesa.\n");
                    break;
                }
                posto = blocca_posto_aula(fascia);
                p = crea_prenotazione(matricola, data_sessione, fascia);
                if(p == NULL){ libera_posto_aula(fascia, posto); break; }
                set_posto_prenotazione(p, posto);
                set_stato_prenotazione(p, CHECKED_IN);
                aggiungi_prenotazione(lista_prenotazioni, p);
                registra_accesso(matricola, fascia, WALK_IN, CHECKED_IN);
                printf("[OK] Accesso diretto: posto %d, %s\n", posto, fascia_to_str(fascia));
                break;

            case 6:
                leggi_matricola(matricola, MAX_MATRICOLA);
                printf("Seleziona fascia:\n");
                fascia = leggi_fascia();
                if((int)fascia < 0){ printf("[ERRORE] Fascia non valida.\n"); break; }
                p = cerca_prenotazione(lista_prenotazioni, matricola, fascia);
                if(p == NULL || prenotazione_get_stato(p) != CHECKED_IN){
                    printf("[ERRORE] Studente non risulta presente in aula.\n");
                    break;
                }
                libera_posto_aula(fascia, prenotazione_get_posto(p));
                aggiorna_stato_prenotazione(lista_prenotazioni, matricola, fascia, CHECKED_OUT);
                registra_accesso(matricola, fascia, PRENOTAZIONE, CHECKED_OUT);
                printf("[OK] Check-out effettuato.\n");
                promuovi_dalla_coda(fascia);
                break;

            case 7:
                printf("Seleziona fascia:\n");
                fascia = leggi_fascia();
                if((int)fascia < 0){ printf("[ERRORE] Fascia non valida.\n"); break; }
                printf("\n--- Prenotati per %s ---\n", fascia_to_str(fascia));
                visualizza_per_stato(lista_prenotazioni, PRENOTATA, 'S');
                break;

            case 8:
                printf("\n--- Studenti attualmente in aula ---\n");
                visualizza_per_stato(lista_prenotazioni, CHECKED_IN, 'S');
                break;

            case 9:
                n = get_dimensione(coda_attesa);
                i = 0;
                printf("\n--- Lista d'attesa (%d studenti) ---\n", n);
                if(n == 0){ printf("  (vuota)\n"); break; }
                tmp = crea_queue();
                while(!is_empty(coda_attesa)){
                    printf("  %d. Matricola: %-10s | Fascia: %s\n",
                           ++i,
                           queue_peek_matricola(coda_attesa),
                           fascia_to_str(queue_peek_fascia(coda_attesa)));
                    enqueue(tmp,
                            queue_peek_matricola(coda_attesa),
                            queue_peek_fascia(coda_attesa),
                            queue_peek_tipo(coda_attesa));
                    dequeue(coda_attesa);
                }
                while(!is_empty(tmp)){
                    enqueue(coda_attesa,
                            queue_peek_matricola(tmp),
                            queue_peek_fascia(tmp),
                            queue_peek_tipo(tmp));
                    dequeue(tmp);
                }
                distruggi_queue(tmp);
                break;

            case 10:
                mostra_disponibilita();
                break;

            case 11:
                genera_report(lista_prenotazioni, coda_attesa, data_sessione);
                printf("[OK] Report generato.\n");
                break;

            case 0:
                printf("Uscita dal pannello amministratore.\n");
                break;

            default:
                printf("[ERRORE] Scelta non valida.\n");
                break;
        }
    } while(scelta != 0);
}

/* ------------------------------------------------------------------ */
/*  INTERFACCIA PUBBLICA                                               */
/* ------------------------------------------------------------------ */

void sistema_init(Data data){
    data_sessione = data;
    database_init();
    aula_init();
    lista_prenotazioni = crea_lista_prenotazioni();
    coda_attesa = crea_queue();
    report_init(data);

    if(lista_prenotazioni == NULL || coda_attesa == NULL){
        fprintf(stderr, "Impossibile allocare le strutture dati principali.\n");
        exit(1);
    }
}

void sistema_esegui(void){
    int ruolo;

    printf("\n----------------------------------------\n");
    printf("||  Sistema Gestione Aula Studio       ||\n");
    printf("----------------------------------------\n");
    printf("Data sessione: %02d/%02d/%04d\n\n",
           data_sessione.giorno, data_sessione.mese, data_sessione.anno);

    printf("Sei uno studente o un amministratore?\n");
    printf("  1. Studente\n");
    printf("  2. Amministratore\n");
    printf("Scelta: ");
    if(scanf("%d", &ruolo) != 1){ svuota_buffer(); ruolo = -1; }
    svuota_buffer();

    switch(ruolo){
        case 1: menu_studente(); break;
        case 2: menu_amministratore(); break;
        default:
            printf("[ERRORE] Scelta non valida. Programma terminato.\n");
            break;
    }
}

void sistema_chiudi(void){
    genera_report(lista_prenotazioni, coda_attesa, data_sessione);
    chiudi_report();
    distruggi_lista_prenotazioni(lista_prenotazioni);
    distruggi_queue(coda_attesa);
    database_chiudi();
}
