cc = g++ -g -Wall -std=gnu++14

all: main picture.o rectangle.o triangle.o
	$(cc) -o a.out main.o Picture.o Rectangle.o Triangle.o

main: main.cpp
	$(cc) -c -o main.o main.cpp

picture.o: Picture.cpp
	$(cc) -c -o Picture.o Picture.cpp

rectangle.o: Rectangle.cpp
	$(cc) -c -o Rectangle.o Rectangle.cpp

triangle.o: Triangle.cpp
	$(cc) -c -o Triangle.o Triangle.cpp

clean:
	rm -f a.out *.o
