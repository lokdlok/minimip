#include <cstdio>
#include <cstdlib>
#include "lpsolver.hpp"

void modelOne() {
    const char* model = "/*\n\
 * Maximise: 6*x0 + 5*x1\n\
 * s.t.:       x0 +   x1 <  5\n\
 *           3*x0 + 2*x1 < 12\n\
 */\n";
    int ncols = 4;
    int nrows = 2;
    double** rows = new double*[nrows];
    double* rhs = new double[nrows];
    double* Z = new double[ncols];
    rows[0] = new double[ncols]; rows[1] = new double[ncols];
    rows[0][0] = 1.0; rows[0][1] = 1.0; rows[0][2] = 1.0; rows[0][3] = 0.0;
    rows[1][0] = 3.0; rows[1][1] = 2.0; rows[1][2] = 0.0; rows[1][3] = 1.0;

    rhs[0] = 5; rhs[1] = 12;
    Z[0] = 6.0; Z[1] = 5.0; Z[2] = 0.0; Z[3] = 0.0;
    printf("%s\n", model);
    printSolution(simplex(rows, rhs, Z, nrows, ncols), Z, ncols, nrows);
}

void modelTwo() {
    const char* model="/*\n\
 * Maximise: 6*x0 + 8*x1\n\
 * s.t.:       x0 +   x1 < 10\n\
 *           2*x0 + 3*x1 < 25\n\
 *             x0 + 5*x1 < 35\n\
 */\n";
    int ncols = 5;
    int nrows = 3;
    double** rows = new double*[nrows];
    double* rhs = new double[nrows];
    double* Z = new double[ncols];
    rows[0] = new double[ncols]; rows[1] = new double[ncols];
    rows[2] = new double[ncols];

    rows[0][0] = 1.0; rows[0][1] = 1.0; rows[0][2] = 1.0; rows[0][3] = 0.0; rows[0][4] = 0.0;
    rows[1][0] = 2.0; rows[1][1] = 3.0; rows[1][2] = 0.0; rows[1][3] = 1.0; rows[1][4] = 0.0;
    rows[2][0] = 1.0; rows[2][1] = 5.0; rows[2][2] = 0.0; rows[2][3] = 0.0; rows[2][4] = 1.0;

    rhs[0] = 10.0; rhs[1] = 25.0; rhs[2] = 35.0;
    Z[0] = 6.0; Z[1] = 8.0; Z[2] = 0.0; Z[3] = 0.0; Z[4] = 0.0;

    printf("%s\n", model);
    printSolution(simplex(rows, rhs, Z, nrows, ncols), Z, ncols, nrows);
}

int main(int argc, char**argv) {
    modelOne();
    modelTwo();
    
    return EXIT_SUCCESS;
}
