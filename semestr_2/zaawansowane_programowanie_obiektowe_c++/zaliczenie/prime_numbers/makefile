CC = g++ -g -Wall
GTEST = -lgtest -lpthread

all: main

main: prime_numbers

prime_numbers:
	$(CC) -o a.out prime_numbers.cpp -pthread -lgmp

clean:
	rm -f a.out

install:
	sudo apt-get install libgmp-dev