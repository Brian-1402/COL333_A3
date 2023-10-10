#include <string>

struct Graph
{
    int **adj_matrix;
    int n, e, k1, k2;
    int *color; // array of size n which has 0 for no org, 1 for drug org1, 2 for org 2.
};

void parse_graph(Graph *G, std::string path, int part);

void output_graph(Graph *G, std::string path, int part);

void print_graph(Graph *G);

void delete_graph(Graph *G);
