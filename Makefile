CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = aula

SRC = main.c \
      sistema.c \
      database.c \
      aula.c \
      lista_dinamica.c \
      prenotazione.c \
      queue.c \
      report.c \
      studente.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)

