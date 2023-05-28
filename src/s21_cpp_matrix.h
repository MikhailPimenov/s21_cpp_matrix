#ifndef S21_CPP_MATRIX_H
#define S21_CPP_MATRIX_H

#include <iostream>
#include <cmath>

class InvalidMatrixException : public std::invalid_argument {
public:
	InvalidMatrixException(const std::string& message) : std::invalid_argument(message) {}
};

class DifferentMatrixDimensionsException : public std::invalid_argument {
public:
	DifferentMatrixDimensionsException(const std::string& message) : std::invalid_argument(message) {}
};

class MultInvalidMatrixSizeException : public std::invalid_argument {
public:
	MultInvalidMatrixSizeException(const std::string& message) : std::invalid_argument(message) {}
};

class NotSquaredMatrixException : public std::invalid_argument {
public:
	NotSquaredMatrixException(const std::string& message) : std::invalid_argument(message) {}
};

class ZeroDeterminantException : public std::runtime_error {
public:
	ZeroDeterminantException(const std::string& message) : std::runtime_error(message) {}
};

class S21Matrix {
    private:
        int rows_, cols_;
        double **matrix_;
		static constexpr double EPSILON = 1e-7;
	private:
		// Private functions for internal use
		bool is_invalid_matrix() const;
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
