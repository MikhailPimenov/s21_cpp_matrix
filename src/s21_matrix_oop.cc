#include "s21_cpp_matrix.h"

// Constructors:

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

S21Matrix::S21Matrix(const S21Matrix& other) 
	: rows_(other.rows_), cols_(other.cols_) {
    matrix_ = new double*[rows_];
    // можно поместить в список инициализации matrix_(new double*[rows_])
    // а не в теле конструктора
		

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
	// здесь и только здесь должна быть проверка на rows > 0 и cols > 0 (или rows >= 0 и cols >= 0) и выброшено исключение, тогда больше нигде не придётся проверять, потому что 
	// матрица с неправильными rows_ и cols_ просто не будет создана, будет выброшено исключение.
	// Мы делаем rows_ и cols_ private специально для этого. И в SetRows и SetCols будет проверка для нового значения.
	// Поэтому больше нет способов изменить их на неправильные. В этом идея инкапсуляции
		
		
	matrix_ = new double*[rows];
	// можно поместить в список инициализации matrix_(new double*[rows_])
    	// а не в теле конструктора
		
	for (int row_i = 0; row_i < rows_; ++row_i) {
		matrix_[row_i] = new double[cols_];
		
		// вместо цикла можно matrix_[row_i] = new double[cols_]{}; тогда сразу нулями будет заполнено
		for (int col_i = 0; col_i < cols_; ++col_i) {
			matrix_[row_i][col_i] = 0.0;
		}
	}
}

// Main matrix functions:

bool S21Matrix::EqMatrix(const S21Matrix& other) {
	bool are_equal = true;
	if (are_different_sizes(other)) {
		are_equal = false;
		// можно сразу return false;
		
		
	} else {
	// если несколько return, то слово 'else' не будет и будет меньше вложенности, код станет удобнее читать
		
		for (int i = 0; i < rows_; ++i) {
			for (int j = 0; j < cols_; ++j) {
				if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > EPSILON) {
					are_equal = false;
					// нет смысла идти дальше по элементам, если элементы на позиции [0][0] отличаются.
					// return false или хотя бы break. Но break прервет только внутренний цикл
				}
			}
		}
	}
	return are_equal;
	
	// если несколько return, то здесь return true;
	// и не понадобится переменная are_equal
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
	are_matrices_valid_exception_check(other);
	// здесь не нужно проверять валидность другой матрицы. Это принципиально.
	// Мы проверяем, правильная ли она будет, при её создании.
	// А далее запрещаем все действия, которые могут оставить её в неверном состоянии, 
	// то есть rows_ неправильный и cols_ неправильный сделать будет нельзя. Внутри SetRows и SetCols должна быть проверка
	
	are_dimensions_equal_exception_check(other);
	count(other, '+', 0.0);
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
	are_matrices_valid_exception_check(other);
	// не нужно, проверка в конструкторе при создании. Аналогично с SumMatrix
	
	
	
	are_dimensions_equal_exception_check(other);
	count(other, '-', 0.0);
}

void S21Matrix::MultNumber(const double num) {
	is_matrix_valid_exception_check();
	// не нужно, проверка в конструкторе при создании. Аналогично с SumMatrix
	
	count(*this, 'n', num);
}
// и тогда метод не должен выбрасывать исключения, появится noexcept

void S21Matrix::MultMatrix(const S21Matrix& other) {
	are_matrices_valid_exception_check(other);
	// не нужно, проверка в конструкторе при создании. Аналогично с SumMatrix
	
	
	
	if (cols_ != other.rows_) {
		throw MultInvalidMatrixSizeException("Numnber of rows of the first matrix must be equal to the number of cols of the second matrix to perform the multiplication");
	} else {
		int result_rows = rows_, result_cols = other.cols_;
		S21Matrix temp(result_rows, result_cols);
		double current_sum = 0.0;
		// на этом уровне current_sum не нужен. Переменную лучше создавать как можно ближе к её использованию, 
		// чтобы её область видимости была минимальной. Чем меньше к ней доступа, тем меньше вероятность дать ей неправильное значение, поэтому меньше потенциальных ошибок
		
		
		for (int read_row_i = 0; read_row_i < result_rows; ++read_row_i) {
			for (int read_col_i = 0; read_col_i < result_cols; ++read_col_i) {
				// current_sum лучше создавать вот здесь. Тогда и обнулять его не придётся
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
	is_matrix_valid_exception_check();
	// не нужно, проверка в конструкторе при создании. Аналогично с SumMatrix
	
	
	
	S21Matrix result(cols_, rows_);
	for (int row_i = 0; row_i < rows_; ++row_i) {
		for (int col_i = 0; col_i < cols_; ++col_i) {
			result.matrix_[col_i][row_i] = matrix_[row_i][col_i];
		}
	}
	return result;
}
// метод должен быть константным, не меняет поля



S21Matrix S21Matrix::CalcComplements() {
	is_matrix_valid_exception_check();
	// не нужно, проверка в конструкторе при создании. Аналогично с SumMatrix
	
	
	
	is_matrix_squared_exception_check();
	if (rows_ == 1) {
		S21Matrix result(1, 1);
		result.setElement(0, 0, matrix_[0][0]);
		return result;
	} else if (rows_ == 2) {
	// слово 'else' лишнее
		
 		
		
		S21Matrix result(2, 2);
		result.setElement(0, 0, matrix_[1][1]);
		result.setElement(0, 1, matrix_[1][0]);
		result.setElement(1, 0, matrix_[0][1]);
		result.setElement(1, 1, matrix_[0][0]);
		return result;
	} else {
	// слово 'else' лишнее
		
		
	
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

double S21Matrix::Determinant() {
	is_matrix_valid_exception_check();
	// не нужно, проверка в конструкторе при создании. Аналогично с SumMatrix
	
	
	is_matrix_squared_exception_check();
	double res = 0.0;
	if (rows_ == 1) {
		res = matrix_[0][0];
		// можно сразу return matrix_[0][0];
		
	} else {
	// тогда else не понадобится и вложенности будет меньше
		
		
		res = get_determinant(*this, rows_);
		// можно сразу return get_determinant(*this, rows_);
		
		
	}
	return res;
}

S21Matrix S21Matrix::InverseMatrix() {
	is_matrix_valid_exception_check();
	// не нужно, проверка в конструкторе при создании. Аналогично с SumMatrix
	
	
	
	double det_res = 0.0;
	det_res = this->Determinant();
	// this-> лишнее
	
	if (fabs(det_res) < EPSILON) {
		throw ZeroDeterminantException("For InverseMatrix calculation the deteminant of the matrix shouldn't be equal to zero");
	} else {
	// слово 'else' лишнее. При выброшенном исключении точка выполнения программы не пойдёт сюда
		S21Matrix temp_first(rows_, cols_);
		S21Matrix temp_second(rows_, cols_);
		temp_first = this->CalcComplements();
		// this-> лишнее
		
		temp_second = temp_first.Transpose();
		temp_second.MultNumber(1.0 / det_res);
		return temp_second;
		
		// можно было обойтись одной временной матрицей:
		// S21Matrix temp(rows_, cols_); // S21Matrix temp(rows_, rows_); тоже подойдёт, потому что матрица квадратная - проверили, когда считали детерминант выше
		// temp = CalcComplements();
		// temp = temp.Transpose(); // да, так можно. При правильно реализованном operator=(S21Matrix&&) или хотя бы operator=(const S21Matrix&) будет работать
		// temp.MultNumber(1.0 / det_res);
		// return temp;
	}
    return S21Matrix();
}

// Operator overloading:

S21Matrix& S21Matrix::operator+(const S21Matrix& other) {
	this->SumMatrix(other);
	return *this;
}
// operator+ не должен менять текущую матрицу. Он должен только возвращать сумму
// https://www.learncpp.com/cpp-tutorial/overloading-the-arithmetic-operators-using-friend-functions/
// https://www.learncpp.com/cpp-tutorial/overloading-operators-using-member-functions/ 
// this-> лишнее
// если через метод, то он будет константным



S21Matrix& S21Matrix::operator-(const S21Matrix& other) {
	this->SubMatrix(other);
	return *this;
}
// аналогично с operator+
// this-> лишнее
// если через метод, то он будет константным


S21Matrix& S21Matrix::operator*(const S21Matrix& other) {
	this->MultMatrix(other);
	return *this;
}
// аналогично с operator+
// this-> лишнее
// если через метод, то он будет константным


S21Matrix& S21Matrix::operator*(const double number) {
	this->MultNumber(number);
	return *this;
}
// аналогично с operator+
// this-> лишнее
// если через метод, то он будет константным


bool S21Matrix::operator==(const S21Matrix& other) {
	return(this->EqMatrix(other));
}
// this-> лишнее
// метод должен быть константым и noexcept

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
	this->SumMatrix(other);
	return *this;
}
// this-> лишнее

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
	this->SubMatrix(other);
	return *this;
}
// this-> лишнее

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
	this->MultMatrix(other);
	return *this;
}
// this-> лишнее

S21Matrix& S21Matrix::operator*=(const double num) {
	this->MultNumber(num);
	return *this;
}
// this-> лишнее
// метод должен быть noexcept

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
		    
		// особо придирчивые могут предложить использовать std::copy для копирования
            }
        }
    }
    return *this;
}
// сделано верно, но есть продвинутый вариант. Он НЕ обязателен
// кратко: если matrix_ = new double*[rows_]; не смогло выделить память и выбросит исключение, 
// то копирование точно провалилось, а текущий объект, в который было копирование, уже удалил всё своё перед тем, как вместить чужое из other
// надо хотя бы чтобы свой объект всё своё сохранил.
// https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
// this-> лишнее


double S21Matrix::operator()(int i, int j) {
	return (this->getElement(i, j));
}
// this-> лишнее
// метод должен быть константным и noexcept
// нужна ещё перегрузка double& S21Matrix::operator()(int i, int j), через которую можно изменить элемент. Второй метод уже не константный
