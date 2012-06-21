
void printTableaux(double** rows, double* rhs, double* Z,
                   unsigned int nrows, unsigned int ncols,
                   double* cmz, double* theta, int* row_vars);

double* simplex(double** rows, double* rhs, double* Z,
                     unsigned int nrows, unsigned int ncols);

void printSolution(double* solution, double* Z, int ncols, int nrows);
