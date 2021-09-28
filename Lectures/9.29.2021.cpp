/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-9 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** matrix.cxx : example of matrix class
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <vector>
using std::vector;

class matrix {
private:
  vector<vector<double>> elements;
public:
  matrix(int m,int n) {
    elements =
      vector<vector<double>>(m,vector<double>(n));
  }
  void set(int i,int j,double v) {
    elements.at(i).at(j) = v;
  };
  double get(int i,int j) {
    return elements.at(i).at(j);
  };
  int rows() {
    return elements.size();
  }
  int cols() {
    return elements[1].size();
  }
  void set(double v) {
    for(int i = 0; i < rows(); i++) {
      for(int j = 0; j < cols(); j++) {
        elements[i][j] = v;
      }
    }
  }
  double totalsum() {
    double sum = 0;
    for(int i = 0; i < rows(); i++) {
      for(int j = 0; j < cols(); j++) {
        sum += get(i,j);
      }
    }
    return sum;
  }
};

int main() {

  cout << "SetGet\n";
  matrix A(2,5);
  A.set(1,2,3.14);

  cout << A.rows() << endl;
  cout << A.cols() << endl;
  cout << A.get(1,2) << endl;
  cout << "setget\n";
  
  cout << "Sum\n";
  A.set(3.);
  cout << "Sum of elements: " << A.totalsum() << endl;
  cout << "sum\n";

  return 0;
}
