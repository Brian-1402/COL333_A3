#include <iostream>
#include <fstream>
#include <string>

// #include "graph.hpp"
#include "sat.hpp"

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        std::cerr << "Incomplete arguments given" << std::endl;
        return 1;
    }
    std::string g_in_path = argv[1];
    std::string sat_in_path = argv[2];
    std::string sat_out_path = argv[3];
    std::string g_out_path = argv[4];

    // cout << in_path << out_path << endl;
    Graph *G;
    G = new Graph;

    // Graph *G = new Graph(0, 0, 0, false);

    parse_graph(G, g_in_path, 2);
    // print_graph(G);
    SAT *S;
    S = new SAT;
    S->G = G;

    int K = (G->n + 1) / 2;
    G->k1 = K;
    int left = 1;
    int right = G->n;
    while (left <= right)
    {
        S->clauses.clear();
        // std::cout << "k: " << K << "\n";
        // std::cout << "left: " << left << "\n";
        // std::cout << "right" << right << "\n";
        G->k1 = K;
        if (K < G->n)
        {
            add_edge_constraints(S, 2);
            add_atleast_constraint2(S, K);
            to_satinput(S, sat_in_path, 2);
        }
        if (K == G->n)
        {
            // run check to see if all are connected,
            // if yes, run minisat for all variables true
            // else, break. we have already satisfied n-1 connected.
            if (check_connectivity(G))
            {
                std::cout << "full\n";
                all_true(S);
                to_satinput(S, sat_in_path, 2);
            }
            else
                break;
        }

        std::string minisat_cmd = "./minisat " + sat_in_path + " " + sat_out_path;
        int c = system(minisat_cmd.c_str());
        if (c != 0)
        {
            // std::cout << "\nExited. Code " << c << std::endl;
        }

        read_satoutput(S, sat_out_path, 2);
        if (!G->satisfiable)
        {
            right = K - 1;
        }
        else
        {
            left = K + 1;
            output_graph(G, g_out_path, 2);
        }
        K = (right + left) / 2;
    }
    G->k1 = K;
    // output_graph(G, g_out_path, 2);

    delete_graph(G);
    return 0;
}