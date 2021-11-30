//Compile line: icpc -I${TACC_GSL_INC} final/matrix.cpp
#include <iostream>
#include <vector>
#include <array>
#include "gsl/gsl-lite.hpp"
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
    int m = 2;
    int lda = 3;
    int n = 2;
    vector<double> data1 = {1,3,5,2,4,6};
    vector<double> data2 = {1,2,3,4};
    vector<double> data3 = {2,2,3,4,5,6,7,8,9,10,11,12};
    vector<double> data4 = {2,2,3,4,5,6,7,8,9};
    Matrix m1(3,4,3,data3.data());
    Matrix m2(3,3,3,data4.data());
    Matrix m3(3,3,3,data4.data());
    m1.print();
    m2.print();
    m1.addMatrices(m2,m3);
    m3.print();

    vector<double> data5 = {1,2,3,4,5,6,7,8,9,10,10,12,13,14,15,16};
    Matrix m4(3,4,4,data5.data());
    //m4.print();
    Matrix l1 = m4.Right(2);
    //l1.print();

    m1.print();
    m2.print();
    Matrix m5(3,3,3,vector<double>(9,0).data());
    m1.MatMult(m2, m5);
    m5.print();

    vector<double> data6 = {1,2,3,4,5,6,7,8,9};
    vector<double> data7 = {2,3,4};
    Matrix m6(3,3,3,data6.data());
    Matrix m7(3,3,1,data7.data());
    Matrix m8(3,3,1,vector<double>(3,0).data());
    m6.MatMult(m7,m8);
    m6.print();
    m7.print();
    m8.print();

    vector<double> r4c5 = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    vector<double> r5c4 = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    vector<double> r4c4 = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    Matrix m20a(4,4,5,r4c5.data());
    Matrix m20b(5,5,4,r4c5.data());
    //Matrix m20c(4,4,4,vector<double>(16,0).data());
    Matrix m20c(4,4,4,r4c4.data());
    cout << "M20A" << endl;
    m20a.print();
    cout << "M20B" << endl;
    m20b.print();
    m20a.BlockedMatMult(m20b,m20c);
    /*

    vector<double> r8c8 = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64};
    vector<double> r8c82 = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64};;
    vector<double> r8c83(64,0);

    Matrix m24a(8,8,8,r8c8.data());
    Matrix m24b(8,8,8,r8c82.data());
    Matrix m24c(8,8,8,r8c83.data());
    m24a.print();
    m24b.print();
    m24a.RecursiveMatMult(m24b,m24c);
    
    m24c.print();*/


    return 0;
}
