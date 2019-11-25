//
// Created by jantosovic on 3/23/18.
//
#include <iostream>
#include <iomanip>
#include <string>
#include "CCalculator.hpp"

using namespace std;

int main (void){
    string command;
	cout.precision(2);
	cout.setf(ios::fixed);
	cout << "To print this help type: help  , to quit calculator print: quit" << endl;
	cout << "To create matrix of width x and height y with name N: scan:N[x,y]" << endl;
	cout << "Program than waits for x*y numbers, you must supply them by one (enter separated) ... " << endl;
	cout << "To sum two matrices with names N and M to matrix K: K=N+M" << endl;
	cout << "To substract matrix with name M from name N to matrix K: K=N-M" << endl;
	cout << "To multiply two matrices with names N and M to matrix K: K=N*M" << endl;
	cout << "To multiply matrix with name N by number x to matrix K: K=x*N" << endl;
	cout << "To transpose matrix with name N write:K=transpose(N)" << endl;
	cout << "To merge two matrices with name N and M in matrix K: K=M||N" << endl;
	cout << "To cut x columns and y rows from matrix N to matrix K from position (k,l): K[x,y]=N\\(n,l)" << endl;
	cout << "To find inverse matrix of matrix N: K=inverse(N)" << endl;
	cout << "To calculate determinant of matrix N: det(N)" << endl;
	cout << "To calculate rank of matrix N: rank(N)" << endl;
	cout << "To GEM the matrix N: GEM(N)verbose=N" << endl;
	cout << "To see the steps of GEM use verbose=Y: GEM(N)verbose=Y" << endl;
	cout << "To print the matrix N write: print(N)" << endl;
    CCalculator calculator;
    calculator.Run();
    return 1;
}