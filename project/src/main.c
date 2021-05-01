#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(void) {
    Matrix* matrix1 = create_matrix_from_file("file.txt");
    check_matrix(matrix1);
    Matrix* matrix2 = create_matrix(3, 3);
    check_matrix(matrix2);

    size_t rows = 0, cols = 0;
    get_rows(matrix1, &rows);
    get_cols(matrix1, &cols);

    double value = 0;
    get_elem(matrix1, 1, 1, &value);
    set_elem(matrix2, 1, 1, value);

    Matrix* matrix3 = sum(matrix1, matrix2);
    check_matrix(matrix3);
    free_matrix(matrix3);

    matrix3 = sub(matrix1, matrix2);
    free_matrix(matrix3);

    matrix3 = mul(matrix2, matrix1);
    free_matrix(matrix3);

    matrix3 = mul_scalar(matrix1, 3);
    free_matrix(matrix3);

    matrix3 = transp(matrix1);
    free_matrix(matrix3);

    double determ = 0;
    det(matrix1, &determ);

    matrix3 = adj(matrix1);
    free_matrix(matrix3);

    matrix3 = inv(matrix1);

    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(matrix3);
    return 0;
}

