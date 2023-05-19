#include <gtest/gtest.h>
#include "../s21_cpp_matrix.h"

TEST(MatrixTest, EqMatrix) {
	S21Matrix matrix1;
	S21Matrix matrix2;
	EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, SumMatrix) {
	S21Matrix matrix1;
	S21Matrix matrix2;
	S21Matrix expected_matrix;

	expected_matrix.setRows(3);
	expected_matrix.setCols(3);

	for (int i = 0; i < expected_matrix.getRows(); ++i) {
		for (int j = 0; j < expected_matrix.getCols(); ++j) {
			double value = 2 * matrix1.getElement(i, j);
			expected_matrix.setElement(i, j, value);
		}
	}

	matrix1.SumMatrix(matrix2);

	EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
}

TEST(MatrixTest, SubMatrix) {
	S21Matrix matrix1;
	S21Matrix matrix2;
	S21Matrix expected_matrix;

	expected_matrix.setRows(3);
	expected_matrix.setCols(3);

	for (int i = 0; i < expected_matrix.getRows(); ++i) {
		for (int j = 0; j < expected_matrix.getCols(); ++j) {
			expected_matrix.setElement(i, j, 0.0);
		}
	}

	matrix1.SubMatrix(matrix2);

	EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
}

TEST(MatrixTest, MultByNumber) {
	S21Matrix matrix1;
	S21Matrix expected_matrix;

	expected_matrix.setRows(3);
	expected_matrix.setCols(3);

	for (int i = 0; i < expected_matrix.getRows(); ++i) {
		for (int j = 0; j < expected_matrix.getCols(); ++j) {
			expected_matrix.setElement(i, j, matrix1.getElement(i, j) * 3.0);
		}
	}

	matrix1.MultNumber(3.0);

	EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
}

//TEST(MatrixTest, MultMatrix) {
//	
//	S21Matrix matrix1;
//	matrix1.setRows(2);
//	matrix1.setCols(3);
//	matrix1.setElement(0, 0, 1.0);
//	matrix1.setElement(0, 1, 2.0);
//	matrix1.setElement(0, 1, 3.0);
//	matrix1.setElement(1, 0, 1.0);
//	matrix1.setElement(1, 1, 2.0);
//	matrix1.setElement(1, 2, 3.0);
//
//	S21Matrix matrix2;
//	matrix2.setRows(3);
//	matrix2.setCols(2);
//	matrix2.setElement(0, 0, 1.0);
//	matrix2.setElement(0, 1, 2.0);
//	matrix2.setElement(0, 2, 1.0);
//	matrix2.setElement(1, 0, 2.0);
//	matrix2.setElement(1, 1, 1.0);
//	matrix2.setElement(1, 2, 2.0);
//
//	S21Matrix expected_matrix;
//
//	expected_matrix.setRows(2);
//	expected_matrix.setCols(2);
//
//    expected_matrix.setElement(0, 0, 6.0);
//    expected_matrix.setElement(0, 1, 12.0);
//    expected_matrix.setElement(1, 0, 6.0);
//    expected_matrix.setElement(1, 1, 12.0);
//    expected_matrix.setElement(2, 2, 111);
//
//	matrix1.MultMatrix(matrix2);
//
//	EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
//
//	matrix1.print_out_matrix();
//	expected_matrix.print_out_matrix();
//}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
