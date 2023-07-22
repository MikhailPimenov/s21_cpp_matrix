#ifndef S21_CPP_MATRIX_H
#define S21_CPP_MATRIX_H

#include <iostream>
#include <cmath>

class S21Matrix {
    private:
        int rows_, cols_;
        double **matrix_;

	static constexpr double kEpsilon = 1e-7;
	private:	// ещё надо смотреть порядок по гугл стилю, что сначала, private или public и т.д.
				// Я бы не смешивал под одним private поля и методы, так неудобно смотреть.
	// Private functions for internal use
	bool isInvalid() const;
	bool areDifferentSizes(const S21Matrix& other) const;
	bool isNotSquared() const;
	void count(const S21Matrix& other, char operand, double mult_num) noexcept;
	void getCofactor(S21Matrix& temp, int skip_row, int skip_col, int size) const;
	static double getDeterminant(const S21Matrix& matrix, int size);
	static void getAlgebraicComplement(double* res, int row_i, int col_i);
	// Exceptions
	void areDimensionsEqualExceptionCheck(const S21Matrix& other) const;
	void isMatrixSquaredExceptionCheck() const;

    public:
	// Constructors
    S21Matrix();
    S21Matrix(int rows, int cols);
	~S21Matrix() noexcept;
	S21Matrix(const S21Matrix& other);
	S21Matrix(S21Matrix&& other) noexcept;
	// Main matrix functions
	bool EqMatrix(const S21Matrix& other) const noexcept;
	void SumMatrix(const S21Matrix& other);
	void SubMatrix(const S21Matrix& other);
	void MultNumber(const double num) noexcept;
	void MultMatrix(const S21Matrix& other);
	S21Matrix Transpose() const;
	S21Matrix CalcComplements() const;
	double Determinant() const;
	S21Matrix InverseMatrix() const;
	// Operator overloading
	// можно снаружи, то есть без friend, потому что им никому не нужен доступ к private полям
	// friend S21Matrix operator+(const S21Matrix& left, const S21Matrix& right);
	// friend S21Matrix operator-(const S21Matrix& left, const S21Matrix& right);
	// friend S21Matrix operator*(const S21Matrix& left, const S21Matrix& right);
	// friend S21Matrix operator*(const S21Matrix& left, const double number) noexcept;
	// friend bool operator==(const S21Matrix& left, const S21Matrix& right) noexcept;

	S21Matrix& operator=(const S21Matrix& other);

	// операторы += -= и тд делают другое:
	// модифициуют текущую матрицу. += прибавляет другую матрицу к текущей:
	// Использование:
	// S21Matrix m1(2, 3);
	// m1 += m2;
	// Принимает только один аргумент и перегружается обычно через метод класса.
	// Но также можно перегружать и через дружественную функцию (если нужен доступ к private полям)
	// и через обычную функцию. Я покажу +=, *=, *= через метод и -= через обычную функцию, выбор за тобой
	// возвращать вообще ничего не обязательно, кстати.
	S21Matrix& operator+=(const S21Matrix& right);
	friend S21Matrix& operator-=(S21Matrix& left, const S21Matrix& right); // <- аргументы не симметрично выглядят, но на это всё равно

	// предпочтительнее через метод, потому что дружественная функция (или обычня функция) какбэ не симметрична по входным параметрам
    S21Matrix& operator*=(const S21Matrix& right);
	S21Matrix& operator*=(const double num) noexcept;
	
	// по заданию здесь должны быть исключения
	double& operator()(int row, int col);
	double operator()(int row, int col) const;
	// Setters, getters and additional helper functions
	void SetRows(int rows);
    int GetRows() const noexcept;
	void SetCols(int cols);
	int GetCols() const noexcept;
	double GetElement(int row, int col) const;			// на мой взгляд, лишние методы. Вместо них работает operator(). На ревью могут придраться
	void SetElement(int row, int col, double value);	// на мой взгляд, лишние методы. Вместо них работает operator(). На ревью могут придраться
	void Print() const;
	bool IsNull() const;
};

S21Matrix operator+(const S21Matrix& left, const S21Matrix& right);			
S21Matrix operator-(const S21Matrix& left, const S21Matrix& right);
S21Matrix operator*(const S21Matrix& left, const S21Matrix& right);
S21Matrix operator*(const S21Matrix& left, const double number) noexcept;
bool operator==(const S21Matrix& left, const S21Matrix& right) noexcept;

// + тесты на += -= *= надо переписать

#endif /* S21_CPP_MATRIX_H */
