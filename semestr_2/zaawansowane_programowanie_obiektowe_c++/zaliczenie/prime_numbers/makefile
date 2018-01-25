CC = g++ -g -Wall
GTEST = -lgtest -lpthread

all: main

main: prime_numbers

prime_numbers: prime_numbers.cpp trial_division.o miller_rabin.o
	$(CC) -o a.out prime_numbers.cpp trial_division.o miller_rabin.o -pthread -lgmp

trial_division.o: trial_division.cpp
	$(CC) -c -o trial_division.o trial_division.cpp

miller_rabin.o: miller_rabin.cpp
	$(CC) -c -o miller_rabin.o miller_rabin.cpp

clean:
	rm -f a.out
	rm -f *.o

install:
	sudo apt-get install libgmp-dev