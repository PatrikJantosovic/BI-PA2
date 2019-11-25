//
// Created by jantosovic on 5/08/18.
//

#include "AMatrix.hpp"
#include <map>
using namespace std;

class CSparse : public AMatrix {
public:
	/**
	* Constructor function for CSparse object
	* @param matrix - map of matrix data
	* @param title - name of Matrix being created
	* @param rows - number of rows of new matrix
	* @param cols - number of columns of new matrix
	*/
	CSparse(map<pair<int, int>, double> matrix, string title, int rows, int cols);
	// Destructor
	~CSparse();
	/**
	* Returns number from position in matrix
	* @param x
	* @param y
	* @return Number from map, where key is [x;y], return 0 if not found
	*/
	double At(int x, int y) const override;
	/**
	* Transpone matrix function
	* @param title - title of transposed matrix
	* @return Transposed matrix
	*/
	AMatrix * Transpose(const string & title) const override;
	/**
	* Function for Gaussian Elimination of matrix
	* @param verbose - flag for printing steps of GEM
	* @return matrix after GEM
	*/
	void GEM(bool verbose) override;
	/**
	* Function for calculating rank of matrix
	* @return rank of matrix
	*/
	virtual int Rank() override;
	/**
	* Determinant function
	* @return determinant (number)
	*/
	virtual double Determinant() override;
private:
	/**
	* Helper function for inserting value at given position
	* 
	* @param c - index of column
	* @param r - index of row
	* @param value - value to insert
	*/
	void InsertAt(int c, int r, double value);
	/**
	* Data structure for sparse matrix
	* We are storing sparse matrix in a map of doubles, using pair of ints as keys
	*/
	map<pair<int, int> , double> matrix_array;
};
