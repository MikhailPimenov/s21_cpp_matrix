#ifndef S21_CPP_MATRIX_H
#define S21_CPP_MATRIX_H

#include <iostream>

class InvalidMatrixException : public std::runtime_error {
public:
	InvalidMatrixException(const std::string& message) : std::runtime_error(message) {}
};

class DifferentMatrixDimensionsException : public std::runtime_error {
public:
	DifferentMatrixDimensionsException(const std::string& message) : std::runtime_error(message) {}
};

class MultInvalidMatrixSize : public std::runtime_error {
public:
	MultInvalidMatrixSize(const std::string& message) : std::runtime_error(message) {}
};

class S21Matrix {
    private:
        int rows_, cols_;
        double **matrix_;
		static constexpr double EPSILON = 1e-7;
	private:
		bool is_invalid_matrix() const;
		bool are_different_sizes(const S21Matrix& other) const;
		void count(const S21Matrix& other, char operand, double mult_num);

    public:
        S21Matrix();
        S21Matrix(int rows, int cols);
		~S21Matrix();
		S21Matrix(const S21Matrix& other);
		S21Matrix& operator=(const S21Matrix& other);
		
        void setRows(int rows);
        int getRows() const;
        void setCols(int cols);
        int getCols() const;
        double getElement(int row, int col) const;
		void setElement(int row, int col, double value);
        void setElementsConst();
		void print_out_matrix() const;
		bool EqMatrix(const S21Matrix& other);
		void SumMatrix(const S21Matrix& other);
		void SubMatrix(const S21Matrix& other);
		void MultNumber(const double num);
		void MultMatrix(const S21Matrix& other);
};

#endif /* S21_CPP_MATRIX_H */
