CC = g++ -g -Wall
GTEST = -lgtest -lpthread

all: main

main: ring_buffer

ring_buffer:
	$(CC) -o a.out ring_buffer.cpp $(GTEST)

clean:
	rm -f a.out