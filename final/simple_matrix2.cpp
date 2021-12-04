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

    matrix simple_addition(matrix B) { // Simple, computationally expensive way to add matrices. A.simple_product(B) = A*B. Solves Exercise 60.1.
        matrix C(nrows(), B.ncols(), 0); //Allocates size of solution matrix C
        for(int i = 0; i < nrows(); i++) {
            for(int j = 0; j < B.ncols(); j++) {
                double sum = 0;
                for (int k = 0; k < ncols(); k++) {
                    sum = getVal(i,k) + B.getVal(k,j);
                }
                C.setVal(i,j,sum);
            }
        }
        return C;
    }
};

int main() {
    double g = 9.81; // gravity, [kg/m*s^2]
    double mu = 0.0001; // dynamic viscosity of water

    // Test adding 2 by 2 matrices
    cout << "Computing Matrix Sum. Result is: " << endl;
    auto start = high_resolution_clock::now(); // time product function
        matrix m1({{400*mu,0},{0,3.5*mu}});
        matrix m2({{g,0},{0,g}});
        matrix m3 = m1.simple_addition(m2); // call function
        m3.print();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    // Test adding 3 by 3 matrices
    cout << "Computing Matrix Sum. Result is: " << endl;
    auto start1 = high_resolution_clock::now(); // time product function
        matrix m4({{400*mu,0.,3001*mu},{0,3.5*mu,0.75*mu},{3001*mu,.75*mu,0}});
        matrix m5({{g,0,0},{0,g,0},{0,0,g}});
        matrix m6 = m4.simple_addition(m5); // call function
        m6.print();
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    cout << "Time taken by function: "
         << duration1.count() << " microseconds" << endl;

    // Test adding 4 by 3 matrices
    cout << "Computing Matrix Sum. Result is: " << endl;
    auto start2 = high_resolution_clock::now(); // time product function
        matrix m7({{400*mu,0.,3001*mu},{0,3.5*mu,0.75*mu},
                   {3001*mu,.75*mu,0}, {400*mu, -0.5, 3001*mu}});
        matrix m8({{g,0,0},{0,g,0},{0,0,g}, {g,0,0}});
        matrix m9 = m7.simple_addition(m8); // call function
        m9.print();
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout << "Time taken by function: "
         << duration2.count() << " microseconds" << endl;

    // Test adding 6 by 3 matrices
    cout << "Computing Matrix Sum. Result is: " << endl;
    auto start3 = high_resolution_clock::now(); // time product function
        matrix m10({{400*mu,0.,3001*mu},{0,3.5*mu,0.75*mu},
                   {3001*mu,.75*mu,0}, {400*mu, -0.5, 3001*mu},
                   {-0.5, 2*mu, 0},{3001*mu, 0, 0}});
        matrix m11({{g,0,0},{0,g,0},{0,0,g}, {g,0,0},{0,g,0},{0,0,g}});
        matrix m12 = m10.simple_addition(m11); // call function
        m12.print();
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop3 - start3);
    cout << "Time taken by function: "
         << duration2.count() << " microseconds" << endl;
}