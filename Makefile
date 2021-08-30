CC = gcc
CFLAGS = -Wall -pedantic -ansi
BIN = freq.exe
OBJ = collision_graph.o stack.o vector.o main.o

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN): $(OBJ)
	$(CC) $^ -o $@ -lm

