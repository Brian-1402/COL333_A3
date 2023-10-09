#include <iostream>
#include <fstream>
#include <string>

#include "parser.hpp"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Incomplete arguments given" << std::endl;
        return 1;
    }
    std::string in_path = argv[1];
    std::string out_path = argv[2];
    // cout << in_path << out_path << endl;
    Graph *G;
    G = new Graph;
    parse_graph(G, in_path, 1);
    print_graph(G);
    delete_graph(G);
    return 0;
}