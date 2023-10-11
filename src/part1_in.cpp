#include <iostream>
#include <fstream>
#include <string>

// #include "graph.hpp"
#include "sat.hpp"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Incomplete arguments given" << std::endl;
        return 1;
    }
    std::string g_in_path = argv[1];
    std::string sat_in_path = argv[2];
    // cout << in_path << out_path << endl;
    Graph *G;
    G = new Graph;

    // Graph *G = new Graph(0, 0, 0, false);

    parse_graph(G, g_in_path, 1);
    // print_graph(G);
    SAT *S;
    S = new SAT;
    S->G = G;

    if (G->k1 == G->n)
    {
        if (check_connectivity(G))
        {
            all_true(S);
            all_false2(S);
        }
        else
        {
            S->clauses.push_back("-1");
            S->clauses.push_back("1");
        }
        to_satinput(S, sat_in_path, 1);
        delete_graph(G);
        return 0;
    }
    add_mutually_exclusive_constraint(S);
    add_edge_constraints(S, 1);
    add_atleast_constraint1(S, G->k1, 1);
    add_atleast_constraint1(S, G->k2, 2);

    to_satinput(S, sat_in_path, 1);
    delete_graph(G);
    // delete G;
    return 0;
}