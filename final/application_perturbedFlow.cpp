//Compile line: icpc -I${TACC_GSL_INC} application_perturbedFlow.cpp
#include <iostream>
#include <vector>
#include <array>
#include "gsl/gsl-lite.hpp"
#include "input_forKnownVelocityProfile.h"
#include "postProcessing.h"
#include <algorithm>


using std::fill;


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

    // double LDA = 50; // LDA, input for input calculator has to be a double
    //int lda = 50; // LDA, input for multiplication functions has to be an int
    vector<double> LDA = {64, 512, 1024, 16384};//, 131072,1048576};
    vector<int> lda = {64, 512, 1024, 16384};//, 131072,1048576};
    double y_max = 50; // radius of the pipe, [m]
    double x = 100.0; // horizontal location on the pipe, [m]
    double z = 50.0; // 3D location on the pipe, [m]
    double g = 9.81; // gravity, [kg/m*s^2]
    double mu = 1e-4; // dynamic viscosity of water, [kg m−1 s−1]
    vector<double> time_BaseMult;// amount of time for base multiplication
    vector<double> time_RecursiveMult; // amount of time for recursive application

    vector<double> data1 = perturbedShear_calculator( LDA[4], y_max, x, z, mu);//Shear Matrix, water.
    vector<double> data2 = surfaceRoughnes_calculator( LDA[4], y_max, x, z, mu);//Shear Matrix, water.
    //for (auto jj : lda){
        //cout << "Computing time for " << jj << "by"<< jj << "matrix" << endl;
        for(int ii=0; ii<1000; ii++){
            // Test base multiplication
            //cout << "Computing Matrix Product with Base Multiplication Function. Result is: " << endl;
            auto start = high_resolution_clock::now();    // time product function
                Matrix m1(64,lda[4],64,data1.data());
                Matrix m2(64,lda[4],64,data2.data());
                Matrix m3(64,lda[4],64,data1.data());
                m3.MatMult(m1,m2);
                m2.print();
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            //cout << "Time taken by Base Multiplication Function: "
            //<< duration.count() << " microseconds" << endl;
                time_BaseMult.push_back(duration.count());

            // Test recursive multiplication
            //cout << "Computing Matrix Product with Recursive Multiplication Function. Result is: " << endl;
            auto startRecursive = high_resolution_clock::now();    // time product function
                Matrix mr1(64,lda[4],64,data1.data());
                Matrix mr2(64,lda[4],64,data2.data());
                Matrix mr3(64,lda[4],64,data1.data());
                mr3.RecursiveMatMult(mr1,mr2);
                mr2.print();
            auto stopRecursive = high_resolution_clock::now();
            auto durationRecursive = duration_cast<microseconds>(stopRecursive - startRecursive);
            //cout << "Time taken by Recursive Multiplication function: "
            //<< durationRecursive.count() << " microseconds" << endl;
                time_RecursiveMult.push_back(durationRecursive.count());
        }
        cout << "Average time for base multiplication: " << endl;
        cout << average(time_BaseMult) << endl;
            cout << "Average time for recursive multiplication: " << endl;
            cout << average(time_RecursiveMult) << endl;
        // empty time vector
            std::fill_n(time_BaseMult.begin(), time_BaseMult.size(), 0);
            std::fill_n(time_RecursiveMult.begin(), time_RecursiveMult.size(), 0);
       // }
    return 0;
}
