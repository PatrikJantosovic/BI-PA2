//
// Created by jantosovic on 5/08/18.
//
#include "CSparse.hpp"
#include<iostream>
#include<cfloat>
#include<cmath>

using namespace std;

CSparse::CSparse(map< pair<int, int>, double > matrix, string title, int rows, int cols)
: AMatrix(title, rows, cols) {
	this->matrix_array = matrix;
}

CSparse::~CSparse() {}

double CSparse::At(int x, int y) const{
	if (x >= this->cols || y >= this->rows) {
		throw invalid_argument("Out of bound");
	};
	auto it = this->matrix_array.find(make_pair(x, y));
	if (it == this->matrix_array.end()) {
		return 0;
	};
	return it->second;
}

AMatrix * CSparse::Transpose(const string & title) const {
	map<pair<int, int>, double> transponed_matrix;
	for (auto it : this->matrix_array) {
		transponed_matrix[make_pair(it.first.second, it.first.first)] = it.second;
	};
	return new CSparse(transponed_matrix, title, this->cols, this->rows);
}

void CSparse::GEM(bool verbose) {
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
			this->InsertAt(j,max_row, this->At(j, i));
			this->InsertAt(j, i, tmp);
		}

		/*Actual GEM happening here*/
		for (int j = i + 1; j < this->rows; ++j) {
			double param = this->At(i, j) / this->At(i, i);
			for (int k = i; k < this->cols; ++k) {
				if (i == k) {
					this->InsertAt(k, j, 0);
				}
				else {
					this->InsertAt(k, j, this->At(k, j) - param*this->At(k, i));
				}
			}
		}
		if (verbose)
			cout << this << endl;
	}
}

int CSparse::Rank() {
	if (this->rows == 0) return 0;
	AMatrix * temporary = new CSparse(this->matrix_array, "temp", this->rows, this->cols);
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

double CSparse::Determinant() {
	double determinant = 1;
	/*Transform to Upper triangular Form and multiply the diagonal*/
	AMatrix * temporary = new CSparse(this->matrix_array, "temp", this->rows, this->cols);
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

void CSparse::InsertAt(int c, int r, double value) {
	if (value == 0) return;
	if (this->At(c, r) == 0) {
		this->matrix_array.insert(make_pair(make_pair(c, r), value));
	}
	else {
		this->matrix_array[make_pair(c, r)] = value;
	};
}