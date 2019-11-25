//
// Created by jantosovic on 3/24/18.
//

#include<string>

using namespace std;

#ifndef AMatrix_H
#define AMatrix_H

class AMatrix {
public:
	/**
	* Constructor for Matrix
	* @param title - gives matrix a name for reusability
	* @param rows  - number of rows of matrix
	* @param columns - number of columns of matrix
	*/
	AMatrix(const string & title, int rows, int columns);
	/**
	* Destructor for Matrix
	*/
	virtual ~AMatrix();
	/**
	* Getter for number of rows
	* @return Number of rows
	*/
	int GetRows() const;
	/**
	* Getter for number of columns
	* @return Number of columns
	*/
	int GetColumns() const;
	/**
	* Getter for title of matrix
	* @return Title of matrix
	*/
	string GetTitle() const;
	/**
	* Print function for matrix
	* @param ostream - ostream to print matrix to
	* @param matrix - matrix to print to ostream
	* @return Ostream with matrix
	*/
	friend ostream & operator<<(ostream & ostream, const AMatrix * matrix);
	/**
	* Returns number from position in matrix
	* @param x 
	* @param y
	* @return Number at position [x;y]
	*/
	virtual double At(int x, int y) const = 0;
	/**
	* Function for Addition of two matrixes
	* @param rhs - right hand side of multiplication (left is *this)
	* @param title - title of new/result matrix
	* @return summed matrix
	*/
	AMatrix * Addition(const AMatrix * rhs, const string & title)  const;
	/**
	* Function for Subtraction of two matrixes
	* @param rhs - right hand side of multiplication (left is *this)
	* @param title - title of new/result matrix
	* @return result of matrix subtraction
	*/
	AMatrix * Subtraction(const AMatrix * rhs, const string & title)  const;
	/**
	* Function for Multiplication of two matrixes
	* @param rhs - right hand side of multiplication (left is *this)
	* @param title - title of new/result matrix
	* @return result of matrix multiplication
	*/
	AMatrix * Multiplication(const AMatrix * rhs, const string & title)  const;
	/**
	* Function for Multiplication of matrix by given number
	* @param number - multiplicator of matrix (*this)
	* @param title - title of new/result matrix
	* @return multiplied matrix
	*/
	AMatrix * MultipleBy(int number, const string & title);
	/**
	* Determinant function
	* @return determinant (number)
	*/
	virtual double Determinant() = 0;
	/**
	* Inverse matrix function
	* @return inversed matrix
	*/
	AMatrix * Inverse(const string & title);
	/**
	* Transpose matrix function
	* @param title - name of new matrix
	* @return transposed matrix
	*/
	virtual AMatrix * Transpose(const string & title) const = 0;
	/**
	* Function for Gaussian Elimination of matrix
	* @param verbose - flag for printing steps of GEM
	*/
	virtual void GEM(bool verbose) = 0;
	/**
	* Function for calculating rank of matrix
	* @return rank of matrix
	*/
	virtual int Rank() = 0;
	/**
	* Function for merging two matrices
	* @param rhs - right hand side of merge operator
	* @param title - name of new matrix
	* @return merged matrix
	*/
	AMatrix * Merge(AMatrix * rhs, const string & title);
	/**
	* Function for cutting matrix from another matrix
	* @param from_x - x position to cut from
	* @param from_y - y position to cut from
	* @param width - number of cols to cut
	* @param height - number of rows to cut
	* @param title - name of new matrix
	* @return matrix
	*/
	AMatrix * Cut(int from_x, int from_y, int width, int height, const string & title);
protected:
	/**
	* Function to calculate cofactor of matrix
	* Used only when calculating inverse of matrix
	* @param row - excluded row
	* @param col - excluded col
	* @return Cofactor matrix
	*/
	AMatrix * Cofactor(int row, int col);
	/**
	* Function to calculate adjoint of matrix
	* Used only when calculating inverse of matrix
	* @return Adjoint matrix
	*/
	AMatrix * Adjoint();
	/**
	* Number of rows of matrix
	*/
	int rows;
	/**
	* Number of cols of matrix
	*/
	int cols;
	/**
	* Name of matrix
	*/
	string title;
};

#endif /* AMatrix_H */
