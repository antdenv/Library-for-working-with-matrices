#include "matrix.h"
#include <math.h>
#include <stdlib.h>

Matrix* mul_scalar(const Matrix* matrix, double val) {
    if (matrix == NULL) {
        return NULL;
    }

    Matrix* mul_matrix = create_matrix(matrix->rows, matrix->cols);
    if (mul_matrix == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < mul_matrix->rows; ++i) {
        for (size_t j = 0; j < mul_matrix->cols; ++j) {
            mul_matrix->mvalues[i * mul_matrix->cols + j] = matrix->mvalues[i * matrix->cols
                                                                            + j] * val;
        }
    }

    return mul_matrix;
}

Matrix* transp(const Matrix* matrix) {
    if (matrix == NULL) {
        return NULL;
    }


    Matrix* transp_matrix = create_matrix(matrix->cols, matrix->rows);
    if (transp_matrix == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < transp_matrix->rows; ++i) {
        for (size_t j = 0; j < transp_matrix->cols; ++j) {
            transp_matrix->mvalues[i * transp_matrix->cols + j] = matrix->mvalues[j *
                                                                                  matrix->cols + i];
        }
    }

    return transp_matrix;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    if (l == NULL || r == NULL || l->rows != r->rows || l->cols != r->cols) {
        return NULL;
    }


    Matrix* sum_matrix = create_matrix(l->rows, l->cols);
    if (sum_matrix == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < sum_matrix->rows; ++i) {
        for (size_t j = 0; j < sum_matrix->cols; ++j) {
            sum_matrix->mvalues[i * sum_matrix->cols + j] = l->mvalues[i *
                                                                       sum_matrix->cols + j] +
                                                            r->mvalues[i * sum_matrix->cols + j];
        }
    }

    return sum_matrix;
}

Matrix* sub(const Matrix* l, const Matrix* r) {
    if (l == NULL || r == NULL || l->rows != r->rows || l->cols != r->cols) {
        return NULL;
    }

    Matrix* sub_matrix = create_matrix(l->rows, l->cols);
    if (sub_matrix == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < sub_matrix->rows; ++i) {
        for (size_t j = 0; j < sub_matrix->cols; ++j) {
            sub_matrix->mvalues[i * sub_matrix->cols + j] = l->mvalues[i *
                                                                       sub_matrix->cols + j] -
                                                            r->mvalues[i * sub_matrix->cols + j];
        }
    }

    return sub_matrix;
}

static double* get_row(const Matrix* matrix, size_t row, size_t cols) {
    double* row_l = calloc(cols, sizeof(double));

    if (row_l == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < cols; ++i) {
        row_l[i] = matrix->mvalues[row * cols + i];
    }

    return row_l;
}

static double* get_col(const Matrix* matrix, size_t col, size_t rows, size_t cols) {
    double* column = calloc(rows, sizeof(double));

    if (column == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < rows; ++i) {
        column[i] = matrix->mvalues[i * cols + col];
    }

    return column;
}

static double row_and_col_scalar(double* row, double* col, size_t col_and_row_size) {
    double res = 0;
    for (size_t i = 0; i < col_and_row_size; ++i) {
        res += (row[i] * col[i]);
    }

    return res;
}

Matrix* mul(const Matrix* l, const Matrix* r) {
    if (l == NULL || r == NULL || l->cols != r->rows) {
        return NULL;
    }

    Matrix* mul_matrix = create_matrix(l->rows, r->cols);
    if (mul_matrix == NULL) {
        return NULL;
    }

    double* row = NULL;
    double* col = NULL;

    for (size_t i = 0; i < mul_matrix->rows; ++i) {
        for (size_t j = 0; j < mul_matrix->cols; ++j) {
            row = get_row(l, i, l->cols);
            if (row == NULL) {
                return NULL;
            }
            col = get_col(r, j, r->rows, r->cols);
            if (col == NULL) {
                free(row);
                return NULL;
            }
            mul_matrix->mvalues[i * mul_matrix->cols + j] = row_and_col_scalar(row, col, l->cols);
            free(row);
            free(col);
        }
    }

    return mul_matrix;
}

