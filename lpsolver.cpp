#include <cstdio>
#include <cstdlib>

void printTableaux(double** rows, double* rhs, double* Z,
                   unsigned int nrows, unsigned int ncols,
                   double* cmz, double* theta, int* row_vars){
    printf("#####TABLEAUX####\n");
    for(unsigned int c=0;c<ncols;c++) printf("\t%lf x%d", Z[c], c);
    printf("\n");
    for(unsigned int r=0;r<nrows;r++) {
        printf("%d\t", row_vars[r]);
        for(unsigned int c=0; c<ncols; c++) printf(" %lf x%d\t", rows[r][c], c);
        printf(" %lf\t%lf\n", rhs[r], theta[r]);
    }
    for(unsigned int c=0;c<ncols;c++) printf("\t%lf", cmz[c]);
    printf("\n");
}

double* simplex(double** rows, double* rhs, double* Z,
                     unsigned int nrows, unsigned int ncols){
    double* cmz = new double[ncols];
    double* theta = new double[nrows];
    int* row_vars = new int[nrows];
    unsigned int pivot_variable = 0;
    unsigned int pivot_row = 0;
    double pivot_element;

    for(unsigned int r=0; r<nrows; r++)
        for(unsigned int c=ncols-nrows; c<ncols; c++) 
            if(rows[r][c] == 1.0) row_vars[r] = c;

    while(1) {

        pivot_variable = 0;
        pivot_row = 0;

        for(unsigned int c=0; c<ncols; c++) {
            double sum = 0.0;
            for(unsigned int r=0; r<nrows; r++) {
                sum += Z[row_vars[r]] * rows[r][c];
            }
            cmz[c] = Z[c] - sum;
            if(cmz[c] > cmz[pivot_variable]) pivot_variable = c;
        }

        if(cmz[pivot_variable] <= 0.0) {
            double* solution = new double[ncols];
            for(unsigned int r=0; r<nrows; r++)
                solution[row_vars[r]] = rhs[r];
            return solution;
        }

        for(unsigned int r=0; r<nrows; r++) {
            if(rows[r][pivot_variable] > 0) {
                theta[r] = rhs[r] / rows[r][pivot_variable];
                if(theta[r] < theta[pivot_row]) pivot_row = r;
            }
        }

#ifdef PRINTTABLEAUX
        printTableaux(rows, rhs, Z, nrows, ncols, cmz, theta, row_vars);
#endif
        
        row_vars[pivot_row] = pivot_variable;
        pivot_element = rows[pivot_row][pivot_variable];
        for(unsigned int c=0; c<ncols; c++) rows[pivot_row][c] /= pivot_element;
        rhs[pivot_row] /= pivot_element;

        for(unsigned int r=0; r<nrows; r++) {
            double coef = rows[r][pivot_variable];
            if(r != pivot_row) {
                for(unsigned int c=0; c<ncols; c++) rows[r][c] -= coef*rows[pivot_row][c];
                rhs[r] -= coef * rhs[pivot_row];
            }
        }

    }
}

void printSolution(double* solution, double* Z, int ncols, int nrows) {
    double sum = 0.0;
    for(unsigned int c=0; c<ncols-nrows; c++) {
        sum += Z[c]*solution[c];
        printf("x%d: %lf\n", c, solution[c]);
    }
    printf("Z: %lf\n", sum);
}

