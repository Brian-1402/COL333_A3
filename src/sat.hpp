#include <string>
#include <vector>

#include "graph.hpp"

struct SAT
{
    Graph *G;
    std::vector<std::string> clauses;
};

void add_mutually_exclusive_constraint(SAT *S);
void add_edge_constraints(SAT *S, int part);
void add_atleast_constraint1(SAT *S, int m, int subpart);
void add_atleast_constraint2(SAT *S, int m);

void to_satinput(SAT *S, std::string path, int part);
void read_satoutput(SAT *S, std::string path, int part);

void all_true(SAT *S);
void all_false2(SAT *S);