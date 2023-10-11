#include <string>

struct Graph
{
    int **adj_matrix;
    int n, e, k1, k2;
    int *color; // array of size n which has 0 for no org, 1 for drug org1, 2 for org 2.
    bool satisfiable;

    // Graph(int n, int e, int k1, int k2) : n(n), e(e), k1(k1), k2(k2), satisfiable(false)
    // {
    //     adj_matrix = new int *[n];
    //     for (int i = 0; i < n; i++)
    //     {
    //         adj_matrix[i] = new int[n]();
    //     }

    //     color = new int[n]();
    // }
    // ~Graph()
    // {
    //     for (int i = 0; i < n; i++)
    //     {
    //         delete[] adj_matrix[i];
    //     }
    //     delete[] adj_matrix;
    //     delete[] color;
    // }
};

void parse_graph(Graph *G, std::string path, int part);

void output_graph(Graph *G, std::string path, int part);

void print_graph(Graph *G);

void delete_graph(Graph *G);

bool check_connectivity(Graph *G);