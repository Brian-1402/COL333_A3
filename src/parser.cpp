#include <iostream>
#include <fstream>
#include <string>

#include "parser.hpp"

void parse_graph(Graph *G, std::string path, int part)
{
    std::ifstream f_in{path};
    if (!f_in)
    {
        std::cerr << "Unable to open file" << std::endl;
        return;
    }

    int n, e;
    f_in >> n >> e;
    if (part == 1)
        f_in >> G->k1 >> G->k2;

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
    G->n = n;
    G->e = e;
    G->adj_matrix = matrix;
}

void output_graph(Graph *G, std::string path, int part)
{
    std::ifstream f_out{path};
    if (!f_out)
    {
        std::cerr << "Unable to open file" << std::endl;
        return;
    }
    // incomplete
}

void print_graph(Graph *G)
{
    std::cout << "\nAdjacency matrix:\n";
    for (int i = 0; i < G->n; i++)
    {
        for (int j = 0; j < G->n; j++)
        {
            std::cout << G->adj_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void delete_graph(Graph *G)
{
    for (int i = 0; i < G->n; i++)
    {
        delete[] G->adj_matrix[i];
    }
    delete[] G->adj_matrix;
    delete[] G;
}