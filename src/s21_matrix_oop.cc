#include "s21_matrix_oop.h"
#include "s21_exception_handling.h"

// Constructors:
// лишний noexcept. Потому что new может выбросить исключение, если не может выделить память
S21Matrix::S21Matrix()
	: rows_(3), cols_(3) {
		
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
}

S21Matrix::~S21Matrix() noexcept {
    for (int i = 0; i < rows_; i++) {
        delete [] matrix_[i];
    }
    delete [] matrix_;
	rows_ = 0;
	cols_ = 0;
	matrix_ = nullptr;
}

// тоже лишний noexcept.
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

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
	: rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
	other.rows_ = 0;
	other.cols_ = 0;
	other.matrix_ = nullptr;
}

// поправил, чтобы удобнее было читать. Если можно раньше выйти из функции, то лучше раньше выйти.
// Так и не будет else, и меньше вложенность будет. (меньше отступа слева, т.е. строки короче будут)
S21Matrix::S21Matrix(int rows, int cols)
	: rows_(rows), cols_(cols) {
	if (isInvalid())
		throw std::bad_array_new_length();

	matrix_ = new double*[rows];
	for (int row_i = 0; row_i < rows_; ++row_i)
		matrix_[row_i] = new double[cols_]{};
}

// Main matrix functions:


// аналогично предыдущему. Написано в стиле C, когда из функции один выход. 
// Но если выйти из функции раньше, то будет меньше кода и легче читать. И меньше переменных
bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
	if (areDifferentSizes(other))
		return false;
	
	int i = 0, j = 0;
	while (i < rows_ && j < cols_) {
		if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > kEpsilon)
			return false;
		
		++j;
		if (j == cols_) {
			++i;
			j = 0;
		}
	}
	return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
	areDimensionsEqualExceptionCheck(other);
	count(other, '+', 0.0);
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
	areDimensionsEqualExceptionCheck(other);
	count(other, '-', 0.0);
}

void S21Matrix::MultNumber(const double num) noexcept {
	count(*this, 'n', num);
}

// При выбросе исключения точка выполнения не пойдёт дальше по методу, это как return.
// Поэтому нет необходимости в else
// Добавил const к переменным, которые не меняются
// Добавил std::move, чтобы превратить temp в ссылку r-value, чтобы вызвалась 
// перегрузка оператора присваивания перемещением. 
void S21Matrix::MultMatrix(const S21Matrix& other) {
	if (cols_ != other.rows_)
		throw MultInvalidMatrixSizeException("Numnber of rows of the first matrix must be equal to the number of cols of the second matrix to perform the multiplication");
	
	const int result_rows = rows_;
	const int result_cols = other.cols_;
	S21Matrix temp(result_rows, result_cols);
	for (int read_row_i = 0; read_row_i < result_rows; ++read_row_i) {
		for (int read_col_i = 0; read_col_i < result_cols; ++read_col_i) {
			double current_sum = 0.0;
			for (int sum_row_i = 0; sum_row_i < cols_; ++sum_row_i) {
				current_sum += matrix_[read_row_i][sum_row_i] * other.matrix_[sum_row_i][read_col_i];
			}
			temp.matrix_[read_row_i][read_col_i] = current_sum;
		}
	}
	*this = std::move(temp); 
}

// лишний noexcept. Потому что
// при создании объекта result выделяется память, поэтому может быть выброшено исключение
S21Matrix S21Matrix::Transpose() const {
	S21Matrix result(cols_, rows_);
	for (int row_i = 0; row_i < rows_; ++row_i) {
		for (int col_i = 0; col_i < cols_; ++col_i) {
			result.matrix_[col_i][row_i] = matrix_[row_i][col_i];
		}
	}
	return result;
}

S21Matrix S21Matrix::CalcComplements() const {
	isMatrixSquaredExceptionCheck();
	if (rows_ == 1) {
		S21Matrix result(1, 1);
		result.SetElement(0, 0, matrix_[0][0]);
		return result;
	}
	if (rows_ == 2) {
		S21Matrix result(2, 2);
		result.SetElement(0, 0, matrix_[1][1]);
		result.SetElement(0, 1, matrix_[1][0]);
		result.SetElement(1, 0, matrix_[0][1]);
		result.SetElement(1, 1, matrix_[0][0]);
		return result;
	}
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

// лишняя проверка для единичной размерности. Это уже делается в getDeterminant 
// Достаточно проверки на исключение
double S21Matrix::Determinant() const {
	isMatrixSquaredExceptionCheck();
	return getDeterminant(*this, rows_);
}


// Добавил const, объединил выражения. Для double не критично, просто меньше строк.
// Но для 	
// S21Matrix temp(rows_, cols_);
// temp = CalcComplements();
// сначала создаётся матрица, выделяется память. А затем при temp = CalcComplements()
// вызывается оператор=, котором всё это делается ещё раз
S21Matrix S21Matrix::InverseMatrix() const {
	const double det_res = Determinant();
	if (fabs(det_res) < kEpsilon) {
		throw ZeroDeterminantException("For InverseMatrix calculation the deteminant of the matrix shouldn't be equal to zero");
	} 
	S21Matrix temp = CalcComplements();  // copy constructor is called
	temp = temp.Transpose();
	temp.MultNumber(1.0 / det_res);
	return temp;
}

// Operator overloading:

S21Matrix operator+(const S21Matrix& left, const S21Matrix& right) {
	S21Matrix result = left;
	result.SumMatrix(right);
	return result;
}

S21Matrix operator-(const S21Matrix& left, const S21Matrix& right) {
	S21Matrix result = left;
	result.SubMatrix(right);
	return result;
}

S21Matrix operator*(const S21Matrix& left, const S21Matrix& right) {
	S21Matrix result = left;
	result.MultMatrix(right);
	return result;
}

S21Matrix operator*(const S21Matrix& left, const double number) noexcept {
	S21Matrix result = left;
	result.MultNumber(number);
	return result;
}

bool operator==(const S21Matrix& left, const S21Matrix& right) noexcept {
	return left.EqMatrix(right);
}

// см .h
S21Matrix& S21Matrix::operator+=(const S21Matrix& right) {
	SumMatrix(right);	// *this изменился здесь, к нему прибавился right
	return *this;
}

// см .h
/*можно и S21Matrix возвращать*/
S21Matrix& operator-=(S21Matrix& left, const S21Matrix& right) {
	left.SubMatrix(right);
	return left;
}

// см .h
S21Matrix& S21Matrix::operator*=(const S21Matrix& right) {
	MultMatrix(right);
	return *this;
}

// см .h
S21Matrix& S21Matrix::operator*=(const double num) noexcept {
	MultNumber(num);
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

// по заданию нужно бросать исключения
double& S21Matrix::operator()(int row, int col) {
	if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
		throw std::out_of_range("Index is out of range!");
	return matrix_[row][col];
}

// по заданию нужно бросать исключения
double S21Matrix::operator()(int row, int col) const {
	if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
		throw std::out_of_range("Index is out of range!");
	return GetElement(row, col);
}