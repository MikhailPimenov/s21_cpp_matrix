#include "s21_cpp_matrix.h"

S21Matrix::S21Matrix() {
    setRows(3);
    setCols(3);
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

S21Matrix::S21Matrix(const S21Matrix& other) {
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

// TODO: Exception when the rows or cols are incorrect
S21Matrix::S21Matrix(int rows, int cols) {
	rows_ = rows;
	cols_ = cols;

	matrix_ = new double*[rows];
	for (int row_i = 0; row_i < rows_; ++row_i) {
		matrix_[row_i] = new double[cols_];
		for (int col_i = 0; col_i < cols_; ++col_i) {
			// Set the default values for the matrix
			matrix_[row_i][col_i] = 0.0;
		}
	}
}

void S21Matrix::setRows(int rows) {
    rows_ = rows;
}

int S21Matrix::getRows() const {
    return rows_;
}

void S21Matrix::setCols(int cols) {
    cols_ = cols;
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
	if (rows_ != other.rows_ || cols_ != other.cols_) {
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
	try {
		if (is_invalid_matrix() || other.is_invalid_matrix()) {
			throw InvalidMatrixException("Matrix dimesions must be greater than zero");
		} else if (are_different_sizes(other)) {
			throw DifferentMatrixDimensionsException("Matrix dimenstions must be equal to perform sum, sub or mult operations");
		} else {
			count(other, '+', 0.0);
		}
	} catch (const InvalidMatrixException& inv_e) {
		std::cerr << "Caugth an invalid matrix exception: " << inv_e.what() << '\n';
	} catch (const DifferentMatrixDimensionsException& diff_dim_e) {
		std::cerr << "Caugth a different matrix dimensions exception: " << diff_dim_e.what() << '\n';
	}
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
	try {
		if (is_invalid_matrix() || other.is_invalid_matrix()) {
			throw InvalidMatrixException("Matrix dimesions must be greater than zero");
		} else if (are_different_sizes(other)) {
			throw DifferentMatrixDimensionsException("Matrix dimenstions must be equal to perform sum, sub or mult operations");
		} else {
			count(other, '-', 0.0);
		}
	} catch (const InvalidMatrixException& inv_e) {
		std::cerr << "Caugth an invalid matrix exception: " << inv_e.what() << '\n';
	} catch (const DifferentMatrixDimensionsException& diff_dim_e) {
		std::cerr << "Caugth a different matrix dimensions exception: " << diff_dim_e.what() << '\n';
	}
}

void S21Matrix::MultMatrix(const S21Matrix& other) {
	try {
		if (is_invalid_matrix() || other.is_invalid_matrix()) {
			throw InvalidMatrixException("Matrix dimesions must be greater than zero");
		} else if (cols_ != other.rows_) {
			throw MultInvalidMatrixSize("Numnber of rows of the first matrix must be equal to the number of cols of the second matrix to perform the multiplication");
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
	} catch (const InvalidMatrixException& inv_e) {
		std::cerr << "Caugth an invalid matrix exception: " << inv_e.what() << '\n';
	} catch (const DifferentMatrixDimensionsException& diff_dim_e) {
		std::cerr << "Caugth a different matrix dimensions exception: " << diff_dim_e.what() << '\n';
	}
}

void S21Matrix::MultNumber(const double num) {
	try {
		if (is_invalid_matrix()) {
			throw InvalidMatrixException("Matrix dimesions must be greater than zero");
		} else {
			count(*this, 'n', num);
		}
	} catch (const InvalidMatrixException& inv_e) {
		std::cerr << "Caugth an invalid matrix exception: " << inv_e.what() << '\n';
	}
}

S21Matrix S21Matrix::Transpose() {
	S21Matrix result(cols_, rows_);
	for (int row_i = 0; row_i < rows_; ++row_i) {
		for (int col_i = 0; col_i < cols_; ++col_i) {
			result.matrix_[col_i][row_i] = matrix_[row_i][col_i];
		}
	}
	return result;
}

S21Matrix S21Matrix::CalcComplements() {
	try {
		if (is_invalid_matrix()) {
			throw InvalidMatrixException("Matrix dimesions must be greater than zero");
		} else if (matrix_is_not_squared()) {
			throw NotSquaredMatrix("Matrix should be squared to perform CaclComplements");
		} else {
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
				S21Matrix temp(rows_, cols_);
				double temp_res = 0.0;
				for (int row_i = 0; row_i < rows_; ++row_i) {
					for (int col_i = 0; col_i < cols_; ++col_i) {
						// TODO get_cofactor function call
						// TODO temp_res = get_determinant function call
						// TODO get_algebraic_compliment function call
						// TODO copy temp to the result matrix
						std::cout << temp_res;
						std::cout << "Hello world";
					}
				}
				// TODO remove the temp object
				// TODO return result
				return temp;
			}
		}
	} catch (const InvalidMatrixException& inv_e) {
		std::cerr << "Caugth an invalid matrix exception: " << inv_e.what() << '\n';
	} catch (const NotSquaredMatrix& not_square_e) {
		std::cerr << "Caugth a not square matrix exception: " << not_square_e.what() << '\n';
	}
    // Return an empty matrix if an exception is thrown
    return S21Matrix();
}

bool S21Matrix::matrix_is_not_squared() const {
	return rows_ != cols_;
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
