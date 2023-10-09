#include <iostream>
#include <fstream>
#include <string>

#include "parser.hpp"

using namespace std;
int **adj_matrix;
int k1, k2;

void parse_graph(string path, int part)
{
    std::ifstream f_in{path};
    if (!f_in)
    {
        std::cerr << "Unable to open file" << endl;
        return;
    }
    int n, e;
    f_in >> n >> e;
    if (part == 1)
        f_in >> k1 >> k2;

    int **matrix = new int *[n];
    for (int i = 0; i < n; i++)
        matrix[i] = new int[n]();
    // instantiate the matrix with all zero values. Zero is done by the '()' after int[n];

    for (int i = 0; i < e; i++)
    {
        int v1, v2;
        f_in >> v1 >> v2;
        // use v1 and v2 to put in graph structure
        matrix[v1 - 1][v2 - 1] = 1;
    }
    adj_matrix = matrix;
    // ! delete the matrix somewhere later, after converting values into clauses
    // for (int i = 0; i < n; i++) {
    //     delete[] matrix[i];
    // }
    // delete[] matrix;
}