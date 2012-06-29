#include <cstdio>
#include <cstdlib>
#include "lpsolver.hpp"

void modelOne() {
    const char* model = "/*\n\
 * Maximise: 6*x0 + 5*x1\n\
 * s.t.:       x0 +   x1 <  5\n\
 *           3*x0 + 2*x1 < 12\n\
 */\n";

    MinimipModel model_1;

    model_1.ncols = 4;
    model_1.nrows = 2;

    double rows[2][4] = {{1.0, 1.0, 1.0, 0.0},
                         {3.0, 2.0, 0.0, 1.0}};
    double rhs[2] = {5.0, 12.0};
    double Z[4] = {6.0, 5.0, 0.0, 0.0};

    for(int r=0; r<model_1.nrows; r++) {
        model_1.rhs[r] = rhs[r];
        model_1.rows.push_back(new std::map<int, double>);
        for(int c=0; c<model_1.ncols; c++)
            model_1.rows[r]->insert(std::pair<int,double>(c, rows[r][c]));
    }

    for(int c=0; c<model_1.ncols; c++)
        model_1.Z[c] = Z[c];

    printf("%s\n", model);

    Minilp *lpsolver = new Minilp(&model_1);

    lpsolver->simplex();
    lpsolver->printSolution();
}


void modelTwo() {
    const char* model="/*\n\
 * Maximise: 6*x0 + 8*x1\n\
 * s.t.:       x0 +   x1 < 10\n\
 *           2*x0 + 3*x1 < 25\n\
 *             x0 + 5*x1 < 35\n\
 */\n";
    MinimipModel model_1;

    model_1.ncols = 5;
    model_1.nrows = 3;

    double rows[3][5] = {{1.0, 1.0, 1.0, 0.0, 0.0},
                         {2.0, 3.0, 0.0, 1.0, 0.0},
                         {1.0, 5.0, 0.0, 0.0, 1.0}};
    double rhs[3] = {10.0, 25.0, 35.0};
    double Z[5] = {6.0, 8.0, 0.0, 0.0, 0.0};

    for(int r=0; r<model_1.nrows; r++) {
        model_1.rhs[r] = rhs[r];
        model_1.rows.push_back(new std::map<int, double>);
        for(int c=0; c<model_1.ncols; c++)
            model_1.rows[r]->insert(std::pair<int,double>(c, rows[r][c]));
    }

    for(int c=0; c<model_1.ncols; c++)
        model_1.Z[c] = Z[c];

    printf("%s\n", model);

    Minilp *lpsolver = new Minilp(&model_1);

    lpsolver->simplex();
    lpsolver->printSolution();
}

int main(int argc, char**argv) {
    modelOne();
    modelTwo();

    return EXIT_SUCCESS;
}
