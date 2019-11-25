//
// Created by jantosovic on 5/08/18.
//

#include "AMatrix.hpp"
#include <vector>
using namespace std;

class CData {
public:
	/**
	* Constructor function for CData
	* @param rows - number of rows of our 2d array
	* @param cols - number of columns of our 2d array
	*/
	CData(int rows, int cols);
	// Destructor
	~CData();
	/**
	* Function creates right kind of Matrix due to its data
	* @param title - name of new matrix
	* @return instance of Matrix
	*/
	AMatrix * BuildFromData(string title);
	/**
	* Function sets the value in matrix
	* @param x - coordinate x
	* @param y - coordinate y
	* @param value - value to be set at position [x;y]
	*/
	void Set(int x, int y, double value);
private:
	vector< vector <double> > matrix_array;

};
