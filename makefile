CC=gcc
CFLAGS=-lm -lSDL2 -g

graph: main.o
	$(CC) -o graph main.c $(CFLAGS)
