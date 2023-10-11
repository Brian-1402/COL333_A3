#include <iostream>
#include <fstream>
#include <string>

#include "graph.hpp"

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
    // G = new Graph(n, e, 0, 0);
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
        matrix[v2 - 1][v1 - 1] = 1;
        // G->adj_matrix[v1 - 1][v2 - 1] = 1;
        // G->adj_matrix[v2 - 1][v1 - 1] = 1;
    }
    G->n = n;
    G->e = e;
    G->adj_matrix = matrix;
    G->color = new int[n]();
}

void output_graph(Graph *G, std::string path, int part)
{
    std::ofstream f_out{path};
    if (!f_out)
    {
        std::cerr << "Unable to open file" << std::endl;
        return;
    }
    if (!G->satisfiable)
    {
        f_out << "0";
        return;
    }
    f_out << "#1\n";
    bool line_start = true;
    for (int i = 0; i < G->n; i++)
        if (G->color[i] == 1)
        {
            if (!line_start)
                f_out << " " << i + 1;
            else
            {
                f_out << i + 1;
                line_start = false;
            }
        }

    if (part == 1)
    {
        bool line_start = true;
        f_out << "\n#2\n";
        for (int i = 0; i < G->n; i++)
            if (G->color[i] == 2)
            {
                if (!line_start)
                    f_out << " " << i + 1;
                else
                {
                    f_out << i + 1;
                    line_start = false;
                }
            }
    }
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
    delete[] G->color;
    delete G;
}

bool check_connectivity(Graph *G)
{
    for (int i = 0; i < G->n; i++)
        for (int j = i + 1; j < G->n; j++)
            if (G->adj_matrix[i][j] == 0)
                return false;
    return true;
}
