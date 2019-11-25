//
// Created by jantosovic on 3/23/18.
//
#include <iostream>
#include<regex>
#include<iterator>
#include<cfloat>
#include "CCalculator.hpp"
#include "CData.hpp"

using namespace std;

CCalculator::CCalculator() {

}

CCalculator::~CCalculator() {
	for (auto & it : this->matrixList) {
		delete it.second;
	}
}

void CCalculator::Print() const {
    if (matrixList.empty() == true){
        cout << "Nothing to print. You can add a matrix with \"scan\" command." << endl;
    }
    for (auto i : matrixList){
        cout << i.second->GetTitle() << " [ " << i.second->GetRows() << " ; " << i.second->GetColumns() << " ] " << endl;
        cout << i.second;
        cout << "-------------------------------------" << endl;
    }
}

void CCalculator::PrintHelp() const {
	cout << "To start the calculator: init" << endl;
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
}

bool CommandOk(string command, regex rx) {
	auto it_begin = sregex_iterator(command.begin(), command.end(), rx);
	auto it_end = sregex_iterator();
	if (distance(it_begin, it_end) != 1) {
		return false;
	};
	return true;
}

string GetTitle(string command, int position) {
	return command.substr(position, 1);
}

int GetNumber(string command, int position) {
	string number = "";
	for (char c : command.substr(position)) {
		if (!isdigit(c))
			break;
		number += c;
	}
	return stoi(number);
}

bool CCalculator::MatrixExists(const string & title) const {
	if (this->matrixList.find(title) != this->matrixList.end()) {
		cout << "Matrix with this name already exists." << endl;
		return true;
	}
	return false;
}

void CCalculator::Run() {
    while(1){
        string command = "";
        cin >> command;
        if(command.find("scan")!=string::npos){
            //new matrix
			regex scan_regex("scan\\:[a-zA-Z]\\[[0-9]\\,[0-9]\\]");
			if (CommandOk(command, scan_regex) == false) {
				cout << "Command scan failed." << endl;
				continue;
			};
			string title = GetTitle(command, 5);
			if (this->MatrixExists(title)) continue;
			int cols = GetNumber(command, 7);
			int rows = GetNumber(command, command.find(",")+1);
			cout << "Enter the numbers of matrix enter separated please:" << endl;
			CData new_matrix(rows, cols);
			for (int r = 0; r < rows; ++r) {
				for (int c = 0; c < cols; ++c) {
					double value = 0;
					cin >> value;
					new_matrix.Set(c, r, value);
				}
			}
			AMatrix * matrix = new_matrix.BuildFromData(title);
			this->matrixList.insert(make_pair(title, matrix));
        }
        else if(command.find("+")!=string::npos){
            //sum of two matrices
			regex sum_regex("[a-zA-Z]\\=[a-zA-Z]\\+[a-zA-Z]");
			if (CommandOk(command, sum_regex) == false) {
				cout << "Command sum failed." << endl;
				continue;
			};
			string result = GetTitle(command, 0);
			if (this->MatrixExists(result)) continue;
			string left_operand = GetTitle(command,2);
			string right_operand = GetTitle(command,4);
			auto left = this->matrixList.find(left_operand);
			auto right = this->matrixList.find(right_operand);
			if (left == this->matrixList.end() || right == this->matrixList.end()) {
				cout << "Matrix not found." << endl;
				continue;
			};
			AMatrix * result_matrix = left->second->Addition(right->second, result);
			if (result_matrix != nullptr) {
				cout << result_matrix << endl;
				this->matrixList[result] = result_matrix;
			}
        }
        else if(command.find("-")!=string::npos){
            //substract of two matrices
			regex sub_regex("[a-zA-Z]\\=[a-zA-Z]\\-[a-zA-Z]");
			if (CommandOk(command, sub_regex) == false) {
				cout << "Command minus failed." << endl;
				continue;
			};
			string result = GetTitle(command,0);
			if (this->MatrixExists(result)) continue;
			string left_operand = GetTitle(command,2);
			string right_operand = GetTitle(command,4);
			auto left = this->matrixList.find(left_operand);
			auto right = this->matrixList.find(right_operand);
			if (left == this->matrixList.end() || right == this->matrixList.end()) {
				cout << "Matrix not found." << endl;
				continue;
			};
			AMatrix * result_matrix = left->second->Subtraction(right->second, result);
			if (result_matrix != nullptr) {
				cout << result_matrix << endl;
				this->matrixList[result] = result_matrix;
			}
        }
        else if(command.find("*")!=string::npos){
            //multiplicating matrix by matrix
			regex matrixbymatrix_regex("[a-zA-Z]\\=[a-zA-Z]\\*[a-zA-Z]");
			regex matrixbynumber_regex("[a-zA-Z]\\=[0-9]+\\*[a-zA-Z]");
			AMatrix * result_matrix;
			string result = GetTitle(command, 0);
			if (this->MatrixExists(result)) continue;
			string right_operand = GetTitle(command, 4);
			if (CommandOk(command, matrixbymatrix_regex)) {
				// we are doing matrix by matrix
				string left_operand = GetTitle(command, 2);
				auto left = this->matrixList.find(left_operand);
				auto right = this->matrixList.find(right_operand);
				if (left == this->matrixList.end() || right == this->matrixList.end()) {
					cout << "Matrix not found." << endl;
					continue;
				};
				result_matrix = left->second->Multiplication(right->second, result);
			}
			else if (CommandOk(command, matrixbynumber_regex)) {
			    // we are doing matrix by number
				int left = GetNumber(command, 2);
				auto right = this->matrixList.find(right_operand);
				if (right == this->matrixList.end()) {
					cout << "Matrix not found." << endl;
					continue;
				};
				result_matrix = right->second->MultipleBy(left, result);
			}
			else {
				cout << "Command multiply failed." << endl;
				continue;
			};
			if (result_matrix != nullptr) {
				cout << result_matrix << endl;
				this->matrixList[result] = result_matrix;
			}
        }
        else if(command.find("transpose")!=string::npos){
            //transpose matrix
			regex transpose_regex("[a-zA-Z]\\=transpose\\([a-zA-Z]\\)");
			if (CommandOk(command, transpose_regex)==false) {
				cout << "Command transpose failed." << endl;
				continue;
			};
			string result = GetTitle(command,0);
			if (this->MatrixExists(result)) continue;
			string operand = GetTitle(command, 12);
			auto matrix = this->matrixList.find(operand);
			if (matrix == this->matrixList.end()) {
				cout << "Matrix not found." << endl;
				continue;
			};
			AMatrix * result_matrix = matrix->second->Transpose(result);
			cout << result_matrix << endl;
			this->matrixList[result] = result_matrix;
        }
        else if(command.find("||")!=string::npos){
            //merge matrix
			regex sub_regex("[a-zA-Z]\\=[a-zA-Z]\\|\\|[a-zA-Z]");
			if (CommandOk(command, sub_regex) == false) {
				cout << "Command merge failed." << endl;
				continue;
			};
			string result = GetTitle(command, 0);
			if (this->MatrixExists(result)) continue;
			string left_operand = GetTitle(command, 2);
			string right_operand = GetTitle(command, 5);
			auto left = this->matrixList.find(left_operand);
			auto right = this->matrixList.find(right_operand);
			if (left == this->matrixList.end() || right == this->matrixList.end()) {
				cout << "Matrix not found." << endl;
				continue;
			};
			AMatrix * result_matrix = left->second->Merge(right->second, result);
			if (result_matrix != nullptr) {
				cout << result_matrix << endl;
				this->matrixList[result] = result_matrix;
			}
        }
        else if(command.find("\\")!=string::npos){
            //cut part of matrix
			regex sub_regex("[a-zA-Z]\\[[0-9]+\\,[0-9]+\\]\\=[a-zA-Z]\\\\\\([0-9]+\\,[0-9]+\\)");
			if (CommandOk(command, sub_regex) == false) {
				cout << "Command cut failed." << endl;
				continue;
			};
			string result = GetTitle(command, 0);
			if (this->MatrixExists(result)) continue;
			int cut_rows = GetNumber(command, 2);
			int cut_cols = GetNumber(command, 4);
			string left_operand = GetTitle(command, 7);
			int from_y = GetNumber(command, 10);
			int from_x = GetNumber(command, 12);
			auto left = this->matrixList.find(left_operand);
			if (left == this->matrixList.end()) {
				cout << "Matrix not found." << endl;
				continue;
			};
			AMatrix * result_matrix = left->second->Cut(from_x, from_y, cut_cols, cut_rows, result);
			if (result_matrix != nullptr) {
				cout << result_matrix << endl;
				this->matrixList[result] = result_matrix;
			}
        }
        else if(command.find("inverse")!=string::npos){
            //inverse matrix
			regex inverse_regex("[a-zA-Z]\\=inverse\\([a-zA-Z]\\)");
			if (CommandOk(command, inverse_regex)==false) {
				cout << "Command inverse failed." << endl;
				continue;
			};
			string result = GetTitle(command, 0);
			if (this->MatrixExists(result)) continue;
			string operand = GetTitle(command, 10);
			auto matrix = this->matrixList.find(operand);
			if (matrix == this->matrixList.end()) {
				cout << "Matrix not found." << endl;
				continue;
			};
			AMatrix * result_matrix = (*matrix).second->Inverse(result);
			if (result_matrix != nullptr) {
				cout << result_matrix << endl;
				this->matrixList[result] = result_matrix;
			}
        }
        else if(command.find("det")!=string::npos){
            //calculate determinant
			regex determinant_regex("det\\([a-zA-Z]\\)");
			if (CommandOk(command, determinant_regex) == false) {
				cout << "Command determinant failed." << endl;
				continue;
			};
			double result = 0;
			string operand = GetTitle(command, 4);
			auto matrix = this->matrixList.find(operand);
			if (matrix == this->matrixList.end()) {
				cout << "Matrix not found." << endl;
				continue;
			};
			result = matrix->second->Determinant();
			if (result == DBL_MIN) continue;
			cout << "Determinant is: " <<  result << endl;
        }
        else if(command.find("rank")!=string::npos){
            //calculate rank of matrix
			regex rank_regex("rank\\([a-zA-Z]\\)");
			if (CommandOk(command, rank_regex)==false) {
				cout << "Command rank failed." << endl;
				continue;
			};
			int result = 0;
			string operand = GetTitle(command, 5);
			auto matrix = this->matrixList.find(operand);
			if (matrix == this->matrixList.end()) {
				cout << "Matrix not found." << endl;
				continue;
			};
			result = matrix->second->Rank();
			cout << "Rank is: " << result << endl;
        }
        else if(command.find("GEM")!=string::npos){
            //GEM the matrix
			regex gem_regex("GEM\\([a-zA-Z]\\)verbose=[Y,N]");
			if (CommandOk(command, gem_regex) == false) {
				cout << "Command GEM failed." << endl;
				continue;
			};
			string operand = GetTitle(command, 4);
			string verbose = GetTitle(command, 14);
			auto matrix = this->matrixList.find(operand);
			if (matrix == this->matrixList.end()) {
				cout << "Matrix not found." << endl;
				continue;
			};
			matrix->second->GEM(verbose=="Y");
			cout << "Result:" << endl;
			cout << matrix->second << endl;
        }
        else if(command.find("print")!=string::npos) {
            //print the matrix
			regex print_regex("print\\([a-zA-Z]\\)");
			if (CommandOk(command, print_regex) == false) {
				cout << "Command print failed." << endl;
				continue;
			};
			string operand = GetTitle(command,6);
			auto matrix = this->matrixList.find(operand);
			if (matrix == this->matrixList.end()) {
				cout << "Matrix not found." << endl;
				continue;
			};
			cout << matrix->second << endl;
        }
		else if (command.find("help") != string::npos) {
			this->PrintHelp();
		}
        else if(command.find("quit")!=string::npos){
            // quit the calculator
            break;
        }
        else{
            cout << "Sorry, command not found." << endl;
        }
    }
}