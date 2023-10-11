CC=g++
CFLAGS=-Wall -std=c++11 -O3 -funroll-loops

part1:
	./scripts/compile.sh
	./scripts/run1.sh data/p1_test1
	./bin/minisat data/p1_test1.satinput data/p1_test1.satoutput -verbosity=0
	./scripts/run2.sh data/p1_test1

# part2: