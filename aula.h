#ifndef AULA_H
#define AULA_H

#include "base.h"

int get_posti_liberi_aula(FasciaOraria fascia); //restituisce i posti liberi
int blocca_posto_aula(FasciaOraria fascia); //modifica lo stato del posto in aula

void libera_posto_aula(FasciaOraria fascia, int posto); //setta a "libero" il posto in aula
void libera_fascia_aula(FasciaOraria fascia); //check out e ripristino dei posti in automatico

#endif // AULA_H