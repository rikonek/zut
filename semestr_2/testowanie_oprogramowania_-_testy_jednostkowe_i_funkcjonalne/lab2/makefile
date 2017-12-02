cc = g++ -g -Wall -std=gnu++14

all: lab2 lab3

lab2: lab2.cpp Picture.o Rectangle.o Triangle.o
	$(cc) -o lab2.out lab2.cpp src/Picture.o src/Rectangle.o src/Triangle.o -pthread -lgtest

lab3: lab3.cpp Picture.o Rectangle.o Triangle.o
	$(cc) -o lab3.out lab3.cpp src/Picture.o src/Rectangle.o src/Triangle.o -pthread -lgtest

Picture.o: src/Picture.cpp
	$(cc) -c -o src/Picture.o src/Picture.cpp

Rectangle.o: src/Rectangle.cpp
	$(cc) -c -o src/Rectangle.o src/Rectangle.cpp

Triangle.o: src/Triangle.cpp
	$(cc) -c -o src/Triangle.o src/Triangle.cpp

clean:
	rm -f *.out *.o