CC = gcc

CFLAGS = -g -Wall -Werror
LDFLAGS = -g

all: client server

CLIENT_LIBS=client.o
SERVER_LIBS=server.o config.o

client: $(CLIENT_LIBS)
	$(CC) $(LDFLAGS) -o client.out $^

server: $(SERVER_LIBS)
	$(CC) $(LDFLAGS) -o server.out $^ -lconfig -D _GNU_SOURCE

%o: %c
	$(CC) $(CFLAGS) -o $@ $<

clean: 
	-@rm -f client.out $(CLIENT_LIBS)
	-@rm -f server.out $(SERVER_LIBS)

libconfig:
	sudo apt-get install libconfig-dev
