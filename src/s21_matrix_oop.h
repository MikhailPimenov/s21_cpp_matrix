#ifndef S21_CPP_MATRIX_H
#define S21_CPP_MATRIX_H

#include <iostream>
#include <cmath>

class S21Matrix {
    private:
        int rows_, cols_;
        double **matrix_;
	static constexpr double kEpsilon = 1e-7;
	// Private functions for internal use
	bool isInvalid() const;
	bool areDifferentSizes(const S21Matrix& other) const;
	bool isNotSquared() const;
	void count(const S21Matrix& other, char operand, double mult_num) noexcept;
	void getCofactor(S21Matrix& temp, int skip_row, int skip_col, int size) const;
	static double getDeterminant(const S21Matrix& matrix, int size);
	static void getAlgebraicComplement(double* res, int row_i, int col_i);
	// Exceptions
	void isMatrixValidExceptionCheck() const;
	void areMatricesValidExceptionCheck(const S21Matrix& other) const;
	void areDimensionsEqualExceptionCheck(const S21Matrix& other) const;
	void isMatrixSquaredExceptionCheck() const;

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
	S21Matrix Transpose() const;
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
	double& operator()(int row, int col);
	double operator()(int row, int col) const;
	// Setters, getters and additional helper functions
	void SetRows(int rows);
    int GetRows() const noexcept;
	void SetCols(int cols);
	int GetCols() const noexcept;
	double GetElement(int row, int col) const;
	void SetElement(int row, int col, double value);
	void Print() const;
	bool isNull() const;
};

#endif /* S21_CPP_MATRIX_H */
