#include "s21_cpp_matrix.h"

// Constructors:

S21Matrix::S21Matrix()
	: rows_(3), cols_(3) {
    SetElementsConst();
}

S21Matrix::~S21Matrix() {
    for (int i = 0; i < rows_; i++) {
        delete [] matrix_[i];
    }
    delete [] matrix_;
	rows_ = 0;
	cols_ = 0;
	matrix_ = nullptr;
}

S21Matrix::S21Matrix(const S21Matrix& other) 
	: rows_(other.rows_), cols_(other.cols_) {
    matrix_ = new double*[rows_];
    for (int row_i = 0; row_i < rows_; ++row_i) {
        matrix_[row_i] = new double[cols_];
        for (int col_i = 0; col_i < cols_; ++col_i) {
            matrix_[row_i][col_i] = other.matrix_[row_i][col_i];
        }
    }
}

S21Matrix::S21Matrix(S21Matrix&& other)
	: rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
	other.rows_ = 0;
	other.cols_ = 0;
	other.matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols)
	: rows_(rows), cols_(cols) {

	matrix_ = new double*[rows];
	for (int row_i = 0; row_i < rows_; ++row_i) {
		matrix_[row_i] = new double[cols_];
		for (int col_i = 0; col_i < cols_; ++col_i) {
			matrix_[row_i][col_i] = 0.0;
		}
	}
}

// Main matrix functions:

bool S21Matrix::EqMatrix(const S21Matrix& other) {
	bool are_equal = true;
	if (areDifferentSizes(other)) {
		are_equal = false;
	} else {
		for (int i = 0; i < rows_; ++i) {
			for (int j = 0; j < cols_; ++j) {
				if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > EPSILON) {
					are_equal = false;
				}
			}
		}
	}
	return are_equal;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
	areMatricesValidExceptionCheck(other);
	areDimensionsEqualExceptionCheck(other);
	count(other, '+', 0.0);
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
	areMatricesValidExceptionCheck(other);
	areDimensionsEqualExceptionCheck(other);
	count(other, '-', 0.0);
}

void S21Matrix::MultNumber(const double num) {
	isMatrixValidExceptionCheck();
	count(*this, 'n', num);
}

void S21Matrix::MultMatrix(const S21Matrix& other) {
	areMatricesValidExceptionCheck(other);
	if (cols_ != other.rows_) {
		throw MultInvalidMatrixSizeException("Numnber of rows of the first matrix must be equal to the number of cols of the second matrix to perform the multiplication");
	} else {
		int result_rows = rows_, result_cols = other.cols_;
		S21Matrix temp(result_rows, result_cols);
		double current_sum = 0.0;
		for (int read_row_i = 0; read_row_i < result_rows; ++read_row_i) {
			for (int read_col_i = 0; read_col_i < result_cols; ++read_col_i) {
				for (int sum_row_i = 0; sum_row_i < cols_; ++sum_row_i) {
					current_sum += matrix_[read_row_i][sum_row_i] * other.matrix_[sum_row_i][read_col_i];
				}
				temp.matrix_[read_row_i][read_col_i] = current_sum;
				current_sum = 0;
			}
		}
		*this = temp;
	} 
}

S21Matrix S21Matrix::Transpose() {
	isMatrixValidExceptionCheck();
	S21Matrix result(cols_, rows_);
	for (int row_i = 0; row_i < rows_; ++row_i) {
		for (int col_i = 0; col_i < cols_; ++col_i) {
			result.matrix_[col_i][row_i] = matrix_[row_i][col_i];
		}
	}
	return result;
}

S21Matrix S21Matrix::CalcComplements() {
	isMatrixValidExceptionCheck();
	isMatrixSquaredExceptionCheck();
	if (rows_ == 1) {
		S21Matrix result(1, 1);
		result.SetElement(0, 0, matrix_[0][0]);
		return result;
	} else if (rows_ == 2) {
		S21Matrix result(2, 2);
		result.SetElement(0, 0, matrix_[1][1]);
		result.SetElement(0, 1, matrix_[1][0]);
		result.SetElement(1, 0, matrix_[0][1]);
		result.SetElement(1, 1, matrix_[0][0]);
		return result;
	} else {
		S21Matrix res_matrix(rows_, cols_);
		double temp_res = 0.0;
		for (int row_i = 0; row_i < rows_; ++row_i) {
			for (int col_i = 0; col_i < cols_; ++col_i) {
				S21Matrix temp(rows_ - 1, cols_ - 1);
				getCofactor(temp, row_i, col_i, rows_);
				temp_res = getDeterminant(temp, temp.rows_);
				getAlgebraicComplement(&temp_res, row_i, col_i);
				res_matrix.SetElement(row_i, col_i, temp_res);
			}
		}
		return res_matrix;
	}
    return S21Matrix();
}

double S21Matrix::Determinant() {
	isMatrixValidExceptionCheck();
	isMatrixSquaredExceptionCheck();
	double res = 0.0;
	if (rows_ == 1) {
		res = matrix_[0][0];
	} else {
		res = getDeterminant(*this, rows_);
	}
	return res;
}

S21Matrix S21Matrix::InverseMatrix() {
	isMatrixValidExceptionCheck();
	double det_res = 0.0;
	det_res = this->Determinant();
	if (fabs(det_res) < EPSILON) {
		throw ZeroDeterminantException("For InverseMatrix calculation the deteminant of the matrix shouldn't be equal to zero");
	} else {
		S21Matrix temp_first(rows_, cols_);
		S21Matrix temp_second(rows_, cols_);
		temp_first = this->CalcComplements();
		temp_second = temp_first.Transpose();
		temp_second.MultNumber(1.0 / det_res);
		return temp_second;
	}
    return S21Matrix();
}

// Operator overloading:

S21Matrix& S21Matrix::operator+(const S21Matrix& other) {
	this->SumMatrix(other);
	return *this;
}

S21Matrix& S21Matrix::operator-(const S21Matrix& other) {
	this->SubMatrix(other);
	return *this;
}

S21Matrix& S21Matrix::operator*(const S21Matrix& other) {
	this->MultMatrix(other);
	return *this;
}

S21Matrix& S21Matrix::operator*(const double number) {
	this->MultNumber(number);
	return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) {
	return(this->EqMatrix(other));
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
	this->SumMatrix(other);
	return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
	this->SubMatrix(other);
	return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
	this->MultMatrix(other);
	return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
	this->MultNumber(num);
	return *this;
}

// Copy assignment operator
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
    if (this != &other) {
        this->~S21Matrix();
        
        rows_ = other.rows_;
        cols_ = other.cols_;

        matrix_ = new double*[rows_];
        for (int row_i = 0; row_i < rows_; ++row_i) {
            matrix_[row_i] = new double[cols_];
            for (int col_i = 0; col_i < cols_; ++col_i) {
                matrix_[row_i][col_i] = other.matrix_[row_i][col_i];
            }
        }
    }
    return *this;
}

double S21Matrix::operator()(int i, int j) {
	return (this->GetElement(i, j));
}
