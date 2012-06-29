#include "lpsolver.hpp"

Minilp::Minilp(MinimipModel *model) {
    //logger = std::cout;
    Minilp::model = model;
    row_vars = new int[model->nrows];
    theta = new double[model->nrows];
}

void Minilp::printTableaux(char* str) {
    printf("#####TABLEAUX: %s####\n", str);
    for (int c = 0; c < model->ncols; c++)
        printf("\t%lf x%d", model->Z[c], c);
    printf("\n");
    for (int r = 0; r < model->nrows; r++) {
        printf("%d\t", row_vars[r]);
        for (int c = 0; c < model->ncols; c++)
            printf(" %lf x%d\t", (*model->rows[r])[c], c);
        printf(" %lf\t%lf\n", model->rhs[r], theta[r]);
    }
    for (int c = 0; c < model->ncols; c++)
        printf("\t%lf", cmz[c]);
    printf("\n");
}

int Minilp::simplex() {
    int pivot_variable = 0;
    int pivot_row = 0;
    double pivot_element;

    for (int r = 0; r < model->nrows; r++) {
    	if(model->rhs[r] < 0.0)
    		return 0;
        for (int c = model->ncols - model->nrows; c < model->ncols; c++)
            if (model->rows[r]->find(c) != model->rows[r]->end()
                    && (*model->rows[r])[c] == 1.0)
                row_vars[r] = c;
    }

    while (1) {
        pivot_variable = 0;
        pivot_row = 0;

        /*
         * Calculate the C - Z vector, the pivot variable is the j with maximum
         * Cj - Zj.
         */
        for (int c = 0; c < model->ncols; c++) {
            double sum = 0.0;
            for (int r = 0; r < model->nrows; r++) {
                sum += model->Z[row_vars[r]] * (*model->rows[r])[c];
            }
            cmz[c] = model->Z[c] - sum;
            if (cmz[c] > cmz[pivot_variable])
                pivot_variable = c;
        }

        /*
         * When the pivot variable (max Cj-Zj) is 0 or negative we have found
         * our solution
         */
        if (cmz[pivot_variable] <= 0.0) {
            for (int r = 0; r < model->nrows; r++)
                solution[row_vars[r]] = model->rhs[r];
            return 1;
        }

        /*
         * Calculate the theta vector, the result of moving the coefficient for
         * the pivot variable in a row to the right hand side.
         */
        for (int r = 0; r < model->nrows; r++) {
            if ((*model->rows[r])[pivot_variable] > 0) {
                theta[r] = model->rhs[r] / (*model->rows[r])[pivot_variable];
                if (theta[r] < theta[pivot_row])
                    pivot_row = r;
            }
        }

        /*
         * Update which variable represents the pivot row and divide the
         * pivot row by the pivot element. The pivot element should go to
         * 1.0.
         */
        row_vars[pivot_row] = pivot_variable;
        pivot_element = (*model->rows[pivot_row])[pivot_variable];
        for (int c = 0; c < model->ncols; c++)
            (*model->rows[pivot_row])[c] /= pivot_element;
        model->rhs[pivot_row] /= pivot_element;

        /*
         * Update the rest of the coefficients. Since the pivot element is 1.0
         * the rest of the coefficients for the pivot variable must be set to
         * 0.0. To do this we mulitply the pivot row by the coefficient of the
         * pivot variable in a non pivot row and then subtract the row from the
         * pivot row.
         */
        for (int r = 0; r < model->nrows; r++) {
            double coef = (*model->rows[r])[pivot_variable];
            if (r != pivot_row) {
                for (int c = 0; c < model->ncols; c++)
                    (*model->rows[r])[c] -= coef * (*model->rows[pivot_row])[c];
                model->rhs[r] -= coef * model->rhs[pivot_row];
            }
        }
    }
}

void Minilp::printSolution() {
    double sum = 0.0;
    for (int c = 0; c < model->ncols - model->nrows; c++) {
        sum += model->Z[c] * solution[c];
        printf("x%d: %lf\n", c, solution[c]);
    }
    printf("Z: %lf\n", sum);
}

