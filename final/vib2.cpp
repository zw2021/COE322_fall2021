//Compile line: icpc -I${TACC_GSL_INC} final/vib2.cpp
#include <iostream>
#include <vector>
#include <array>
#include "gsl/gsl-lite.hpp"

#include <chrono>
using namespace std::chrono;

#define INDEX(i,j,lda) (j)*(lda) + (i)


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

        this->m = m;
        this->lda = lda;
        this->n = n;
        this->data = span<double> (data,lda*n);

    }

    //return element function (ex. 60.3)
    double& at(int i, int j) {
        if(i >= m || j >= n || i < 0 || j < 0) { 
            cout << "Error: index out of bounds" << endl;
            throw(1); 
        }
        return data[j*lda + i];

    }
    auto get_double_data() {
        double *adata;
        adata = data.data();
        return adata;
    }
    //Addition method (ex. 60.4)
    void addMatrices(Matrix& B, Matrix& out) {
        if (this->getrows() != B.getrows() || this->getcols() != B.getcols()) {
            cout << "Error using addMatrices: Matrices do no have the same dimensions" << endl;
            throw(1);
        }

        auto adata = this->get_double_data();
        auto bdata = B.get_double_data();
        auto cdata = out.get_double_data();
        for(int j = 0; j < this->getcols(); j++) {
            for(int i = 0; i < this->getrows(); i++) {
                #ifdef DEBUG
                    cdata[INDEX(j,this->getrows(),i)] = this->at(i,j) + B.at(i,j);
                #else
                    cdata[INDEX(j,this->getrows(),i)] = adata[INDEX(j,this->getlda(),i)] + bdata[INDEX(j,B.getlda(),i)];
                #endif
            }
        }
    }


    //Submatrices support (ex. 60.6)
    Matrix Left(int j) {
        return Matrix(this->m,this->lda,j,this->get_double_data());
    }
    Matrix Right(int j) {
        return Matrix(this->m,this->lda,n-j,this->get_double_data() + lda*j);
    }
    Matrix Top(int i) {
        return Matrix(i,this->lda,this->n,this->get_double_data());
    }
    Matrix Bot(int i) {
        return Matrix(m-i,this->lda,this->n,this->get_double_data() + i);
    }

    //Multiplication functions
    void MatMult(Matrix& other, Matrix& out) {
        auto adata = this->get_double_data();
        auto bdata = other.get_double_data();
        auto cdata = out.get_double_data();
        for(int i = 0; i < this->m; i++) {
            for(int j = 0; j < other.getcols(); j++) {
                for (int k = 0; k < this->n; k++) {
                    #ifdef DEBUG
                        out.at(i,j) += this->at(i,k) * other.at(k,j);
                    #else
                        cdata[INDEX(i,j,out.getlda())] += adata[INDEX(i,k,this->lda)] * bdata[INDEX(k,j,other.getlda())];
                    #endif
                }
            }
        }
        return;
    }


    void BlockedMatMult(Matrix& other, Matrix& out) {

        Matrix atl = this->Left(this->getcols()/2).Top(this->getrows()/2);
        Matrix atr = this->Right(this->getcols()/2).Top(this->getrows()/2);
        Matrix abl = this->Left(this->getcols()/2).Bot(this->getrows()/2);
        Matrix abr = this->Right(this->getcols()/2).Bot(this->getrows()/2);

        Matrix btl = other.Left(other.getcols()/2).Top(other.getrows()/2);
        Matrix btr = other.Right(other.getcols()/2).Top(other.getrows()/2);
        Matrix bbl = other.Left(other.getcols()/2).Bot(other.getrows()/2);
        Matrix bbr = other.Right(other.getcols()/2).Bot(other.getrows()/2);

        Matrix otl = out.Left(out.getcols()/2).Top(out.getrows()/2);
        Matrix otr = out.Right(out.getcols()/2).Top(out.getrows()/2);
        Matrix obl = out.Left(out.getcols()/2).Bot(out.getrows()/2);
        Matrix obr = out.Right(out.getcols()/2).Bot(out.getrows()/2);

        atl.MatMult(btl,otl);
        atr.MatMult(bbl,otl);

        atl.MatMult(btr,otr);
        atr.MatMult(bbr,otr);

        abl.MatMult(btl,obl);
        abr.MatMult(bbl,obl);

        abl.MatMult(btr,obr);
        abr.MatMult(bbr,obr);
                
    }

    //Ex 60.7
    void RecursiveMatMult(Matrix& other, Matrix& out) {

        if(this->getrows() < 4 && this->getcols() < 4 && other.getrows() < 4 && other.getcols() < 4) {
            this->MatMult(other,out);
        }
        else {
            Matrix atl = this->Left(this->getcols()/2).Top(this->getrows()/2);
            Matrix atr = this->Right(this->getcols()/2).Top(this->getrows()/2);
            Matrix abl = this->Left(this->getcols()/2).Bot(this->getrows()/2);
            Matrix abr = this->Right(this->getcols()/2).Bot(this->getrows()/2);

            Matrix btl = other.Left(other.getcols()/2).Top(other.getrows()/2);
            Matrix btr = other.Right(other.getcols()/2).Top(other.getrows()/2);
            Matrix bbl = other.Left(other.getcols()/2).Bot(other.getrows()/2);
            Matrix bbr = other.Right(other.getcols()/2).Bot(other.getrows()/2);

            Matrix otl = out.Left(out.getcols()/2).Top(out.getrows()/2);
            Matrix otr = out.Right(out.getcols()/2).Top(out.getrows()/2);
            Matrix obl = out.Left(out.getcols()/2).Bot(out.getrows()/2);
            Matrix obr = out.Right(out.getcols()/2).Bot(out.getrows()/2);

            atl.RecursiveMatMult(btl,otl);
            atr.RecursiveMatMult(bbl,otl);

            atl.RecursiveMatMult(btr,otr);
            atr.RecursiveMatMult(bbr,otr);

            abl.RecursiveMatMult(btl,obl);
            abr.RecursiveMatMult(bbl,obl);

            abl.RecursiveMatMult(btr,obr);
            abr.RecursiveMatMult(bbr,obr);
        }
    }

    //for testing purposes
    void print() {
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
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



int main() {

    double g = 9.81; // gravity, [kg/m*s^2]
    double mu = 0.0001; // dynamic viscosity of water

    vector<double> data1 = {400*mu,0,3001*mu, 400*mu,-0.5,0,3001*mu,
                            0,3.5*mu, .75*mu,-0.5,2*mu,0,
                            3001*mu,.75*mu,0,3001*mu, 0, 0};//Shear Matrix, water.
    vector<double> data2 = {g,0,0,g,0,0,
                            0,g,0,0,g,0,
                            0,0,g,0,0,g};// Body Forces Matrix
    vector<double> data3 = {g,0,0,0,0,0,
                            0,0,g,0,0,0,
                            0,0,0,0,0,g}; // Dummy Matrix

     // Test adding 2 by 2 matrices

    auto start = high_resolution_clock::now();    // time product function
        Matrix m1(2,6,2,data1.data());
        Matrix m2(2,6,2,data2.data());
        Matrix m3(2,6,2,data3.data());
        m3.addMatrices(m1,m2);
        m2.print();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
    << duration.count() << " microseconds" << endl;

    // Test adding 3 by 3 matrices
        auto start1 = high_resolution_clock::now();    // time product function
        Matrix m4(3,6,3,data1.data());
        Matrix m5(3,6,3,data2.data());
        Matrix m6(3,6,3,data3.data());
        m6.addMatrices(m4,m5);
        m5.print();
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
    << duration.count() << " microseconds" << endl;

    // Test adding 4 by 4 matrices

    Matrix m7(4,6,4,data1.data());
    Matrix m8(4,6,4,data2.data());
    Matrix m9(4,6,4,data3.data());

    // Test adding 6 by 6 matrices
    Matrix m10(6,6,6,data1.data());
    Matrix m11(6,6,6,data2.data());
    Matrix m12(6,6,6,data3.data());
    // Tests varying dynamic viscosity at different orders of magnitude
    /*
    vector<double> data1 = {4,0,0, 0,0.0035,0,0,0};//Shear Matrix, water.
    vector<double> data2 = {g,0,0,0,g,0,0,0,g};// Body Forces Matrix 
    vector<double> data3 = {g,0,0,0,0,0,0,0,g}; // Dummy Matrix
    Matrix m1(2,3,2,data1.data());
    Matrix m2(2,3,2,data2.data());
    Matrix m3(2,3,2,data3.data());
    // Test cases for a known viscosity. In this case, we're using water
    
    m1.print();
    m2.print();

    m3.addMatrices(m1,m2);
    m2.print();

   // Test case with varying arbitrary viscosity values within orders of magnitude
   vector<double> mu = {0, 0.0001, 0.001, 0.01, 0.1, 1, 10};// Vary viscosity within order of magnitudes
   for (int ii = 0; ii< mu.size(); ii++){
    vector<double> data5 = {400*mu[ii],0,0, 0,7*mu[ii]*0.5,0,0,0};//Shear Matrix
    Matrix m5(2,3,2,data5.data());
    m3.addMatrices(m1,m5);
    m5.print();
     */
}
    return 0;
}
