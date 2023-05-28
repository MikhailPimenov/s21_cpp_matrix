#include "s21_cpp_matrix.h"

S21Matrix::S21Matrix()
	: rows_(3), cols_(3) {
    setElementsConst();
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

bool S21Matrix::matrix_is_null() const {
	return (matrix_ == nullptr);
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
	return (this->getElement(i, j));
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

void S21Matrix::setRows(int rows) {
//	if (rows > 0) {
	    rows_ = rows;
//	} else {
//		throw std::out_of_range("Rows cannot be less than 1");
//	}
}

int S21Matrix::getRows() const {
    return rows_;
}

void S21Matrix::setCols(int cols) {
//    if (cols > 0) {
	    cols_ = cols;
//	} else {
//		throw std::out_of_range("Cols cannot be less than 1");
//	}
}

int S21Matrix::getCols() const {
    return cols_;
}

double S21Matrix::getElement(int row, int col) const {
    if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
        return matrix_[row][col];
    } else {
        throw std::out_of_range("Index out of range");
    }
}

void S21Matrix::setElement(int row, int col, double value) {
	matrix_[row][col] = value;
}

void S21Matrix::setElementsConst() {
	try {
		matrix_ = new double*[rows_];
		for (int i = 0; i < rows_; ++i) {
			matrix_[i] = new double[cols_];
	    }
		double element = 0.0;
	    for (int i = 0; i < rows_; ++i) {
		    for (int j = 0; j < cols_; ++j) {
			    matrix_[i][j] = element;
				++element;
	        }
	    }
	} catch (std::bad_alloc& ba) {
		std::cerr << "bad_alloc caught: " << ba.what() << '\n';
	}
}

void S21Matrix::print_out_matrix() const {
    for (int i = 0; i < getRows(); ++i) {
        for (int j = 0; j < getCols(); ++j) {
            std::cout << getElement(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
	bool are_equal = true;
	if (are_different_sizes(other)) {
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
	are_matrices_valid_exception_check(other);
	are_dimensions_equal_exception_check(other);
	count(other, '+', 0.0);
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
	are_matrices_valid_exception_check(other);
	are_dimensions_equal_exception_check(other);
	count(other, '-', 0.0);
}

void S21Matrix::MultMatrix(const S21Matrix& other) {
	are_matrices_valid_exception_check(other);
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

void S21Matrix::MultNumber(const double num) {
	is_matrix_valid_exception_check();
	count(*this, 'n', num);
}

S21Matrix S21Matrix::Transpose() {
	is_matrix_valid_exception_check();
	S21Matrix result(cols_, rows_);
	for (int row_i = 0; row_i < rows_; ++row_i) {
		for (int col_i = 0; col_i < cols_; ++col_i) {
			result.matrix_[col_i][row_i] = matrix_[row_i][col_i];
		}
	}
	return result;
}

S21Matrix S21Matrix::CalcComplements() {
	is_matrix_valid_exception_check();
	is_matrix_squared_exception_check();
	if (rows_ == 1) {
		S21Matrix result(1, 1);
		result.setElement(0, 0, matrix_[0][0]);
		return result;
	} else if (rows_ == 2) {
		S21Matrix result(2, 2);
		result.setElement(0, 0, matrix_[1][1]);
		result.setElement(0, 1, matrix_[1][0]);
		result.setElement(1, 0, matrix_[0][1]);
		result.setElement(1, 1, matrix_[0][0]);
		return result;
	} else {
		S21Matrix res_matrix(rows_, cols_);
		double temp_res = 0.0;
		for (int row_i = 0; row_i < rows_; ++row_i) {
			for (int col_i = 0; col_i < cols_; ++col_i) {
				S21Matrix temp(rows_ - 1, cols_ - 1);
				get_cofactor(temp, row_i, col_i, rows_);
				temp_res = get_determinant(temp, temp.rows_);
				get_algebraic_complement(&temp_res, row_i, col_i);
				res_matrix.setElement(row_i, col_i, temp_res);
			}
		}
		return res_matrix;
	}
    return S21Matrix();
}

S21Matrix S21Matrix::InverseMatrix() {
	is_matrix_valid_exception_check();
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

bool S21Matrix::matrix_is_not_squared() const {
	return rows_ != cols_;
}

void S21Matrix::are_matrices_valid_exception_check(const S21Matrix& other) const {
	if (this->is_invalid_matrix() || other.is_invalid_matrix()) {
		throw InvalidMatrixException("Matrix dimensions must be greater than zero");
	}
}

void S21Matrix::is_matrix_valid_exception_check() const {
	if (this->is_invalid_matrix()) {
		throw InvalidMatrixException("Matrix dimensions must be greater than zero");
	}
}

void S21Matrix::are_dimensions_equal_exception_check(const S21Matrix& other) const { 
	if (other.rows_ != rows_ || other.cols_ != cols_) {
		throw DifferentMatrixDimensionsException("Matrix dimenstions must be equal to perform sum, sub or mult operations");
	}
}

void S21Matrix::is_matrix_squared_exception_check() const {
	if (matrix_is_not_squared()) {
		throw NotSquaredMatrixException("Matrix should be squared to perform CaclComplements or Determinant");
	}
}
	
bool S21Matrix::are_different_sizes(const S21Matrix& other) const {
	return (other.rows_ != rows_ || other.cols_ != cols_);
}

bool S21Matrix::is_invalid_matrix() const {
	return (rows_ < 1 || cols_ < 1); 
}

void S21Matrix::count(const S21Matrix& other, char operand, double mult_num) {
	int row_i = 0, col_i = 0;
	while (row_i < rows_) {
		while (col_i < cols_) {
			if (operand == '+') {
				matrix_[row_i][col_i] = other.matrix_[row_i][col_i] + matrix_[row_i][col_i];
			}
			if (operand == '-') {	
				matrix_[row_i][col_i] = other.matrix_[row_i][col_i] - matrix_[row_i][col_i];
			}
			if (operand == 'n') {
				matrix_[row_i][col_i] = matrix_[row_i][col_i] * mult_num;
			}
			++col_i;
		}
		col_i = 0;
		++row_i;
	}
}

void S21Matrix::get_cofactor(S21Matrix& temp, int skip_row, int skip_col, int size) const {
	for (int temp_row_i = 0, read_row_i = 0; read_row_i < size; ++read_row_i) {
		if (read_row_i == skip_row) {
			continue;
		}
		for (int temp_col_i = 0, read_col_i = 0; read_col_i < size; ++read_col_i) {
			if (read_col_i == skip_col) {
				continue;
			}
			temp.matrix_[temp_row_i][temp_col_i] = matrix_[read_row_i][read_col_i];
			++temp_col_i;
		}
		++temp_row_i;
	}
}

double S21Matrix::get_determinant(const S21Matrix& matrix, int size) {
	double res = 0.0;
	if (size == 1) {
		res = matrix.matrix_[0][0];
	} else if (size > 1) {
		S21Matrix temp(size - 1, size - 1);
		int sign = 1;
		for (int col_index = 0; col_index < size; ++col_index) {
			matrix.get_cofactor(temp, 0, col_index, size);
			res += sign * matrix.matrix_[0][col_index] * get_determinant(temp, temp.rows_);
			sign *= -1;
		}
	}
	return res;
}

void S21Matrix::get_algebraic_complement(double* res, int row_i, int col_i) {
	*res *= pow(-1.0, row_i + col_i + 2);
}

double S21Matrix::Determinant() {
	is_matrix_valid_exception_check();
	is_matrix_squared_exception_check();
	double res = 0.0;
	if (rows_ == 1) {
		res = matrix_[0][0];
	} else {
		res = get_determinant(*this, rows_);
	}
	return res;
}
