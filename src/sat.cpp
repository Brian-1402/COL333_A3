#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// #include "graph.hpp"
#include "sat.hpp"

/*
Variables:
xi, yi; 1<i<=n; represents whether node i is in org or not. x for org1, y for org 2
si_j, ti_j; 1<i<=n, 0 < j < (k1 for s, k2 for t); Represents s_ij according to pdf.

variables in order:
xi -> i; i- 1 to n.
yi -> n+i; i- 1 to n.
si_j -> 2n + k1(i-1) + j; i- 1 to n, j- 1 to k1;
ti_j -> 2n + nk1 + k2(i-1) + j; i- 1 to n, j- 1 to k1;


correction to si_j:
till then, n*px vars covered.
i: 1 to n-1. j: 1 to k.
For atmost k:
si_j -> px*n + k(i-1) + j; i: 1 to n-1, j: 1 to k;
For atleast k,
si_j -> px*n + (n-k0)*(n-1) + (n-k)*(i-1) + j;

*/

// #define x(n, px, i) (std::to_string(n * px + i))
// #define s_atleast(n, px, k0, k, i, j) (std::to_string(px * n + (n - 1) * (n - k0) + (n - k) * (i - 1) + j))
// px means previous count, no. of times x() has been previously used.
// if x, px=0, y- px=1
// k0 corresponds to previous "atleast k0 true" call made.
// If no atleast call was made before, ****consider k0 as n****, just for making that term conveniently zero.
// That does seem equivalent to "atleast n true", but the constraint set is undefined for k=n, so ignore the logical flaw there.
// k corresponds to current "atleast k true" call being made.
// But s here is getting way too much complicated just to avoid 3 separate s definitions, so I prolly won't use this.

// #define x_count(n, px) (std::to_string(n * px))
// #define s(n, px, k0, k, i, j) (std::to_string(px * n + (n - 1) * (n - k0) + k * (n - 1)))

// px means previous count, no. of times x() has been previously used.
// If xi, then px=0; if yi, then px=1.
#define x(n, px, i) (std::to_string(n * px + i))

// #define s1a(n, k, i, j) (std::to_string(2 * n + k * (i - 1) + j))
// #define s1b(n, k0, _k, i, j) (std::to_string(2 * n + (n - 1) * (n - k0) + _k * (i - 1) + j))
#define s1(n, k0, _k, i, j) (std::to_string(2 * n + (n - 1) * (n - k0) + _k * (i - 1) + j))
#define s2(n, _k, i, j) (std::to_string(n + _k * (i - 1) + j))

// IMP: k0 and k are differently defined.
// k0 represents the value used in previous "atleast k0 true" call made.
// If no atleast call was made before, ****consider k0 as n****, just for making that term conveniently zero.
// _k represents value used in current "atleast n - _k true" call being made.
// i.e., if we call "atleast m true", then _k = n-m, and that is handled in the caller function.
// The above namings are implemented to maintain consistency between structure of atmost and atleast functions.

// Only for part 1.
void add_mutually_exclusive_constraint(SAT *S)
{
    int n = S->G->n;
    for (int i = 1; i < n + 1; i++)
    {
        //(¬xi ∨ ¬yj)
        S->clauses.push_back(
            "-" + x(n, 0, i) + " -" + x(n, 1, i));
    }
}

void add_edge_constraints(SAT *S, int part)
{
    Graph *G = S->G;
    int n = G->n;
    // iterating through matrix,
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (G->adj_matrix[i][j] == 0)
            {
                // No edge implies (¬xi ∨ ¬xj), i.e. the 2 nodes cannot be in same org
                //(¬xi ∨ ¬xj)
                S->clauses.push_back(
                    "-" + x(n, 0, i + 1) + " -" + x(n, 0, j + 1));
                if (part == 1)
                {
                    // (¬yi ∨ ¬yj)
                    S->clauses.push_back(
                        "-" + x(n, 1, i + 1) + " -" + x(n, 1, j + 1));
                }
            }
        }
    }
}

void add_atleast_constraint1(SAT *S, int m, int subpart)
{
    int n = S->G->n;
    int k = n - m;

    int px = 0, k0 = n;
    if (subpart == 1)
        px = 0, k0 = n;

    if (subpart == 2)
        px = 1, k0 = S->G->k1;

    // (x1 ∨ s1,1)
    S->clauses.push_back(x(n, px, 1) + " " + s1(n, k0, k, 1, 1));

    for (int j = 2; j <= k; j++)
        // (¬s1,j )
        S->clauses.push_back("-" + s1(n, k0, k, 1, j));

    for (int i = 2; i < n; i++)
    {
        // (xi ∨ si,1)
        S->clauses.push_back(x(n, px, i) + " " + s1(n, k0, k, i, 1));
        // (¬si−1,1 ∨ si,1)
        S->clauses.push_back("-" + s1(n, k0, k, i - 1, 1) + " " + s1(n, k0, k, i, 1));

        for (int j = 2; j <= k; j++)
        {
            // (xi ∨ ¬si−1,j−1 ∨ si,j )
            S->clauses.push_back(x(n, px, i) + " -" + s1(n, k0, k, i - 1, j - 1) + " " + s1(n, k0, k, i, j));
            // (¬si−1,j ∨ si,j )
            S->clauses.push_back("-" + s1(n, k0, k, i - 1, j) + " " + s1(n, k0, k, i, j));
        }
        // (xi ∨ ¬si−1,k)
        S->clauses.push_back(x(n, px, i) + " -" + s1(n, k0, k, i - 1, k));
    }
    // (xn ∨ ¬sn−1,k)
    S->clauses.push_back(x(n, px, n) + " -" + s1(n, k0, k, n - 1, k));
}

void add_atleast_constraint2(SAT *S, int m)
{
    int n = S->G->n;
    int k = n - m;

    int px = 0;

    // (x1 ∨ s1,1)
    S->clauses.push_back(x(n, px, 1) + " " + s2(n, k, 1, 1));

    for (int j = 2; j <= k; j++)
        // (¬s1,j )
        S->clauses.push_back("-" + s2(n, k, 1, j));

    for (int i = 2; i < n; i++)
    {
        // (xi ∨ si,1)
        S->clauses.push_back(x(n, px, i) + " " + s2(n, k, i, 1));
        // (¬si−1,1 ∨ si,1)
        S->clauses.push_back("-" + s2(n, k, i - 1, 1) + " " + s2(n, k, i, 1));

        for (int j = 2; j <= k; j++)
        {
            // (xi ∨ ¬si−1,j−1 ∨ si,j )
            S->clauses.push_back(x(n, px, i) + " -" + s2(n, k, i - 1, j - 1) + " " + s2(n, k, i, j));
            // (¬si−1,j ∨ si,j )
            S->clauses.push_back("-" + s2(n, k, i - 1, j) + " " + s2(n, k, i, j));
        }
        // (xi ∨ ¬si−1,k)
        S->clauses.push_back(x(n, px, i) + " -" + s2(n, k, i - 1, k));
    }
    // (xn ∨ ¬sn−1,k)
    S->clauses.push_back(x(n, px, n) + " -" + s2(n, k, n - 1, k));
}

void to_satinput(SAT *S, std::string path, int part)
{
    std::ofstream f_out{path};
    if (!f_out)
    {
        std::cerr << "Unable to open file" << std::endl;
        return;
    }
    int n = S->G->n;
    // f_out << "p cnf " << 2 * n + n * S->G->k1 + n * S->G->k2 << "\n";
    f_out << "p cnf ";
    if (part == 1)
        f_out << 2 * n + (n - 1) * (n - S->G->k1) + (n - 1) * (n - S->G->k2);
    if (part == 2)
        f_out << n + (n - 1) * (n - S->G->k1);
    f_out << " " << S->clauses.size() << "\n";
    for (std::string c : S->clauses)
    {
        f_out << c << " 0\n";
    }
}

void read_satoutput(SAT *S, std::string path, int part)
{
    std::ifstream f_in{path};
    if (!f_in)
    {
        std::cerr << "Unable to open file" << std::endl;
        return;
    }
    std::string sat;
    std::getline(f_in, sat);
    // std::getline()

    S->G->satisfiable = (sat == "SAT");
    int count = 0;
    for (int i = 0; i < S->G->n; i++)
    {
        int v;
        f_in >> v;
        if ((v > 0) && (count < S->G->k1))
        {
            S->G->color[i] = 1;
            count++;
        }
        else
            S->G->color[i] = 0;
    }
    count = 0;
    if (part == 1)
    {
        for (int i = 0; i < S->G->n; i++)
        {
            int v;
            f_in >> v;
            if ((v > 0) && (count < S->G->k2))
            {
                S->G->color[i] = 2;
                count++;
            }
        }
    }
}

void all_true(SAT *S)
{
    for (int i = 1; i < S->G->n + 1; i++)
    {
        S->clauses.push_back(std::to_string(i));
    }
}

void all_false2(SAT *S)
{
    for (int i = S->G->n + 1; i < 2 * S->G->n + 1; i++)
    {
        S->clauses.push_back("-" + std::to_string(i));
    }
}