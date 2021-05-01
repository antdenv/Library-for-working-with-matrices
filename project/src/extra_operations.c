#include "matrix.h"
#include <math.h>

static Matrix* set_additional_minor(const Matrix* matrix, size_t col, size_t row) {
    if (matrix == NULL || matrix->mvalues == NULL) {
        return NULL;
    }

    Matrix* help_matrix = create_matrix(matrix->rows - 1, matrix->cols - 1);
    if (help_matrix == NULL) {
        return NULL;
    }

    double value = 0;
    int matr_i = 0;
    int matr_j = 0;
    for (size_t i = 0; i < matrix->rows; ++i) {
        if (i == row) {
            continue;
        } else {
            for (size_t j = 0; j < matrix->cols; ++j) {
                if (j == col) {
                    continue;
                } else {
                    get_elem(matrix, i, j, &value);
                    set_elem(help_matrix, matr_i, matr_j, value);
                    ++matr_j;
                }
            }
            matr_j = 0;
            ++matr_i;
        }
    }
    return help_matrix;
}

static double get_determinant(const Matrix* matrix) {
    if (matrix == NULL || matrix->mvalues == NULL) {
        return MATRIX_ERROR;
    }

    double value = 1;
    if (matrix->cols == 1) {
        return *(matrix->mvalues);
    }

    if (matrix->cols == 2) {
        return matrix->mvalues[0] * matrix->mvalues[3] - matrix->mvalues[1] * matrix->mvalues[2];
    } else {
        double determ = 0.0;
        for (size_t j = 0; j < matrix->cols; ++j) {
            Matrix* minor_matrix = set_additional_minor(matrix, j, 0);

            determ += *(matrix->mvalues + j) * get_determinant(minor_matrix) * value;
            value *= -1;

            free_matrix(minor_matrix);
        }
        return determ;
    }
}

int det(const Matrix* matrix, double* val) {
    if (matrix == NULL || matrix->mvalues == NULL) {
        return MATRIX_ERROR;
    }

    if (val == NULL) {
        return VALUE_ERROR;
    }

    if (matrix->cols != matrix->rows) {
        return NOT_SQUARE_MATRIX;
    }

    *val = get_determinant(matrix);
    return 0;
}

Matrix* adj(const Matrix* matrix) {
    if (matrix == NULL || matrix->mvalues == NULL || matrix->cols != matrix->rows) {
        return NULL;
    }

    Matrix* transp_matr = transp(matrix);
    Matrix* help_matrix = create_matrix(matrix->rows, matrix->cols);

    double value = -1;
    for (size_t i = 0; i < matrix->rows; ++i) {
        for (size_t j = 0; j < matrix->cols; ++j) {
            Matrix* minor_matrix = set_additional_minor(transp_matr, j, i);
            set_elem(help_matrix, i, j, pow(value, i + j) * get_determinant(minor_matrix));
            free_matrix(minor_matrix);
        }
    }

    free_matrix(transp_matr);
    return help_matrix;
}

Matrix* inv(const Matrix* matrix) {
    if (matrix == NULL || matrix->mvalues == NULL || matrix->cols != matrix->rows) {
        return NULL;
    }

    double d = 0;
    if (det(matrix, &d) != 0) {
        return NULL;
    }

    if (matrix->rows == 1) {
        Matrix* help_matrix = create_matrix(matrix->rows, matrix->cols);
        if (help_matrix == NULL) {
            return NULL;
        }
        set_elem(help_matrix, 0, 0, 1.0 / d);
        return help_matrix;
    }

    Matrix* adj_matrix = adj(matrix);
    Matrix* mul_matrix = mul_scalar(adj_matrix, 1.0 / d);

    free_matrix(adj_matrix);
    return mul_matrix;
}
