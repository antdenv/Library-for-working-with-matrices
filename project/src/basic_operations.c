#include "matrix.h"

int get_rows(const Matrix* matrix, size_t* rows) {
    check_matrix(matrix);
    check_rowsncols(rows);
    *rows = matrix->rows;

    return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    check_matrix(matrix);
    check_rowsncols(cols);

    *cols = matrix->cols;

    return 0;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    check_matrix(matrix);
    check_limit(matrix, row, col);
    check_value(val);

    *val = matrix->mvalues[row * matrix->cols + col];

    return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    check_limit(matrix, row, col);

    matrix->mvalues[row * matrix->cols + col] = val;

    return 0;
}
