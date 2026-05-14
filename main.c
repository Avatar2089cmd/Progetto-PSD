#include "sistema.h"

int main() {
    Data oggi;

    /* Imposta la data della sessione */
    printf("Inserisci la data della sessione (gg mm aaaa): ");
    scanf("%d %d %d", &oggi.giorno, &oggi.mese, &oggi.anno);

    /* Inizializzazione del sistema */
    sistema_init(oggi);

    /* Avvio del menu principale */
    sistema_esegui();

    /* Chiusura e salvataggio finale */
    sistema_chiudi();

    return 0;
}
