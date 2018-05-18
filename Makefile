CC=gcc

.SILENT:

.PHONY: all clean run

all: main test_client

clean:
	rm -f *.o main test_client

main: main.o server.o
	$(CC) -o main main.o server.o -lpthread

main.o: main.c 
	$(CC) -c main.c

server.o: server.c
	$(CC) -c server.c

test_client: test_client.o
	$(CC) -o test_client test_client.o

test_client.o: test_client.c
	$(CC) -c test_client.c