CC=g++
CFLAGS=-Wall -std=c++11 -O3 -funroll-loops

part1:
	$(CC) $(CFLAGS) src/part1.cpp src/parser.cpp -o bin/part1
	./bin/part1 data/p1_test1.graphs fsdf

# part1_run: