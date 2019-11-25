//
// Created by jantosovic on 5/08/18.
//
#include "CDense.hpp"
#include "CData.hpp"
#include <cfloat>
#include<iostream>
#include <cmath>

using namespace std;

CDense::CDense(vector< vector<double> > & matrix, string title, int rows, int cols) 
: AMatrix(title, rows, cols) {
	this->matrix_array.resize(cols, vector<double> (rows, 0));
	for (int r = 0; r < this->rows; ++r) {
		for (int c = 0; c < this->cols; ++c) {
			this->matrix_array[c][r] = matrix[c][r];
		}
	}
}

CDense::~CDense() {}

double CDense::At(int x, int y) const {
	if (x >= this->cols || y >= this->rows) {
		throw invalid_argument("Out of bound");
	};
	return this->matrix_array[x][y];
}

AMatrix * CDense::Transpose(const string & title) const {
	vector<vector<double>> transposed_matrix(this->rows, vector<double>(this->cols, 0));
	for (int r = 0; r < this->rows; ++r) {
		for (int c = 0; c < this->cols; ++c) {
			transposed_matrix[r][c] = this->matrix_array[c][r];
		}
	}
	return new CDense(transposed_matrix, title, this->cols, this->rows);
}

void CDense::GEM(bool verbose) {
	if (verbose) {
		cout << "Initial matrix:" << endl;
		cout << this << endl;
	};
	/* Pivotisation of matrix*/
	for (int i = 0; i < this->rows; ++i) {
		double max_value = this->At(i, i);
		int max_row = i;

		for (int k = i + 1; k < this->rows; ++k) {
			if (fabs(this->At(i, k)) > max_value) {
				max_row = k;
				max_value = this->At(i, k);
			}
		}

		for (int j = i; j < this->cols; ++j)
		{
			double tmp = this->At(j, max_row);
			this->matrix_array[j][max_row] = this->At(j, i);
			this->matrix_array[j][i] = tmp;
		}

		/*Actual GEM happening here*/
		for (int j = i + 1; j < this->rows; ++j) {
			double param = this->At(i, j) / this->At(i, i);
			for (int k = i; k < this->cols; ++k) {
				if (i == k) {
					this->matrix_array[k][j] = 0;
				}
				else {
					this->matrix_array[k][j] = this->At(k, j) - param*this->At(k, i);
				}
			}
		}
		if (verbose)
			cout << this << endl;
	}
}


int CDense::Rank() {
	if (this->rows == 0) return 0;
	AMatrix * temporary = new CDense(this->matrix_array, "temp", this->rows, this->cols);
	temporary->GEM(false);
	int rank = temporary->GetRows();
	for (int r = 0; r < temporary->GetRows(); ++r) {
		int nulls = 0;
		for (int c = 0; c < temporary->GetColumns(); ++c) {
			if (this->At(c, r) == 0)
				++nulls;
		}
		if (nulls == this->cols)
			--rank;
	};
	delete temporary;
	return rank;
}

double CDense::Determinant() {
	double determinant = 1;
	/*Transform to Upper triangular Form and multiply the diagonal*/
	AMatrix * temporary = new CDense(this->matrix_array, "temp", this->rows, this->cols);
	temporary->GEM(false);
	if (temporary->GetColumns() != temporary->GetRows()) {
		delete temporary;
		cout << "Can not calculate determinant of non square matrix." << endl;
		return DBL_MIN;
	};
	for (int r = 0; r < temporary->GetRows(); ++r) {
		determinant = determinant * temporary->At(r, r);
	};
	delete temporary;
	return determinant;
}