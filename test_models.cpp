#include <cstdio>
#include <cstdlib>
#include "lpsolver.hpp"

void modelOne() {
    const char* model = "/*\n\
 * Maximise: 6*x0 + 5*x1\n\
 * s.t.:       x0 +   x1 <  5\n\
 *           3*x0 + 2*x1 < 12\n\
 * Solution  6* 2 + 5* 3 = 27\n\
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
 * Solution  6* 5 + 8* 5 = 70\n\
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

void modelThree() {
    const char* model="/*\n\
 * Maximise: 60*x0 +  30*x1 +  20*x2\n\
 * s.t.:      2*x0 + 1.5*x1 + 0.5*x2 <= 8\n\
 *            8*x0 +   6*x1 +     x2 <= 48\n\
 *            4*x0 +   2*x1 + 1.5*x2 <= 20\n\
 *                       x1          <= 5\n\
 * Solution  60* 2 +  30* 0 +  20* 8 = 280\n\
 */\n";

    MinimipModel model_1;

    model_1.ncols = 7;
    model_1.nrows = 4;

    double rows[4][7] = {{2.0, 1.5, 0.5, 1, 0, 0, 0},
                         {8.0, 6.0, 1.0, 0, 1, 0, 0},
                         {4.0, 2.0, 1.5, 0, 0, 1, 0},
    					 {0.0, 1.0, 0.0, 0, 0, 0, 1}};
    double rhs[4] = {8.0, 48.0, 20.0, 5.0};
    double Z[7] = {60.0, 30.0, 20.0, 0, 0, 0, 0};

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
    modelThree();

    return EXIT_SUCCESS;
}
