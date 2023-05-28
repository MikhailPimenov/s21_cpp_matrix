#include "s21_matrix_oop.h"

// Setters and getters:

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

// Calculation helpers:

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

// Additional helper functions:
// Used for troubleshooting
//void S21Matrix::print_out_matrix() const {
//    for (int i = 0; i < getRows(); ++i) {
//        for (int j = 0; j < getCols(); ++j) {
//            std::cout << getElement(i, j) << " ";
//        }
//        std::cout << std::endl;
//    }
//}

bool S21Matrix::are_different_sizes(const S21Matrix& other) const {
	return (other.rows_ != rows_ || other.cols_ != cols_);
}

bool S21Matrix::is_invalid_matrix() const {
	return (rows_ < 1 || cols_ < 1); 
}

bool S21Matrix::matrix_is_not_squared() const {
	return rows_ != cols_;
}

bool S21Matrix::matrix_is_null() const {
	return (matrix_ == nullptr);
}

