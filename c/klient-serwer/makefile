cc = gcc -g -Wall

all: client server

client:
	$(cc) -o client.out client.c

server:
	$(cc) -o server.out server.c -lconfig

clean:
	rm -f client.out
	rm -f server.out