#ifndef REPORT_H
#define REPORT_H

#include "shared.h"
#include "lista_dinamica.h"
#include "queue.h"

void genera_report(ListaPrenotazioni lista, Queue coda_report, Data data);
void registra_accesso(const char* matricola, FasciaOraria fascia, TipoAccesso tipo, StatoPrenotazione stato); 
void chiudi_report();

#endif // REPORT_H