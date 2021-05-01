#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stddef.h>

#define ROWS_AND_COLS_ERROR 1
#define ROWS_AND_COLS 2
#define MATRIX_ERROR 3
#define NOT_SQUARE_MATRIX 4
#define VALUE_ERROR 5
#define MATRIX_LIMIT_ERROR 6

typedef struct Matrix {
    size_t cols;
    size_t rows;
    double* mvalues;
} Matrix;

int check_rowsncols(size_t* rows_or_cols);

int check_limit(const Matrix* matrix, size_t row, size_t col);

int check_matrix(const Matrix* matrix);

int check_value(double* value);

// Init/release operations
Matrix* create_matrix_from_file(const char* path_file);

Matrix* create_matrix(size_t rows, size_t cols);

int free_matrix(Matrix* matrix);

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows);

int get_cols(const Matrix* matrix, size_t* cols);

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val);

int set_elem(Matrix* matrix, size_t row, size_t col, double val);

// Math operations
Matrix* mul_scalar(const Matrix* matrix, double val);

Matrix* transp(const Matrix* matrix);

Matrix* sum(const Matrix* l, const Matrix* r);

Matrix* sub(const Matrix* l, const Matrix* r);

Matrix* mul(const Matrix* l, const Matrix* r);

// Extra operations
int det(const Matrix* matrix, double* val);

Matrix* adj(const Matrix* matrix);

Matrix* inv(const Matrix* matrix);

#endif  // PROJECT_INCLUDE_MATRIX_H_

