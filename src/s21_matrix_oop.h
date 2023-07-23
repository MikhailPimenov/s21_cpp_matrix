#ifndef S21_CPP_MATRIX_H
#define S21_CPP_MATRIX_H

class S21Matrix {
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
  S21Matrix operator+(const S21Matrix& right) const;
  S21Matrix operator-(const S21Matrix& right) const;
  S21Matrix operator*(const S21Matrix& right) const;
  S21Matrix operator*(const double number) const noexcept;
  bool operator==(const S21Matrix& right) const noexcept;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& right);
  S21Matrix& operator-=(const S21Matrix& right);
  S21Matrix& operator*=(const S21Matrix& right);
  S21Matrix& operator*=(const double num) noexcept;
  double& operator()(int row, int col);
  double operator()(int row, int col) const;
  // Setters, getters and additional helper functions
  void SetRows(int rows);
  int GetRows() const noexcept;
  void SetCols(int cols);
  int GetCols() const noexcept;
  void Print() const;
  bool IsNull() const;

 private:
  // Private member variables
  int rows_, cols_;
  double** matrix_;
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
  void areDimensionsEqualExceptionCheck(const S21Matrix& other) const;
  void isMatrixSquaredExceptionCheck() const;
};

#endif /* S21_CPP_MATRIX_H */
