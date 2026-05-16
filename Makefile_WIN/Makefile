CC     = gcc
CFLAGS = -Wall -Wextra -std=c89 -pedantic -I../include
TARGET = aula.exe

SRC = ../src/main.c \
      ../src/sistema.c \
      ../src/database.c \
      ../src/aula.c \
      ../src/lista_dinamica.c \
      ../src/prenotazione.c \
      ../src/queue.c \
      ../src/report.c \
      ../src/studente.c

OBJ = ../obj/main.o \
      ../obj/sistema.o \
      ../obj/database.o \
      ../obj/aula.o \
      ../obj/lista_dinamica.o \
      ../obj/prenotazione.o \
      ../obj/queue.o \
      ../obj/report.o \
      ../obj/studente.o

# Rileva se siamo in ambiente MSYS2/Unix-like o CMD nativo
# MSYS2 e Git Bash definiscono la variabile MSYSTEM (es. MINGW64, UCRT64)
# Se MSYSTEM e' definita usiamo sintassi Unix, altrimenti CMD
ifdef MSYSTEM
	MV    = mv
	RM    = rm -f
	RMDIR = rm -f
else
	MV    = move
	RM    = del /Q
	RMDIR = del /Q
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
	$(MV) $(TARGET) ..\$(TARGET)

../obj/%.o: ../src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	..\$(TARGET)

clean:
ifdef MSYSTEM
	$(RM) ../obj/*.o 2>/dev/null; true
	$(RM) ../$(TARGET) 2>/dev/null; true
else
	if exist ..\obj\*.o $(RM) ..\obj\*.o
	if exist ..\$(TARGET) $(RM) ..\$(TARGET)
endif

.PHONY: all run clean
