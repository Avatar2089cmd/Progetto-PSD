#!/bin/bash

# Spostati nella directory dove si trova lo script
cd "$(dirname "$0")"

clear
echo "================================"
echo "Compilazione in corso (Linux/macOS)..."
echo "================================"

# Su Linux/mac il comando è quasi sempre 'make'
MAKE_CMD="make"

if ! command -v $MAKE_CMD &> /dev/null; then
    echo "ERRORE: 'make' non trovato. Installalo con 'sudo apt install build-essential' o simili."
    exit 1
fi

# Esegue il Makefile spostandosi dentro la directory 'Makefile_LX_MOS'
$MAKE_CMD -C Makefile_LX_MOS

if [ $? -ne 0 ]; then
    echo ""
    echo "================================"
    echo "Errore durante la compilazione."
    echo "================================"
    exit 1
fi

clear
echo "================================"
echo "Esecuzione programma..."
echo "================================"
echo ""

# --- ESECUZIONE ---
# Assicurati che l'eseguibile abbia i permessi
chmod +x ./aula 2>/dev/null

./aula
EXITCODE=$?

echo ""
echo "================================"
echo "Gestione post-esecuzione..."
echo "================================"

if [ $EXITCODE -eq 0 ]; then
    echo "Uscita normale: pulizia..."
    # Corretto anche qui per fare la pulizia nella cartella giusta
    $MAKE_CMD -C Makefile_LX_MOS clean
else
    echo "Crash o errore rilevato (Codice: $EXITCODE)"
    
    # Pulizia oggetti
    rm -f ../obj/*.o 2>/dev/null

    # Creazione cartella report
    mkdir -p crash_report_client

    # --- GESTIONE ETICHETTA _LATEST ---
    # Rinomina il vecchio file _LATEST togliendo il suffisso
    for f in crash_report_client/*_LATEST.log; do
        if [ -f "$f" ]; then
            mv "$f" "${f%_LATEST.log}.log"
        fi
    done

    # --- GENERAZIONE TIMESTAMP (Formato: YYYYMMDD_HHMMSS) ---
    STAMP=$(date +%Y%m%d_%H%M%S)
    LOGFILE="crash_${STAMP}_LATEST.log"

    # --- SCRITTURA LOG ---
    {
        echo "===== CRASH LOG ====="
        echo "Data/Ora: $(date '+%d/%m/%Y %H:%M:%S')"
        echo "Exit code: $EXITCODE"
        echo "======================"
    } > "crash_report_client/$LOGFILE"

    echo ""
    echo "================================"
    echo "Report salvato: $LOGFILE"
    echo "================================"
fi

echo ""
echo "================================"
echo "Programma terminato."
echo "================================"
read -p "Premi invio per uscire..."
