#include <iostream>

class InvalidMatrixException : public std::runtime_error {
public:
	InvalidMatrixException(const std::string& message) : std::runtime_error(message) {}
};

class DifferentMatrixDimensionsException : public std::runtime_error {
public:
	DifferentMatrixDimensionsException(const std::string& message) : std::runtime_error(message) {}
};

class S21Matrix {
    private:
        int rows_, cols_;
        double **matrix_;
		static constexpr double EPSILON = 1e-7;
		bool is_invalid_matrix() const;
		bool are_different_sizes(const S21Matrix& other) const;
		void count(const S21Matrix& other, char operand);

    public:
        S21Matrix();
        ~S21Matrix();
		
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
};
