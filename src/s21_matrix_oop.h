// общее: 
// если метод не выбрасывает исключение, он должен быть noexcept
// если метод не меняет поля класса, он должен быть const
// если метод вообще не обращается к полям класса, он должен быть static 




#ifndef S21_CPP_MATRIX_H
#define S21_CPP_MATRIX_H


#include <iostream>
#include <cmath>
#include "s21_exception_handling.h"
// заголовочные файлы надо перенести в .cc.
// Так будет меньше включений в том файле, который подключит этот файл s21_matrix_oop.h в качестве заголовочного


// в целом нужно соблюсти порядок private полей, методов, public полей, методов. То есть что сначала идет в классе, а что в конце по гугл стилю


class S21Matrix {
    private:
        int rows_, cols_;
        double **matrix_;
		static constexpr double EPSILON = 1e-7;
		// именование: kEpsilon
		// https://google.github.io/styleguide/cppguide.html#Constant_Names
	
	
	
	private:
		// Private functions for internal use
		bool is_invalid_matrix() const;
		// именование: is_invalid слово matrix лишнее.
		// Очень хорошо, что ты стараешься писать понятно, но matrix лишнее, потому что мы уже находимся в классе S21Matrix 
		// и понятно, что valid к матрице относится
		// Аналогично и имена других методов
	
	
	
		bool are_different_sizes(const S21Matrix& other) const;
		bool matrix_is_not_squared() const;
		void count(const S21Matrix& other, char operand, double mult_num);
		void get_cofactor(S21Matrix& temp, int skip_row, int skip_col, int size) const;
		double get_determinant(const S21Matrix& matrix, int size);
		void get_algebraic_complement(double* res, int row_i, int col_i);
		// Exceptions
		void is_matrix_valid_exception_check() const;
		void are_matrices_valid_exception_check(const S21Matrix& other) const;
		void are_dimensions_equal_exception_check(const S21Matrix& other) const;
		void is_matrix_squared_exception_check() const;

    public:
		// Constructors
        S21Matrix();
        S21Matrix(int rows, int cols);
		~S21Matrix();
		S21Matrix(const S21Matrix& other);
		S21Matrix(S21Matrix&& other);
		// Main matrix functions
		bool EqMatrix(const S21Matrix& other);
		void SumMatrix(const S21Matrix& other);
		void SubMatrix(const S21Matrix& other);
		void MultNumber(const double num);
		void MultMatrix(const S21Matrix& other);
		S21Matrix Transpose();
		S21Matrix CalcComplements();
		double Determinant();
		S21Matrix InverseMatrix();
		// Operator overloading
		S21Matrix& operator+(const S21Matrix& other);
		S21Matrix& operator-(const S21Matrix& other);
		S21Matrix& operator*(const S21Matrix& other);
		S21Matrix& operator*(const double num);
		bool operator==(const S21Matrix& other);
		S21Matrix& operator=(const S21Matrix& other);
		S21Matrix& operator+=(const S21Matrix& other);
		S21Matrix& operator-=(const S21Matrix& other);
		S21Matrix& operator*=(const S21Matrix& other);
		S21Matrix& operator*=(const double num);
		double operator()(int i, int j);
		// Setters, getters and additional helper functions
        void setRows(int rows);
        int getRows() const;
        void setCols(int cols);
        int getCols() const;
        double getElement(int row, int col) const;
		void setElement(int row, int col, double value);
        void setElementsConst();
		void print_out_matrix() const;
		bool matrix_is_null() const;
};

#endif /* S21_CPP_MATRIX_H */
