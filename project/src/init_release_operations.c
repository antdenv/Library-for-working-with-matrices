#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int check_matrix(const Matrix* matrix) {
    if (matrix == NULL) {
        return MATRIX_ERROR;
    }

    return 0;
}

int check_rowsncols(size_t* rows_or_cols) {
    if (rows_or_cols == NULL) {
        return ROWS_AND_COLS_ERROR;
    }

    return 0;
}

int check_limit(const Matrix* matrix, size_t row, size_t col) {
    if (row > matrix->rows || col > matrix->cols) {
        return MATRIX_LIMIT_ERROR;
    }

    return 0;
}

int check_value(double* value) {
    if (value == NULL) {
        return VALUE_ERROR;
    }

    return 0;
}

Matrix* create_matrix(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        return NULL;
    }

    Matrix* matrix = calloc(1, sizeof(Matrix));
    if (matrix == NULL) {
        return NULL;
    }

    matrix->cols = cols;
    matrix->rows = rows;
    matrix->mvalues = calloc(matrix->rows * matrix->cols, sizeof(double));

    if (matrix->mvalues == NULL) {
        free(matrix);
        return NULL;
    }

    return matrix;
}

Matrix* create_matrix_from_file(const char* path_file) {
    FILE* file = fopen(path_file, "r");

    if (file == NULL) {
        return NULL;
    }

    size_t rows = 0;
    size_t cols = 0;
    if (fscanf(file, "%zu %zu", &rows, &cols) != ROWS_AND_COLS) {
        fclose(file);
        return NULL;
    }

    if (rows < 1 || cols < 1) {
        fclose(file);
        return NULL;
    }

    Matrix* matrix = create_matrix(rows, cols);
    if (matrix == NULL) {
        fclose(file);
        return NULL;
    }

    for (size_t i = 0; i < matrix->rows; ++i) {
        for (size_t j = 0; j < matrix->cols; ++j) {
            if (fscanf(file, "%lf", &matrix->mvalues[i * matrix->cols + j]) != 1) {
                fclose(file);
                free_matrix(matrix);
                return NULL;
            }
        }
    }

    fclose(file);

    return matrix;
}

int free_matrix(Matrix* matrix) {
    if (matrix == NULL) {
        return MATRIX_ERROR;
    }

    free(matrix->mvalues);
    free(matrix);

    return 0;
}
