//Compile line: icpc -I${TACC_GSL_INC} final/matrix.cpp
#include <iostream>
#include <vector>
#include <array>
//#include <..\GSL-main\include\gsl\span>
#include "gsl/gsl-lite.hpp"



using namespace std;
using gsl::span;

class Matrix {

    private:

    int m,n,lda;
    span<double> data;

    public:

    //Getters
    int getrows() { return m; }
    int getcols() { return n; }
    int getlda() { return lda; }

    //Constructors (ex. 60.3)
    Matrix(int m, int lda, int n, double *data) {
        if (lda < m) {
            cout << "Error creating matrix: LDA < m" << endl;
            throw(1);
        }

        //cout << *data << endl;

        this->m = m;
        this->lda = lda;
        this->n = n;
        this->data = span<double> (data,lda*n);

        //this->printdata();
    }

    //return element function (ex. 60.3)
    double& at(int i, int j) {
        if(i >= m || j >= n || i < 0 || j < 0) { 
            cout << "Error: index out of bounds" << endl;
            throw(1); 
        }
        //cout << data[j*lda + i] << endl;
        //this->printdata();
        return data[j*lda + i];

    }

    //for testing purposes
    void print() {
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < m; j++) {
                cout << this->at(i,j) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void printdata() {
        for(int i = 0; i < lda*n; i++) {
            cout << data[i] << " ";
        }
        cout << endl << endl;
    }
    
};

//Addition method (ex. 60.4)
Matrix addMatrices(Matrix A, Matrix B) {
    if (A.getrows() != B.getrows() || A.getcols() != B.getcols()) {
        cout << "Error using addMatrices: Matrices do no have the same dimensions" << endl;
        throw(1);
    }

    vector<double> cdata(A.getrows()*B.getrows(),0);
    //cout << cdata[0] << endl;
    for(int j = 0; j < A.getcols(); j++) {
        for(int i = 0; i < A.getrows(); i++) {
            //cout << A.at(i,j) << ", " << B.at(i,j) << endl;
            //cout << j*A.getrows() + i << endl;
            cdata[j*A.getrows() + i] = A.at(i,j) + B.at(i,j);
            //cout << cdata[0] << endl;
        }
    }
    //cout << cdata[0] << endl;
    Matrix C(A.getrows(),A.getrows(),A.getcols(),cdata.data());
    C.printdata();
    return C;
    // Matrix(A.getrows(),A.getrows(),A.getcols(),cdata.data());

}

int main() {
    int m = 2;
    int lda = 3;
    int n = 2;
    //vector<double> one_data(lda*n,1);
    vector<double> data1 = {1,3,5,2,4,6};
    vector<double> data2 = {1,2,3,4};
    vector<double> data3 = {2,2,3,4,5,6,7,8,9,10,11,12};
    vector<double> data4 = {2,2,3,4,5,6,7,8,9};
    //cout << one_data[0] << endl;
    //cout << one_data.data() << endl;
    Matrix m1(3,4,3,data3.data());
    Matrix m2(3,3,3,data4.data());
    m1.print();
    m2.print();
    Matrix m3 = addMatrices(m1,m2);
    m3.printdata();
    //m3.at(0,0);
    //m3.printdata();
    /* METHOD TO CHANGE ELEMENTS IN A MATRIX
    double& x = mat.at(1,1);
    x = 5;
    cout << mat.at(1,1) << endl;
    */
    return 0;
}
