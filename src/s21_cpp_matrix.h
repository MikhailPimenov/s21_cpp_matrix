#include <iostream>

class S21Matrix {
    private:
        int rows_, cols_;
        double **matrix_;

    public:

        S21Matrix() {
			setRows(3);
			setCols(3);
			setElementsConst();
		}

        ~S21Matrix() {
			for (int i = 0; i < rows_; i++) {
				delete [] matrix_[i];
			}
			delete [] matrix_;
		}
		
		void setRows(int rows) {
			rows_ = rows;
		}

		int getRows() const {
			return rows_;
		}
		
		void setCols(int cols) {
			cols_ = cols;
		}
		
		int getCols() const {
			return cols_;
		}

		double getElement(int row, int col) const {
			if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
				return matrix_[row][col];
			} else {
				throw std::out_of_range("Index out of range");
			}
		}

		void setElementsConst() {
			matrix_ = new double*[rows_];
			for (int i = 0; i < rows_; ++i) {
				matrix_[i] = new double[cols_];
			}
			double element = 0.0;
			for (int i = 0; i < rows_; ++i) {
				for (int j = 0; j < cols_; ++j) {
					matrix_[i][j] = element;
					++element;
				}
			}
		}
};
