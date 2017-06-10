cc = g++

all: main

function.o: function.cpp
	$(cc) -c -o function.o function.cpp

main.o: main.cpp
	$(cc) -c -o main.o main.cpp

main: main.o function.o
	$(cc) -o a.out main.o function.o