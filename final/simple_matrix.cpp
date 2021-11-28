#include <iostream>
#include <vector>
#include <chrono>
using namespace std::chrono;

using namespace std;

class matrix {
    private:
    vector<vector<double>> A;
    public:
     // left public for ease of computations

    //CONSTRUCTOR
    matrix(vector<vector<double>> matrix) {
        A = matrix;
    }
    matrix(int rows,int cols,double num) { //initializes matrix to num with m rows and n cols
        vector<double> nums;
        for(int i = 0; i < cols; i++) {
            nums.push_back(num);
        }
        for(int i = 0; i < rows; i++) {
            A.push_back(nums);
        }
    }

    int nrows() {
        return A.size();
    }

    int ncols() {
        return A[0].size();
    }

    double getVal(int row,int col) {
        return A[row][col];
    }

    void setVal(int row, int col, double num) {
        A[row][col] = num;
    }

    void print() {
        for(int i = 0; i < nrows(); i++) {
            for(int j = 0; j < ncols(); j++) {
                cout << getVal(i,j) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    matrix simple_product(matrix B) { // Simple, computationally expensive way to multiple matrices. A.simple_product(B) = A*B. Solves Exercise 60.1.
        matrix C(nrows(), B.ncols(), 0); //Allocates size of solution matrix C
        for(int i = 0; i < nrows(); i++) {
            for(int j = 0; j < B.ncols(); j++) {
                double sum = 0;
                for (int k = 0; k < ncols(); k++) {
                    sum += getVal(i,k) * B.getVal(k,j);
                }
                C.setVal(i,j,sum);
            }
        }
        return C;
    }

    // Exercise 60.1
    matrix simple_product_variant(matrix B) { // Simple, computationally expensive way to multiple matrices. A.simple_product(B) = A*B. Solves Exercise 60.1.
        matrix C(nrows(), B.ncols(), 0); //Allocates size of solution matrix C
        for(int i = 0; i < B.ncols(); i++) {
            for(int j = 0; j < B.nrows(); j++) {
                double sum = 0;
                for (int k = 0; k < B.nrows(); k++) {
                    sum += getVal(i,k) * B.getVal(k,j);
                }
                C.setVal(i,j,sum);
            }
        }
        return C;
    }
};

int main() {
    matrix A({{1,2,3},{4,5,6}});
    A.print();
    matrix B({{1,2},{3,4},{5,6}});
    B.print();
    // time product function
    auto start = high_resolution_clock::now();
        matrix C = A.simple_product_variant(B); // call function
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    C.print();
}