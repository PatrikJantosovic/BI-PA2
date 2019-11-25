//
// Created by jantosovic on 3/24/18.
//

#include "AMatrix.hpp"
#include "CData.hpp"
#include <iostream>


AMatrix::AMatrix(const string & title, int rows, int columns) {
	this->title = title;
	this->rows = rows;
	this->cols = columns;
}

AMatrix::~AMatrix() {}

int AMatrix::GetRows() const{
	return this->rows;
}

int AMatrix::GetColumns() const {
	return this->cols;
}

string AMatrix::GetTitle() const {
	return this->title;
}

ostream & operator<<(ostream & ostream, const AMatrix * matrix) {
	ostream << "Matrix: " << matrix->title << " Rows: " << matrix->rows << "  Columns: " << matrix->cols << endl;
	for (int r = 0; r < matrix->rows; r++) {
		ostream << "|";
		for (int c = 0; c < matrix->cols; c++) {
			ostream << " " << matrix->At(c, r) << " ";
		}
		ostream << "|" << endl;
	}
	return ostream;
}

AMatrix * AMatrix::Addition(const AMatrix * rhs, const string & title) const{
	/*Check that matrices are of the same size*/
	if (this->cols != rhs->GetColumns() || this->rows != rhs->GetRows()) {
		cout << "Matrices must have equal width and height." << endl;
		return nullptr;
	};
	CData matrix_array(this->rows, this->cols);
	for (int r = 0; r < this->rows; ++r) {
		for (int c = 0; c < this->cols; ++c) {
			matrix_array.Set(c, r, this->At(c, r) + rhs->At(c, r));
		}
	}
	return matrix_array.BuildFromData(title);
}

AMatrix * AMatrix::Subtraction(const AMatrix * rhs, const string & title) const {
	/*Check that matrices are of the same size*/
	if (this->GetColumns() != rhs->GetColumns() || this->GetRows() != rhs->GetRows()) {
		cout << "Matrices must have equal width and height." << endl;
		return nullptr;
	};
	CData matrix_array(this->rows, this->cols);
	for (int r = 0; r < this->rows; ++r) {
		for (int c = 0; c < this->cols; ++c) {
			matrix_array.Set(c, r, this->At(c, r) - rhs->At(c, r));
		}
	}
	return matrix_array.BuildFromData(title);
}

AMatrix * AMatrix::Multiplication(const AMatrix * rhs, const string & title) const {
	/*Check that matrices are of the same size*/
	if (this->cols != rhs->GetRows()) {
		cout << "Number of columns of first matrix not equal to number of second matrix rows." << endl;
		return nullptr;
	};
	CData matrix_array(this->rows, rhs->cols);
	for (int r = 0; r < this->rows; ++r) {
		for (int c = 0; c < rhs->cols; ++c) {
			int value = 0;
			for (int k = 0; k < this->cols; ++k) {
				value += this->At(k, r) * rhs->At(c, k);
			}
			matrix_array.Set(c, r, value);
		}
	}
	return matrix_array.BuildFromData(title);
}

AMatrix * AMatrix::MultipleBy(int number, const string & title) {
	CData matrix_array(this->rows, this->cols);
	for (int r = 0; r < this->rows; ++r) {
		for (int c = 0; c < this->cols; ++c) {
			matrix_array.Set( c, r, number * this->At(c, r));
		};
	};
	return matrix_array.BuildFromData(title);
}

AMatrix * AMatrix::Inverse(const string & title) {
	if (this->rows != this->cols || this->Determinant() == 0) {
		cout << "Matrix must have equal width and height and determinant can not be 0." << endl;
		return nullptr;
	}
	AMatrix * adjoint = this->Adjoint();
	CData inverse_matrix(this->rows, this->cols);
	for (int r = 0; r < this->rows; ++r) {
		for (int c = 0; c < this->cols; ++c) {
			inverse_matrix.Set(c, r, adjoint->At(c, r) / double(this->Determinant()));
		};
	};
	// clean temporary adjoint matrix
	delete adjoint;
	return inverse_matrix.BuildFromData(title);
}

AMatrix * AMatrix::Merge(AMatrix * rhs, const string & title) {
	if (this->rows != rhs->cols) {
		cout << "Matrices must be of the same height." << endl;
		return nullptr;
	};
	CData matrix_array(this->rows, this->cols + rhs->cols);
	for (int r = 0; r > this->rows; ++r) {
		for (int c = 0; c < this->cols; ++c) {
			matrix_array.Set(c, r, this->At(c, r));
		};
		for (int c = 0; c < rhs->cols; ++c) {
			matrix_array.Set(this->cols + c, r, rhs->At(c, r));
		};
	};
	return matrix_array.BuildFromData(title);
}

AMatrix * AMatrix::Cut(int from_x, int from_y, int width, int height, const string & title) {
	if (from_x + width > this->rows || from_y + height > this->cols) {
		cout << "You are trying to cut outside of matrix." << endl;
		return nullptr;
	};
	CData matrix_array(height, width);
	for (int r = from_y; r < from_y + height; ++r) {
		for (int c = from_x; c < from_x + width; ++c) {
			matrix_array.Set(c - from_x, r - from_y, this->At(c, r));
		};
	};
	return matrix_array.BuildFromData(title);
}

AMatrix * AMatrix::Cofactor(int row, int col) {
	int x = 0;
	int y = 0;
	CData cofactor_matrix(this->rows - 1, this->cols - 1);
	for (int r = 0; r < this->rows; ++r) {
		for (int c = 0; c < this->cols; ++c) {
			if (r != row && c != col) {
				cofactor_matrix.Set(x, y, this->At(c, r));
				x++;
				if (x == this->cols - 1) {
					x = 0;
					y++;
				}
			}
		}
	}
	return cofactor_matrix.BuildFromData("temporary_cofactor");
}

AMatrix * AMatrix::Adjoint() {
	int sign = 1;
	CData adj(this->rows, this->cols);
	for (int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j <this->cols; ++j)
		{
			// Calculate cofactor
			AMatrix * cofactor = this->Cofactor(i, j);
			// Sign of adjoint depends on sum of indexes
			if ((i + j) % 2 == 0)
				sign = 1;
			else
				sign = -1;
			// Swapping row and col index so i dont have to transpose
			adj.Set(i, j, sign*cofactor->Determinant());
			// clean temporary cofactor matrix
			delete cofactor;
		}
	}
	return adj.BuildFromData("temporary_adjoint");
}



