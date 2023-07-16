#include "s21_matrix_oop.h"
#include "s21_exception_handling.h"

void S21Matrix::areMatricesValidExceptionCheck(const S21Matrix& other) const {
	if (this->isInvalidMatrix() || other.isInvalidMatrix()) {
		throw InvalidMatrixException("Matrix dimensions must be greater than zero");
	}
}

void S21Matrix::isMatrixValidExceptionCheck() const {
	if (this->isInvalidMatrix()) {
		throw InvalidMatrixException("Matrix dimensions must be greater than zero");
	}
}

void S21Matrix::areDimensionsEqualExceptionCheck(const S21Matrix& other) const { 
	if (other.rows_ != rows_ || other.cols_ != cols_) {
		throw DifferentMatrixDimensionsException("Matrix dimenstions must be equal to perform sum, sub or mult operations");
	}
}

void S21Matrix::isMatrixSquaredExceptionCheck() const {
	if (matrixIsNotSquared()) {
		throw NotSquaredMatrixException("Matrix should be squared to perform CaclComplements or Determinant");
	}
}
