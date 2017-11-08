cc = gcc -g -Wall

all: client server

client:
	$(cc) -o client.out client.c

server:
	$(cc) -o server.out server.c config.c -lconfig -D _GNU_SOURCE

clean:
	rm -f client.out
	rm -f server.out

libconfig:
	sudo apt-get install libconfig-dev
