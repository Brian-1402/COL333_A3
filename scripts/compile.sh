CC=g++
CXXFLAGS="-Wall -std=c++11 -O3 -funroll-loops"

$CC $CXXFLAGS src/part1_in.cpp src/graph.cpp src/sat.cpp -o bin/part1_in
$CC $CXXFLAGS src/part1_out.cpp src/graph.cpp src/sat.cpp -o bin/part1_out

$CC $CXXFLAGS src/part2.cpp src/graph.cpp src/sat.cpp -o bin/part2
