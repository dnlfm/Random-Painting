BIN = artwork
SRC = src/Coordenadas.c src/TADFigura.c src/TADQuadro.c src/main.c

CC=gcc

CFLAGS=-O2 -march=native
LFLAGS=-static

all: compile

compile:
	$(CC) -o $(BIN) $(SRC) $(CFLAGS) $(LFLAGS)

run:
	./$(BIN)
