//
// Created by huang on 9/29/2021.
//

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

#include <numeric>

class matrix {
    private:
        vector<vector<double>> elements;
    public:
        matrix(int m,int n) {
            elements = vector<vector<double>>(m,vector<double>(n));
        }
        void set(int i,int j,double v) {
            elements.at(i).at(j) = v;
        };
        double totalsum(){
            double sum_of_elems;
            for( auto &row : elements) // range into vector of vectors
                for( auto col : row) // range into element of vector
                    sum_of_elems += col; // add
                    return sum_of_elems;
}
        double get(int i,int j) {
            return elements.at(i).at(j);
        };
};

int main() {

    cout << "SetGet\n";
    matrix A(2,5);
    A.set(1,2,3.14);
    cout << A.get(1,2) << endl;
    cout << "setget\n";

    cout << "Sum\n";
    A.set(1, 2, 3.);
    A.set(1,3, 4.);
    A.set(1,4,1);
    cout << "Sum of elements: " << A.totalsum() << endl;
    cout << "sum\n";

return 0;
}
