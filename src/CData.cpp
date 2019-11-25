//
// Created by jantosovic on 5/08/18.
//
#include "CData.hpp"
#include "CDense.hpp"
#include "CSparse.hpp"
#include<map>
#include <cmath>
#include<iostream>

using namespace std;

CData::CData(int rows, int cols) {
	vector<vector<double>> matrix(cols, vector<double>(rows, 0));
	this->matrix_array = matrix;
}

CData::~CData() {}

AMatrix * CData::BuildFromData(string title) {
	map<pair<int, int>, double> sparse_matrix;
	int cols = this->matrix_array.size();
	int rows = this->matrix_array[0].size();
	int zeroCount = 0;
	int totalCount = rows * cols;
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			if (this->matrix_array[c][r] == 0) {
				++zeroCount;
			}
			else {
				sparse_matrix.insert(make_pair(make_pair(c, r),this->matrix_array[c][r]));
			};
		}
	}
	/* Decide which type of matrix is better
	*  2 ints + double needed for one record in sparse means 
	*  there needs to be more then 2/3 nulls to be effective */
	AMatrix * result_matrix;
	if (floor(2*totalCount / 3) < zeroCount) {
		result_matrix = new CSparse(sparse_matrix, title, rows, cols);
	}
	else {
		result_matrix = new CDense(this->matrix_array, title, rows, cols);
	};
	return result_matrix;
}

void CData::Set(int x, int y, double value) {
	this->matrix_array[x][y] = value;
}

