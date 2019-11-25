//
// Created by jantosovic on 3/23/18.
//

#include <map>
#include "AMatrix.hpp"
using namespace std;

class CCalculator{
public:
    // Constructor
    CCalculator();
    // Destructor
    ~CCalculator();
    /** 
	* Print all matrices in calculator
	*/
    void Print() const;
	/**
	* Print help text for calculator usage
	*/
	void PrintHelp() const;
    /**
	* Run one instance of calculator
	*/
    void Run();
private:
	/**
	* Function to check if matrix exists in database
	* @param title - name of matrix
	* @return - true for exists, false for not existing
	*/
	bool MatrixExists(const string & title) const;
	/**
	* Database of matrices that belong to instance of calculator
	*/
    map<string, AMatrix*> matrixList;

};
