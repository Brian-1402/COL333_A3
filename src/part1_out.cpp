#include <iostream>
#include <fstream>
#include <string>

// #include "graph.hpp"
#include "sat.hpp"

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cerr << "Incomplete arguments given" << std::endl;
        return 1;
    }
    std::string sat_out_path = argv[1];
    std::string g_in_path = argv[2];
    std::string g_out_path = argv[3];

    Graph *G;
    G = new Graph;

    parse_graph(G, g_in_path, 1);
    // print_graph(G);
    SAT *S;
    S = new SAT;
    S->G = G;
    read_satoutput(S, sat_out_path, 1);
    output_graph(G, g_out_path, 1);
    delete_graph(G);
    // delete G;
    return 0;
}