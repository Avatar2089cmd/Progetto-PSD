CC = gcc
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

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
	move $(TARGET) ..\$(TARGET) >nul

../obj/%.o: ../src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	if exist ..\obj\*.o del /Q ..\obj\*.o
	if exist ..\$(TARGET) del /Q ..\$(TARGET)

