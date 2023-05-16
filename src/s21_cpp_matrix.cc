#include "s21_cpp_matrix.h"

void print_out_matrix(const S21Matrix& matrix) {
	for (int i = 0; i < matrix.getRows(); ++i) {
		for (int j = 0; j < matrix.getCols(); ++j) {
			std::cout << matrix.getElement(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

int main() {
	S21Matrix test_matrix;
	print_out_matrix(test_matrix);	
	return 0;
}

