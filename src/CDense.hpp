//
// Created by jantosovic on 5/08/18.
//

#include "AMatrix.hpp"
#include <vector>
using namespace std;

class CDense : public AMatrix {
public:
	/** 
	* Constructor function for CDense object
	* @param matrix - 2d vector of data
	* @param title - name of Matrix being created
	* @param rows - number of rows of new matrix
	* @param cols - number of columns of new matrix
	*/
	CDense(vector< vector<double> > & matrix, string title, int rows, int cols);
	// Destructor
	~CDense();
	/**
	* Returns number from position in matrix
	* @param x
	* @param y
	* @return Number from array at position [x;y]
	*/
	double At(int x, int y) const override;
	/**
	* Transpone matrix function
	* @param title - title of transposed matrix
	* @return transponed matrix
	*/
	AMatrix * Transpose(const string & title) const override;
	/**
	* Function for Gaussian Elimination of matrix
	* @param verbose - flag for printing steps of GEM
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
	* Data structure for dense matrix
	* We are storing dense matrix as 2d vector
	*/
	vector< vector<double> > matrix_array;
};
