#include "matrix.h"
#include <cmath>
#include <iomanip>
#include <limits>
#include "exceptions.h"

#define EXPONENT 1.0e-7

namespace prep {
    Matrix::Matrix(size_t rows, size_t cols): matrix_rows(rows), matrix_cols(cols) {
        matrix.resize(rows);
        for (size_t i = 0; i < rows; ++i) {
            matrix[i].resize(cols);
        }
    }

    Matrix::Matrix(std::istream& is) {
        if (is.fail()) {
            throw InvalidMatrixStream();
        }

        is >> matrix_rows >> matrix_cols;

        if (is.fail()) {
            throw InvalidMatrixStream();
        }

        matrix.resize(matrix_rows);
        for (size_t i = 0; i < matrix_rows; ++i) {
            matrix[i].resize(matrix_cols);
        }

        for (size_t i = 0; i < matrix_rows; ++i) {
            for (size_t j = 0; j < matrix_cols; ++j) {
                is >> matrix[i][j];
                if (is.fail()) {
                    throw InvalidMatrixStream();
                }
            }
        }
    }

    size_t Matrix::getRows() const {
        return matrix_rows;
    }

    size_t Matrix::getCols() const {
        return matrix_cols;
    }

    double Matrix::operator()(size_t i, size_t j) const {
        if (i >= matrix_rows || j >= matrix_cols) {
            throw OutOfRange(i, j, *this);
        }
        return matrix[i][j];
    }

    double& Matrix::operator()(size_t i, size_t j) {
        if (i >= matrix_rows || j >= matrix_cols) {
            throw OutOfRange(i, j, *this);
        }
        return matrix[i][j];
    }

    bool Matrix::operator==(const Matrix& rhs) const {
        if (matrix_rows != rhs.matrix_rows || matrix_cols != rhs.matrix_cols) {
            return false;
        }

        for (size_t i = 0; i < matrix_rows; ++i) {
            for (size_t j = 0; j < matrix_cols; ++j) {
                if (std::abs(matrix[i][j] - rhs.matrix[i][j]) > EXPONENT) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Matrix::operator!=(const Matrix& rhs) const {
        if (matrix_rows != rhs.matrix_rows || matrix_cols != rhs.matrix_cols) {
            return true;
        }

        for (size_t i = 0; i < matrix_rows; ++i) {
            for (size_t j = 0; j < matrix_cols; ++j) {
                if (std::abs(matrix[i][j] - rhs.matrix[i][j]) > EXPONENT) {
                    return true;
                }
            }
        }
        return false;
    }

    Matrix Matrix::operator+(const Matrix& rhs) const {
        if (matrix_rows != rhs.matrix_rows || matrix_cols != rhs.matrix_cols) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix sum_matrix = Matrix(matrix_rows, matrix_cols);

        for (size_t i = 0; i < matrix_rows; ++i) {
            for (size_t j = 0; j < matrix_cols; ++j) {
                sum_matrix.matrix[i][j] = matrix[i][j] + rhs.matrix[i][j];
            }
        }
        return sum_matrix;
    }

    Matrix Matrix::operator-(const Matrix& rhs) const {
        if (matrix_rows != rhs.matrix_rows || matrix_cols != rhs.matrix_cols) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix sub_matrix = Matrix(matrix_rows, matrix_cols);

        for (size_t i = 0; i < matrix_rows; ++i) {
            for (size_t j = 0; j < matrix_cols; ++j) {
                sub_matrix.matrix[i][j] = matrix[i][j] - rhs.matrix[i][j];
            }
        }
        return sub_matrix;
    }

    Matrix Matrix::operator*(const Matrix& rhs) const {
        if (matrix_cols != rhs.matrix_rows) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix result_matrix = Matrix(matrix_rows, rhs.matrix_cols);

        for (size_t i = 0; i < matrix_rows; ++i) {
            for (size_t j = 0; j < rhs.matrix_cols; ++j) {
                for (size_t k = 0; k < matrix_cols; ++k) {
                    result_matrix.matrix[i][j] += matrix[i][k] * rhs.matrix[k][j];
                }
            }
        }
        return result_matrix;
    }

    Matrix Matrix::operator*(double val) const {
        Matrix result_matrix = Matrix(matrix_rows, matrix_cols);

        for (size_t i = 0; i < matrix_rows; ++i) {
            for (size_t j = 0; j < matrix_cols; ++j) {
                result_matrix.matrix[i][j] = matrix[i][j] * val;
            }
        }
        return result_matrix;
    }

    Matrix operator*(double val, const Matrix& matrix) {
        Matrix result_matrix = Matrix(matrix.matrix_rows, matrix.matrix_cols);

        for (size_t i = 0; i < matrix.matrix_rows; ++i) {
            for (size_t j = 0; j < matrix.matrix_cols; ++j) {
                result_matrix.matrix[i][j] = matrix.matrix[i][j] * val;
            }
        }
        return result_matrix;
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        os << matrix.matrix_rows << " " << matrix.matrix_cols << std:: endl;

        for (size_t i = 0; i < matrix.matrix_rows; ++i) {
            for (size_t j = 0; j < matrix.matrix_cols; ++j) {
                os << std::setprecision(std::numeric_limits<double>::max_digits10)
                << matrix.matrix[i][j] << ' ';
            }
            os << std::endl;
        }
        return os;
    }

    Matrix Matrix::transp() const {
        Matrix transp_matrix = Matrix(matrix_cols, matrix_rows);

        for (size_t i = 0; i < transp_matrix.matrix_rows; ++i) {
            for (size_t j = 0; j < transp_matrix.matrix_cols; ++j) {
                transp_matrix.matrix[i][j] = matrix[j][i];
            }
        }
        return transp_matrix;
    }

    Matrix Matrix::set_additional_minor(const Matrix& matrix, size_t rows, size_t cols) const {
        Matrix minor_matrix(matrix.getRows() - 1, matrix.getCols() - 1);
        size_t matrix_i = 0;
        size_t matrix_j = 0;

        for (size_t i = 0; i < matrix.getRows(); ++i) {
            if (i == rows) {
                continue;
            }
            for (size_t j = 0; j < matrix.getCols(); ++j) {
                if (j == cols) {
                    continue;
                }
                minor_matrix(matrix_i, matrix_j) = matrix(i, j);
                matrix_j++;
            }
            matrix_j = 0;
            matrix_i++;
        }
        return minor_matrix;
    }

    double Matrix::det() const {
        if (matrix_rows != matrix_cols) {
            throw DimensionMismatch(*this);
        }

        double num = 1;
        if (matrix_cols == 1) {
            return (*this)(0, 0);
        }

        if (matrix_cols == 2) {
            return (*this)(0, 0) * (*this)(1, 1) - (*this)(1, 0) * (*this)(0, 1);
        } else {
            double value = 0.0;
            for (size_t j = 0; j < matrix_cols; ++j) {
                Matrix minor_matrix = set_additional_minor((*this), 0, j);
                value += (*this)(0, j) * minor_matrix.det() * num;
                num *= -1;
            }
            return value;
        }
    }

    Matrix Matrix::adj() const {
        if (matrix_cols != matrix_rows) {
            throw DimensionMismatch(*this);
        }

        Matrix transp_matrix = this->transp();
        Matrix adj_matrix(this->getRows(), this->getRows());

        int num = 1;

        for (size_t i = 0; i < this->getRows(); i++)
            for (size_t j = 0; j < this->getRows(); j++) {
                num = (i + j) % 2 == 0 ? 1 : -1;

                Matrix matrix_minor = set_additional_minor(transp_matrix, i, j);
                double minor_matrix_det = matrix_minor.det();
                adj_matrix(i, j) = minor_matrix_det * num;
            }
        return adj_matrix;
    }

    Matrix Matrix::inv() const {
        if (matrix_cols != matrix_rows) {
            throw DimensionMismatch(*this);
        }

        double determinant = (*this).det();
        if (fabs(determinant) <= 1e-07) {
            throw SingularMatrix();
        }

        Matrix inv_matrix = (*this).adj()*(1.0/determinant);

        return inv_matrix;
    }
}  // namespace prep
