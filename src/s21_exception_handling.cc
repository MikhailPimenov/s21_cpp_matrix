#include "s21_exception_handling.h"

#include "s21_matrix_oop.h"

void S21Matrix::are_matrices_valid_exception_check(
    const S21Matrix& other) const {
  if (this->is_invalid_matrix() || other.is_invalid_matrix()) {
  // (this) this-> лишнее. Да, с ним легче понимать, чей метод вызываешь, но это только на первом этапе.
  // Далее его необходимо писать надо только при обращении к полям или методам родительского класса-шаблона, вот там без него работать не будет
      
    throw InvalidMatrixException("Matrix dimensions must be greater than zero");
  }
}

void S21Matrix::is_matrix_valid_exception_check() const {
  if (this->is_invalid_matrix()) {
      // (this)
    throw InvalidMatrixException("Matrix dimensions must be greater than zero");
  }
}

void S21Matrix::are_dimensions_equal_exception_check(
    const S21Matrix& other) const {
  if (other.rows_ != rows_ || other.cols_ != cols_) {
    throw DifferentMatrixDimensionsException(
        "Matrix dimenstions must be equal to perform sum, sub or mult "
        "operations");
  }
}

void S21Matrix::is_matrix_squared_exception_check() const {
  if (matrix_is_not_squared()) {
    throw NotSquaredMatrixException(
        "Matrix should be squared to perform CaclComplements or Determinant");
  }
}
