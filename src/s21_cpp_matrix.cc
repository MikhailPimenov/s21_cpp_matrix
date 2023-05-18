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
			count(other, '+');
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
			count(other, '-');
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
		} else if (are_different_sizes(other)) {
			throw DifferentMatrixDimensionsException("Matrix dimenstions must be equal to perform sum, sub or mult operations");
		} else {
			count(other, '*');
		}
	} catch (const InvalidMatrixException& inv_e) {
		std::cerr << "Caugth an invalid matrix exception: " << inv_e.what() << '\n';
	} catch (const DifferentMatrixDimensionsException& diff_dim_e) {
		std::cerr << "Caugth a different matrix dimensions exception: " << diff_dim_e.what() << '\n';
	}
}

bool S21Matrix::are_different_sizes(const S21Matrix& other) const {
	return (other.rows_ != rows_ || other.cols_ != cols_);
}

bool S21Matrix::is_invalid_matrix() const {
	return (rows_ < 1 || cols_ < 1); 
}

void S21Matrix::count(const S21Matrix& other, char operand) {
	int row_i = 0, col_i = 0;
	while (row_i < rows_) {
		while (col_i < cols_) {
			if (operand == '+') {
				matrix_[row_i][col_i] = other.matrix_[row_i][col_i] + matrix_[row_i][col_i];
			}
			if (operand == '-') {	
				matrix_[row_i][col_i] = other.matrix_[row_i][col_i] - matrix_[row_i][col_i];
			}
			if (operand == '*') {
				int sum_row_i = 0, current_sum = 0;
				while (sum_row_i < cols_) {
					current_sum += other.matrix_[row_i][col_i] * matrix_[row_i][col_i];
					++sum_row_i;
				}
				matrix_[row_i][col_i] = current_sum;
			}
			++col_i;
		}
		col_i = 0;
		++row_i;
	}
}
