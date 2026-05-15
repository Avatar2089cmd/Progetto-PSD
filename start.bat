@echo off
setlocal enabledelayedexpansion
cd /d "%~dp0"
cls

REM --- RILEVAMENTO COMANDO MAKE ---
set "MAKE_CMD="
where mingw32-make >nul 2>nul
if %errorlevel% equ 0 (
    set "MAKE_CMD=mingw32-make"
) else (
    where make >nul 2>nul
    if %errorlevel% equ 0 (
        set "MAKE_CMD=make"
    )
)

if not defined MAKE_CMD (
    echo ========================================
    echo ERRORE: Make non trovato! 
    echo Assicurati che MinGW sia installato e nel PATH.
    echo ========================================
    pause
    exit /b 1
)

echo ================================
echo Usando: %MAKE_CMD%
echo Compilazione in corso...
echo ================================

%MAKE_CMD% -C Makefile_WIN

if %errorlevel% neq 0 (
    echo.
    echo ================================
    echo Errore durante la compilazione.
    echo ================================
    pause
    exit /b 1
)

cls
echo ================================
echo Esecuzione programma...
echo ================================
echo.

REM --- ESECUZIONE (Cerca l'eseguibile nella root) ---
if exist ".\aula.exe" (
    .\aula.exe
) else (
    echo ERRORE: aula.exe non trovato nella cartella principale.
    set EXITCODE=9009
    goto GESTIONE_CRASH
)

set EXITCODE=%errorlevel%

:GESTIONE_CRASH
echo.
echo ================================
echo Gestione post-esecuzione...
echo ================================

if %EXITCODE%==0 (
    echo Uscita normale: pulizia...
    %MAKE_CMD% -C Makefile_WIN clean
) else (
    echo Crash o errore rilevato (Codice: %EXITCODE%)
    del /Q obj\*.o 2>nul

    if not exist crash_report_client mkdir crash_report_client

    for %%F in (crash_report_client\*_LATEST.log) do (
        set "oldname=%%~nF"
        ren "%%F" "!oldname:~0,-7!%%~xF"
    )

    for /f "tokens=2 delims==" %%I in ('wmic os get localdatetime /value') do set datetime=%%I
    set "STAMP=!datetime:~0,8!_!datetime:~8,6!"

    (
        echo ===== CRASH LOG =====
        echo Data/Ora: %date% %time%
        echo Exit code: %EXITCODE%
        echo ======================
    ) > "crash_report_client\crash_!STAMP!_LATEST.log"

    echo Report salvato: crash_!STAMP!_LATEST.log
)

echo.
echo ================================
echo Programma terminato.
echo ================================
pause


