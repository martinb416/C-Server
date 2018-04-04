CC=gcc

.SILENT:

.PHONY: all clean run

all: main

clean:
	rm -f *.o main

main: main.o
	$(CC) -o main main.o

main.o: main.c 
	$(CC) -c main.c