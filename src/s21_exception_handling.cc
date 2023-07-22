#include "s21_matrix_oop.h"
#include "s21_exception_handling.h"
#include <iostream>
#include <cmath>

void S21Matrix::areDimensionsEqualExceptionCheck(const S21Matrix& other) const { 
	if (other.rows_ != rows_ || other.cols_ != cols_) {
		throw DifferentMatrixDimensionsException("Matrix dimenstions must be equal to perform sum, sub or mult operations");
	}
}

void S21Matrix::isMatrixSquaredExceptionCheck() const {
	if (isNotSquared()) {
		throw NotSquaredMatrixException("Matrix should be squared to perform CaclComplements or Determinant");
	}
}
