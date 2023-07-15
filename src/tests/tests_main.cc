#include <gtest/gtest.h>
#include "../s21_matrix_oop.h"

TEST(MatrixTest, EqMatrixElementsAreEqual) {
	S21Matrix matrix1;
	S21Matrix matrix2;
	EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixElementsAreDifferent) {

	S21Matrix matrix1(3, 2);
	matrix1.SetElement(0, 0, 1.0);
	matrix1.SetElement(0, 1, 2.0);
	matrix1.SetElement(1, 0, 3.0);
	matrix1.SetElement(1, 1, 1.0);
	matrix1.SetElement(2, 0, 2.0);
	matrix1.SetElement(2, 1, 3.0);

	S21Matrix matrix2(2, 3);
	matrix2.SetElement(0, 0, 1.0);
	matrix2.SetElement(0, 1, 3.0);
	matrix2.SetElement(0, 2, 3.0);
	matrix2.SetElement(1, 0, 1.0);
	matrix2.SetElement(1, 1, 2.0);
	matrix2.SetElement(1, 2, 3.0);

	EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixSizesAreDifferent) {

	S21Matrix matrix1(2, 2);
	matrix1.SetElement(0, 0, 1.0);
	matrix1.SetElement(0, 1, 2.0);
	matrix1.SetElement(1, 0, 3.0);
	matrix1.SetElement(1, 1, 1.0);

	S21Matrix matrix2(2, 3);
	matrix2.SetElement(0, 0, 1.0);
	matrix2.SetElement(0, 1, 3.0);
	matrix2.SetElement(0, 2, 3.0);
	matrix2.SetElement(1, 0, 1.0);
	matrix2.SetElement(1, 1, 2.0);
	matrix2.SetElement(1, 2, 3.0);

	EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixEpsilon) {

	S21Matrix matrix1(2, 2);
	matrix1.SetElement(0, 0, 1.0);
	matrix1.SetElement(0, 1, 2.000001);
	matrix1.SetElement(1, 0, 3.0);
	matrix1.SetElement(1, 1, 1.0);

	S21Matrix matrix2(2, 2);
	matrix2.SetElement(0, 0, 1.0);
	matrix2.SetElement(0, 1, 2.000000);
	matrix2.SetElement(1, 0, 1.0);
	matrix2.SetElement(1, 1, 2.0);

	EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixOperatorElementsAreEqual) {
	S21Matrix matrix1;
	S21Matrix matrix2;
	EXPECT_TRUE(matrix1 == matrix2);
}

TEST(MatrixTest, SumMatrixBasic) {
	S21Matrix matrix1;
	S21Matrix matrix2;
	S21Matrix expected_matrix;

	expected_matrix.SetRows(3);
	expected_matrix.SetCols(3);

	for (int i = 0; i < expected_matrix.GetRows(); ++i) {
		for (int j = 0; j < expected_matrix.GetCols(); ++j) {
			double value = 2 * matrix1.GetElement(i, j);
			expected_matrix.SetElement(i, j, value);
		}
	}

	matrix1.SumMatrix(matrix2);

	EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
}

TEST(MatrixTest, SumMatrixMatricesAreInvalid) {
	S21Matrix matrix1;
	matrix1.SetCols(0);
	S21Matrix matrix2;

	EXPECT_THROW(matrix1.SumMatrix(matrix2), InvalidMatrixException);
}

TEST(MatrixTest, SumMatrixMatricesOfDifferentSizes) {
	S21Matrix matrix1;
	matrix1.SetCols(1);
	S21Matrix matrix2;

	EXPECT_THROW(matrix1.SumMatrix(matrix2), DifferentMatrixDimensionsException);
}

TEST(MatrixTest, SumOperatorMatrix) {
	S21Matrix matrix1;
	S21Matrix matrix2;
	S21Matrix expected_matrix;

	expected_matrix.SetRows(3);
	expected_matrix.SetCols(3);

	for (int i = 0; i < expected_matrix.GetRows(); ++i) {
		for (int j = 0; j < expected_matrix.GetCols(); ++j) {
			double value = 2 * matrix1.GetElement(i, j);
			expected_matrix.SetElement(i, j, value);
		}
	}

	matrix1 + matrix2;

	EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
}

TEST(MatrixTest, SumOperatorMatrixMatricesAreInvalid) {
	S21Matrix matrix1;
	matrix1.SetCols(0);
	S21Matrix matrix2;

	EXPECT_THROW(matrix1 + matrix2, InvalidMatrixException);
}

TEST(MatrixTest, SumOperatorMatrixMatricesOfDifferentSizes) {
	S21Matrix matrix1;
	matrix1.SetCols(1);
	S21Matrix matrix2;

	EXPECT_THROW(matrix1 + matrix2, DifferentMatrixDimensionsException);
}

TEST(MatrixTest, AdditionAssignmentOperatorMatrix) {
	S21Matrix matrix1;
	S21Matrix matrix2;
	S21Matrix expected_matrix;

	expected_matrix.SetRows(3);
	expected_matrix.SetCols(3);

	for (int i = 0; i < expected_matrix.GetRows(); ++i) {
		for (int j = 0; j < expected_matrix.GetCols(); ++j) {
			double value = 2 * matrix1.GetElement(i, j);
			expected_matrix.SetElement(i, j, value);
		}
	}

	matrix1 += matrix2;

	EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
}

TEST(MatrixTest, AdditionAssignmentOperatorMatricesAreInvalid) {
	S21Matrix matrix1;
	matrix1.SetCols(0);
	S21Matrix matrix2;

	EXPECT_THROW(matrix1 += matrix2, InvalidMatrixException);
}



TEST(MatrixTest, AdditionAssignmentOperatorMatricesOfDifferentSizes) {
	S21Matrix matrix1;
	matrix1.SetCols(1);
	S21Matrix matrix2;

	EXPECT_THROW(matrix1 += matrix2, DifferentMatrixDimensionsException);
}


TEST(MatrixTest, SubMatrixBasic) {
	S21Matrix matrix1;
	S21Matrix matrix2;
	S21Matrix expected_matrix;

	expected_matrix.SetRows(3);
	expected_matrix.SetCols(3);

	for (int i = 0; i < expected_matrix.GetRows(); ++i) {
		for (int j = 0; j < expected_matrix.GetCols(); ++j) {
			expected_matrix.SetElement(i, j, 0.0);
		}
	}

	matrix1.SubMatrix(matrix2);

	EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
}

TEST(MatrixTest, SubMatrixMatricesAreInvalid) {
	S21Matrix matrix1;
	matrix1.SetCols(0);
	S21Matrix matrix2;
	S21Matrix expected_matrix;

	EXPECT_THROW(matrix1.SubMatrix(matrix2), InvalidMatrixException);
}

TEST(MatrixTest, SubMatrixMatricesOfDifferentSizes) {
	S21Matrix matrix1;
	matrix1.SetCols(1);
	S21Matrix matrix2;
	S21Matrix expected_matrix;

	EXPECT_THROW(matrix1.SubMatrix(matrix2), DifferentMatrixDimensionsException);
}

TEST(MatrixTest, SubOperatorMatrix) {
	S21Matrix matrix1;
	S21Matrix matrix2;
	S21Matrix expected_matrix;

	expected_matrix.SetRows(3);
	expected_matrix.SetCols(3);

	for (int i = 0; i < expected_matrix.GetRows(); ++i) {
		for (int j = 0; j < expected_matrix.GetCols(); ++j) {
			expected_matrix.SetElement(i, j, 0.0);
		}
	}

	matrix1 - matrix2;

	EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
}

TEST(MatrixTest, SubOperatorMatricesAreInvalid) {
	S21Matrix matrix1;
	matrix1.SetCols(0);
	S21Matrix matrix2;

	EXPECT_THROW(matrix1 - matrix2, InvalidMatrixException);
}

TEST(MatrixTest, SubOperatorMatricesOfDifferentSizes) {
	S21Matrix matrix1;
	matrix1.SetCols(1);
	S21Matrix matrix2;

	EXPECT_THROW(matrix1 - matrix2, DifferentMatrixDimensionsException);
}

TEST(MatrixTest, DifferenceAssignmentOperatorMatrix) {
	S21Matrix matrix1;
	S21Matrix matrix2;
	S21Matrix expected_matrix;

	expected_matrix.SetRows(3);
	expected_matrix.SetCols(3);

	for (int i = 0; i < expected_matrix.GetRows(); ++i) {
		for (int j = 0; j < expected_matrix.GetCols(); ++j) {
			expected_matrix.SetElement(i, j, 0.0);
		}
	}

	matrix1 -= matrix2;

	EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
}

TEST(MatrixTest, DifferenceAssignmentOperatorMatricesAreInvalid) {
	S21Matrix matrix1;
	matrix1.SetCols(0);
	S21Matrix matrix2;

	EXPECT_THROW(matrix1 -= matrix2, InvalidMatrixException);
}

TEST(MatrixTest, DifferenceAssignmentOperatorMatricesOfDifferentSizes) {
	S21Matrix matrix1;
	matrix1.SetCols(1);
	S21Matrix matrix2;

	EXPECT_THROW(matrix1 -= matrix2, DifferentMatrixDimensionsException);
}

TEST(MatrixTest, MultByNumberBasic) {
	S21Matrix matrix1;
	S21Matrix expected_matrix;

	expected_matrix.SetRows(3);
	expected_matrix.SetCols(3);

	for (int i = 0; i < expected_matrix.GetRows(); ++i) {
		for (int j = 0; j < expected_matrix.GetCols(); ++j) {
			expected_matrix.SetElement(i, j, matrix1.GetElement(i, j) * 3.0);
		}
	}

	matrix1.MultNumber(3.0);

	EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
}

TEST(MatrixTest, MultByNumberInvalidMatrixException) {
	S21Matrix matrix1(1, 0);
	EXPECT_THROW(matrix1.MultNumber(1.0), InvalidMatrixException);
}

TEST(MatrixTest, MultByNumberOperator) {
	S21Matrix matrix1;
	S21Matrix expected_matrix;

	expected_matrix.SetRows(3);
	expected_matrix.SetCols(3);

	for (int i = 0; i < expected_matrix.GetRows(); ++i) {
		for (int j = 0; j < expected_matrix.GetCols(); ++j) {
			expected_matrix.SetElement(i, j, matrix1.GetElement(i, j) * 3.0);
		}
	}

	matrix1 * 3.0;

	EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
}

TEST(MatrixTest, MultByNumberOperatorInvalidMatrixException) {
	S21Matrix matrix1(1, 0);
	EXPECT_THROW(matrix1 * 1.0, InvalidMatrixException);
}

TEST(MatrixTest, MultiplicationAssignmentOperatorMultNumber) {
	S21Matrix matrix1;
	S21Matrix expected_matrix;

	expected_matrix.SetRows(3);
	expected_matrix.SetCols(3);

	for (int i = 0; i < expected_matrix.GetRows(); ++i) {
		for (int j = 0; j < expected_matrix.GetCols(); ++j) {
			expected_matrix.SetElement(i, j, matrix1.GetElement(i, j) * 3.0);
		}
	}

	matrix1 *= 3.0;

	EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
}

TEST(MatrixTest, MultiplicationAssignmentOperatorInvalidMatrixException) {
	S21Matrix matrix1(1, 0);
	EXPECT_THROW(matrix1 *= 1.0, InvalidMatrixException);
}


TEST(MatrixTest, MultMatrixBasic) {
	
	S21Matrix matrix1(3, 2);
	matrix1.SetElement(0, 0, 1.0);
	matrix1.SetElement(0, 1, 2.0);
	matrix1.SetElement(1, 0, 3.0);
	matrix1.SetElement(1, 1, 1.0);
	matrix1.SetElement(2, 0, 2.0);
	matrix1.SetElement(2, 1, 3.0);

	S21Matrix matrix2(2, 3);
	matrix2.SetElement(0, 0, 1.0);
	matrix2.SetElement(0, 1, 2.0);
	matrix2.SetElement(0, 2, 3.0);
	matrix2.SetElement(1, 0, 1.0);
	matrix2.SetElement(1, 1, 2.0);
	matrix2.SetElement(1, 2, 3.0);

	S21Matrix expected_matrix(3, 3);

    expected_matrix.SetElement(0, 0, 3.0);
    expected_matrix.SetElement(0, 1, 6.0);
    expected_matrix.SetElement(0, 2, 9.0);
	expected_matrix.SetElement(1, 0, 4.0);
    expected_matrix.SetElement(1, 1, 8.0);
    expected_matrix.SetElement(1, 2, 12.0);
	expected_matrix.SetElement(2, 0, 5.0);
    expected_matrix.SetElement(2, 1, 10.0);
    expected_matrix.SetElement(2, 2, 15.0);

	matrix1.MultMatrix(matrix2);

	EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
}

TEST(MatrixTest, MultMatrixInvalidMatrixException) {
	
	S21Matrix matrix1(3, 0);

	S21Matrix matrix2(2, 3);
	matrix2.SetElement(0, 0, 1.0);
	matrix2.SetElement(0, 1, 2.0);
	matrix2.SetElement(0, 2, 3.0);
	matrix2.SetElement(1, 0, 1.0);
	matrix2.SetElement(1, 1, 2.0);
	matrix2.SetElement(1, 2, 3.0);

	EXPECT_THROW(matrix1.MultMatrix(matrix2), InvalidMatrixException);
}

TEST(MatrixTest, MultMatrixMultIndalidMatrixSizeException) {
	
	S21Matrix matrix1(3, 1);
	matrix1.SetElement(0, 0, 1.0);
	matrix1.SetElement(1, 0, 3.0);
	matrix1.SetElement(2, 0, 2.0);

	S21Matrix matrix2(2, 3);
	matrix2.SetElement(0, 0, 1.0);
	matrix2.SetElement(0, 1, 2.0);
	matrix2.SetElement(0, 2, 3.0);
	matrix2.SetElement(1, 0, 1.0);
	matrix2.SetElement(1, 1, 2.0);
	matrix2.SetElement(1, 2, 3.0);

	EXPECT_THROW(matrix1.MultMatrix(matrix2), MultInvalidMatrixSizeException);
}

TEST(MatrixTest, MultMatrixOperator) {
	
	S21Matrix matrix1(3, 2);
	matrix1.SetElement(0, 0, 1.0);
	matrix1.SetElement(0, 1, 2.0);
	matrix1.SetElement(1, 0, 3.0);
	matrix1.SetElement(1, 1, 1.0);
	matrix1.SetElement(2, 0, 2.0);
	matrix1.SetElement(2, 1, 3.0);

	S21Matrix matrix2(2, 3);
	matrix2.SetElement(0, 0, 1.0);
	matrix2.SetElement(0, 1, 2.0);
	matrix2.SetElement(0, 2, 3.0);
	matrix2.SetElement(1, 0, 1.0);
	matrix2.SetElement(1, 1, 2.0);
	matrix2.SetElement(1, 2, 3.0);

	S21Matrix expected_matrix(3, 3);

    expected_matrix.SetElement(0, 0, 3.0);
    expected_matrix.SetElement(0, 1, 6.0);
    expected_matrix.SetElement(0, 2, 9.0);
	expected_matrix.SetElement(1, 0, 4.0);
    expected_matrix.SetElement(1, 1, 8.0);
    expected_matrix.SetElement(1, 2, 12.0);
	expected_matrix.SetElement(2, 0, 5.0);
    expected_matrix.SetElement(2, 1, 10.0);
    expected_matrix.SetElement(2, 2, 15.0);

	matrix1 * matrix2;

	EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
}

TEST(MatrixTest, MultiplicationAssignmentOperatorMultMatrix) {
	
	S21Matrix matrix1(3, 2);
	matrix1.SetElement(0, 0, 1.0);
	matrix1.SetElement(0, 1, 2.0);
	matrix1.SetElement(1, 0, 3.0);
	matrix1.SetElement(1, 1, 1.0);
	matrix1.SetElement(2, 0, 2.0);
	matrix1.SetElement(2, 1, 3.0);

	S21Matrix matrix2(2, 3);
	matrix2.SetElement(0, 0, 1.0);
	matrix2.SetElement(0, 1, 2.0);
	matrix2.SetElement(0, 2, 3.0);
	matrix2.SetElement(1, 0, 1.0);
	matrix2.SetElement(1, 1, 2.0);
	matrix2.SetElement(1, 2, 3.0);

	S21Matrix expected_matrix(3, 3);

    expected_matrix.SetElement(0, 0, 3.0);
    expected_matrix.SetElement(0, 1, 6.0);
    expected_matrix.SetElement(0, 2, 9.0);
	expected_matrix.SetElement(1, 0, 4.0);
    expected_matrix.SetElement(1, 1, 8.0);
    expected_matrix.SetElement(1, 2, 12.0);
	expected_matrix.SetElement(2, 0, 5.0);
    expected_matrix.SetElement(2, 1, 10.0);
    expected_matrix.SetElement(2, 2, 15.0);

	matrix1 *= matrix2;

	EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
}

TEST(MatrixTest, EqMatrixOperator) {
	
	S21Matrix matrix1(3, 2);
	matrix1.SetElement(0, 0, 1.0);
	matrix1.SetElement(0, 1, 2.0);
	matrix1.SetElement(1, 0, 3.0);
	matrix1.SetElement(1, 1, 1.0);
	matrix1.SetElement(2, 0, 2.0);
	matrix1.SetElement(2, 1, 3.0);

	S21Matrix matrix2(3, 2);
	matrix2.SetElement(0, 0, 1.0);
	matrix2.SetElement(0, 1, 2.0);
	matrix2.SetElement(1, 0, 3.0);
	matrix2.SetElement(1, 1, 1.0);
	matrix2.SetElement(2, 0, 2.0);
	matrix2.SetElement(2, 1, 3.0);

	EXPECT_TRUE(matrix1 == matrix2);
}

TEST(MatrixTest, TransposeMatrixBasic) {
	
	S21Matrix matrix1(3, 2);
	matrix1.SetElement(0, 0, 1.0);
	matrix1.SetElement(0, 1, 2.0);
	matrix1.SetElement(1, 0, 3.0);
	matrix1.SetElement(1, 1, 1.0);
	matrix1.SetElement(2, 0, 2.0);
	matrix1.SetElement(2, 1, 3.0);

	S21Matrix expected_matrix(2, 3);

    expected_matrix.SetElement(0, 0, 1.0);
    expected_matrix.SetElement(0, 1, 3.0);
    expected_matrix.SetElement(0, 2, 2.0);
	expected_matrix.SetElement(1, 0, 2.0);
    expected_matrix.SetElement(1, 1, 1.0);
    expected_matrix.SetElement(1, 2, 3.0);

	S21Matrix transposed_matrix = matrix1.Transpose();

	EXPECT_TRUE(transposed_matrix.EqMatrix(expected_matrix));
}

TEST(MatrixTest, TransposeMatrixInvalidMatrixException) {
	
	S21Matrix matrix1(3, 0);

	EXPECT_THROW(matrix1.Transpose(), InvalidMatrixException);
}

TEST(MatrixTest, CalcComplementsMatrixBasic00) {
	S21Matrix input_matrix(1, 1);
	input_matrix.SetElement(0, 0, 21.0);

	S21Matrix expected_result(1, 1);
	expected_result.SetElement(0, 0, 21.0);

	S21Matrix actual_result = input_matrix.CalcComplements();

	EXPECT_TRUE(actual_result.EqMatrix(expected_result));
}

TEST(MatrixTest, CalcComplementsMatrixBasic01) {
	S21Matrix input_matrix(2, 2);
	input_matrix.SetElement(0, 0, 21.0);
	input_matrix.SetElement(0, 1, 42.0);
	input_matrix.SetElement(1, 0, 13.0);
	input_matrix.SetElement(1, 1, 420.0);

	S21Matrix expected_result(2, 2);
	expected_result.SetElement(0, 0, 420.0);
	expected_result.SetElement(0, 1, 13.0);
	expected_result.SetElement(1, 0, 42.0);
	expected_result.SetElement(1, 1, 21.0);

	S21Matrix actual_result = input_matrix.CalcComplements();

	EXPECT_TRUE(actual_result.EqMatrix(expected_result));
}

TEST(MatrixTest, CalcComplementsMatrixBasic02) {
	
	S21Matrix input_matrix(3, 3);
	input_matrix.SetElement(0, 0, 1.0);
	input_matrix.SetElement(0, 1, 2.0);
	input_matrix.SetElement(0, 2, 3.0);
	input_matrix.SetElement(1, 0, 1.0);
	input_matrix.SetElement(1, 1, 3.0);
	input_matrix.SetElement(1, 2, 2.0);
	input_matrix.SetElement(2, 0, 5.0);
	input_matrix.SetElement(2, 1, 2.0);
	input_matrix.SetElement(2, 2, 1.0);

	S21Matrix expected_matrix(3, 3);

    expected_matrix.SetElement(0, 0, -1.0);
    expected_matrix.SetElement(0, 1, 9.0);
    expected_matrix.SetElement(0, 2, -13.0);
	expected_matrix.SetElement(1, 0, 4.0);
    expected_matrix.SetElement(1, 1, -14.0);
    expected_matrix.SetElement(1, 2, 8.0);
    expected_matrix.SetElement(2, 0, -5.0);
    expected_matrix.SetElement(2, 1, 1.0);
    expected_matrix.SetElement(2, 2, 1.0);

	S21Matrix actual_result = input_matrix.CalcComplements();

	EXPECT_TRUE(actual_result.EqMatrix(expected_matrix));
}

TEST(MatrixTest, CalcComplementsMatrixInvalidMatrixException) {
	
	S21Matrix input_matrix(3, 0);
	
	EXPECT_THROW(input_matrix.CalcComplements(), InvalidMatrixException);
}

TEST(MatrixTest, CalcComplementsMatrixNotSquaredMatrixException) {
	
	S21Matrix input_matrix(3, 1);
	
	EXPECT_THROW(input_matrix.CalcComplements(), NotSquaredMatrixException);
}

TEST(MatrixTest, DeterminantMatrixBasic00) {
	
	S21Matrix input_matrix(3, 3);
	input_matrix.SetElement(0, 0, 21.0);
	input_matrix.SetElement(0, 1, 42.0);
	input_matrix.SetElement(0, 2, 13.0);
	input_matrix.SetElement(1, 0, 21.0);
	input_matrix.SetElement(1, 1, 42.0);
	input_matrix.SetElement(1, 2, 13.0);
	input_matrix.SetElement(2, 0, 21.0);
	input_matrix.SetElement(2, 1, 42.0);
	input_matrix.SetElement(2, 2, 13.0);

	double expected_result = 0.0;

	double actual_result = input_matrix.Determinant();

	ASSERT_DOUBLE_EQ(expected_result, actual_result);
}

TEST(MatrixTest, DeterminantMatrixBasic01) {
	
	S21Matrix input_matrix(3, 3);
	input_matrix.SetElement(0, 0, 2.0);
	input_matrix.SetElement(0, 1, 5.0);
	input_matrix.SetElement(0, 2, 7.0);
	input_matrix.SetElement(1, 0, 6.0);
	input_matrix.SetElement(1, 1, 3.0);
	input_matrix.SetElement(1, 2, 4.0);
	input_matrix.SetElement(2, 0, 5.0);
	input_matrix.SetElement(2, 1, -2.0);
	input_matrix.SetElement(2, 2, -3.0);

	double expected_result = -1.0;

	double actual_result = input_matrix.Determinant();

	ASSERT_DOUBLE_EQ(expected_result, actual_result);
}

TEST(MatrixTest, DeterminantInvalidMatrixException) {
	
	S21Matrix input_matrix(3, 0);

	EXPECT_THROW(input_matrix.Determinant(), InvalidMatrixException);
}

TEST(MatrixTest, DeterminantNotSquaredMatrixException) {
	
	S21Matrix input_matrix(3, 1);

	EXPECT_THROW(input_matrix.Determinant(), NotSquaredMatrixException);
}

TEST(MatrixTest, InverseMatrixBasic) {
	
	S21Matrix input(3, 3);
	input.SetElement(0, 0, 2.0);
	input.SetElement(0, 1, 5.0);
	input.SetElement(0, 2, 7.0);
	input.SetElement(1, 0, 6.0);
	input.SetElement(1, 1, 3.0);
	input.SetElement(1, 2, 4.0);
	input.SetElement(2, 0, 5.0);
	input.SetElement(2, 1, -2.0);
	input.SetElement(2, 2, -3.0);

	S21Matrix expected(3, 3);

    expected.SetElement(0, 0, 1.0);
    expected.SetElement(0, 1, -1.0);
    expected.SetElement(0, 2, 1.0);
	expected.SetElement(1, 0, -38.0);
    expected.SetElement(1, 1, 41.0);
    expected.SetElement(1, 2, -34.0);
    expected.SetElement(2, 0, 27.0);
    expected.SetElement(2, 1, -29.0);
    expected.SetElement(2, 2, 24.0);

	S21Matrix actual = input.InverseMatrix();

	EXPECT_TRUE(actual.EqMatrix(expected));
}

TEST(MatrixTest, InverseMatrixZeroException) {
	
	S21Matrix input(3, 3);
	input.SetElement(0, 0, 1.0);
	input.SetElement(0, 1, 2.0);
	input.SetElement(0, 2, 3.0);
	input.SetElement(1, 0, 4.0);
	input.SetElement(1, 1, 5.0);
	input.SetElement(1, 2, 6.0);
	input.SetElement(2, 0, 7.0);
	input.SetElement(2, 1, 8.0);
	input.SetElement(2, 2, 9.0);

	EXPECT_THROW(input.InverseMatrix(), ZeroDeterminantException);
}

TEST(MatrixTest, InverseInvalidMatrixException) {
	
	S21Matrix input(3, 0);

	EXPECT_THROW(input.InverseMatrix(), InvalidMatrixException);
}

TEST(MatrixTest, BasicConstructorTest) {
	
	S21Matrix actual;

	S21Matrix expected(3, 3);
	expected.SetElement(0, 0, 0.0);
	expected.SetElement(0, 1, 1.0);
	expected.SetElement(0, 2, 2.0);
	expected.SetElement(1, 0, 3.0);
	expected.SetElement(1, 1, 4.0);
	expected.SetElement(1, 2, 5.0);
	expected.SetElement(2, 0, 6.0);
	expected.SetElement(2, 1, 7.0);
	expected.SetElement(2, 2, 8.0);

	EXPECT_TRUE(actual.EqMatrix(expected));
}

TEST(MatrixTest, ParametrizedConstructorTest) {
	
	S21Matrix actual(3, 3);

	S21Matrix expected(3, 3);
	expected.SetElement(0, 0, 0.0);
	expected.SetElement(0, 1, 0.0);
	expected.SetElement(0, 2, 0.0);
	expected.SetElement(1, 0, 0.0);
	expected.SetElement(1, 1, 0.0);
	expected.SetElement(1, 2, 0.0);
	expected.SetElement(2, 0, 0.0);
	expected.SetElement(2, 1, 0.0);
	expected.SetElement(2, 2, 0.0);

	EXPECT_TRUE(actual.EqMatrix(expected));
}

TEST(MatrixTest, CopyConstructorTest) {
	
	S21Matrix input(3, 3);
	input.SetElement(0, 0, 1.0);
	input.SetElement(0, 1, 2.0);
	input.SetElement(0, 2, 3.0);
	input.SetElement(1, 0, 4.0);
	input.SetElement(1, 1, 5.0);
	input.SetElement(1, 2, 6.0);
	input.SetElement(2, 0, 7.0);
	input.SetElement(2, 1, 8.0);
	input.SetElement(2, 2, 9.0);

	S21Matrix expected(3, 3);
	expected.SetElement(0, 0, 1.0);
	expected.SetElement(0, 1, 2.0);
	expected.SetElement(0, 2, 3.0);
	expected.SetElement(1, 0, 4.0);
	expected.SetElement(1, 1, 5.0);
	expected.SetElement(1, 2, 6.0);
	expected.SetElement(2, 0, 7.0);
	expected.SetElement(2, 1, 8.0);
	expected.SetElement(2, 2, 9.0);

	S21Matrix actual(input);

	EXPECT_TRUE(actual.EqMatrix(expected));
}

TEST(MatrixTest, CopyAssignmentOperatorTest) {
	
	S21Matrix input(3, 3);
	input.SetElement(0, 0, 1.0);
	input.SetElement(0, 1, 2.0);
	input.SetElement(0, 2, 3.0);
	input.SetElement(1, 0, 4.0);
	input.SetElement(1, 1, 5.0);
	input.SetElement(1, 2, 6.0);
	input.SetElement(2, 0, 7.0);
	input.SetElement(2, 1, 8.0);
	input.SetElement(2, 2, 9.0);

	S21Matrix expected(3, 3);
	expected.SetElement(0, 0, 1.0);
	expected.SetElement(0, 1, 2.0);
	expected.SetElement(0, 2, 3.0);
	expected.SetElement(1, 0, 4.0);
	expected.SetElement(1, 1, 5.0);
	expected.SetElement(1, 2, 6.0);
	expected.SetElement(2, 0, 7.0);
	expected.SetElement(2, 1, 8.0);
	expected.SetElement(2, 2, 9.0);

	S21Matrix actual = input;

	EXPECT_TRUE(actual.EqMatrix(expected));
}

TEST(MatrixTest, MovementConstructorTest) {
	
	S21Matrix input(3, 3);
	input.SetElement(0, 0, 1.0);
	input.SetElement(0, 1, 2.0);
	input.SetElement(0, 2, 3.0);
	input.SetElement(1, 0, 4.0);
	input.SetElement(1, 1, 5.0);
	input.SetElement(1, 2, 6.0);
	input.SetElement(2, 0, 7.0);
	input.SetElement(2, 1, 8.0);
	input.SetElement(2, 2, 9.0);

	S21Matrix expected(3, 3);
	expected.SetElement(0, 0, 1.0);
	expected.SetElement(0, 1, 2.0);
	expected.SetElement(0, 2, 3.0);
	expected.SetElement(1, 0, 4.0);
	expected.SetElement(1, 1, 5.0);
	expected.SetElement(1, 2, 6.0);
	expected.SetElement(2, 0, 7.0);
	expected.SetElement(2, 1, 8.0);
	expected.SetElement(2, 2, 9.0);

	S21Matrix actual(std::move(input));

	EXPECT_TRUE(actual.EqMatrix(expected));
}

TEST(MatrixTest, DestructorTest) {
	
	S21Matrix input(3, 3);
	input.SetElement(0, 0, 1.0);
	input.SetElement(0, 1, 2.0);
	input.SetElement(0, 2, 3.0);
	input.SetElement(1, 0, 4.0);
	input.SetElement(1, 1, 5.0);
	input.SetElement(1, 2, 6.0);
	input.SetElement(2, 0, 7.0);
	input.SetElement(2, 1, 8.0);
	input.SetElement(2, 2, 9.0);

	input.~S21Matrix();

	int rows = input.GetRows();
	int cols = input.GetCols();
	bool is_null = input.Matrix_is_null();
	
	ASSERT_EQ(rows, 0);
	ASSERT_EQ(cols, 0);
	EXPECT_TRUE(is_null);
}

TEST(MatrixTest, IndexationByMatrixElements) {
	
	S21Matrix input(3, 3);
	input.SetElement(0, 0, 1.0);
	input.SetElement(0, 1, 2.0);
	input.SetElement(0, 2, 3.0);
	input.SetElement(1, 0, 4.0);
	input.SetElement(1, 1, 5.0);
	input.SetElement(1, 2, 6.0);
	input.SetElement(2, 0, 7.0);
	input.SetElement(2, 1, 8.0);
	input.SetElement(2, 2, 9.0);

	double actual = input(1, 1);
	double expected = 5.0;

	ASSERT_DOUBLE_EQ(expected, actual);
}

TEST(MatrixTest, IndexationByMatrixElementsOutOfRange) {
	
	S21Matrix input(3, 3);
	input.SetElement(0, 0, 1.0);
	input.SetElement(0, 1, 2.0);
	input.SetElement(0, 2, 3.0);
	input.SetElement(1, 0, 4.0);
	input.SetElement(1, 1, 5.0);
	input.SetElement(1, 2, 6.0);
	input.SetElement(2, 0, 7.0);
	input.SetElement(2, 1, 8.0);
	input.SetElement(2, 2, 9.0);

	EXPECT_THROW(input(1, 4), std::out_of_range);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
