CC     = gcc
CFLAGS = -Wall -Wextra -std=c89 -pedantic -I../include
TARGET = aula

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

# Comandi standard Unix/Linux/macOS
MV = mv
RM = rm -f

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
	$(MV) $(TARGET) ../$(TARGET)

../obj/%.o: ../src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	../$(TARGET)

clean:
	$(RM) ../obj/*.o 2>/dev/null || true
	$(RM) ../$(TARGET) 2>/dev/null || true

.PHONY: all run clean
