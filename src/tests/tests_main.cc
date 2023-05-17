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

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
