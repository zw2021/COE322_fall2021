//Compile line: icpc -I${TACC_GSL_INC} final/matrix.cpp
#include <iostream>
#include <vector>
#include <array>
//#include <..\GSL-main\include\gsl\span>
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

    // void BlockedMatMult(Matrix& other, Matrix& out) {
    //     auto adata = this->get_double_data();
    //     auto bdata = other.get_double_data();
    //     auto cdata = out.get_double_data();
    //     if(this->m != 2 || this->n != 2 || other.getrows() != 2 || other.getcols() != 2 || out.getrows() != 2 || out.getcols() != 2) {
    //         cout << "Error: BlockedMatMal matrix not 2x2" << endl;
    //         throw(1);
    //     }
    //     #ifdef DEBUG
    //         out.at(0,0) = this->at(0,0)*other.at(0,0) + this->at(0,1)*other.at(1,0);
    //         out.at(0,1) = this->at(0,0)*other.at(0,1) + this->at(0,1)*other.at(1,1);
    //         out.at(1,0) = this->at(1,0)*other.at(0,0) + this->at(1,1)*other.at(1,0);
    //         out.at(1,1) = this->at(1,0)*other.at(0,1) + this->at(1,1)*other.at(1,1);
    //     #else
    //         cdata[INDEX(0,0,out.getlda())] = adata[INDEX(0,0,this->getlda())]*bdata[INDEX(0,0,other.getlda())] + adata[INDEX(0,1,this->getlda())]*bdata[INDEX(1,0,other.getlda())];
    //         cdata[INDEX(0,1,out.getlda())] = adata[INDEX(0,0,this->getlda())]*bdata[INDEX(0,1,other.getlda())] + adata[INDEX(0,1,this->getlda())]*bdata[INDEX(1,1,other.getlda())];
    //         cdata[INDEX(1,0,out.getlda())] = adata[INDEX(1,0,this->getlda())]*bdata[INDEX(0,0,other.getlda())] + adata[INDEX(1,1,this->getlda())]*bdata[INDEX(1,0,other.getlda())];
    //         cdata[INDEX(1,1,out.getlda())] = adata[INDEX(1,0,this->getlda())]*bdata[INDEX(0,1,other.getlda())] + adata[INDEX(1,1,this->getlda())]*bdata[INDEX(1,1,other.getlda())];
    //     #endif
    // }
    void BlockedMatMult(Matrix& other, Matrix& out) {
        // Matrix aleft = this->Left(this->getcols()/2);
        // Matrix aright = this->Right(this->getcols()/2);
        // Matrix atop = this->Top(this->getrows()/2);
        // Matrix abot = this->Bot(this->getrows()/2);

        // Matrix bleft = other.Left(this->getcols()/2);
        // Matrix bright = other.Right(this->getcols()/2);
        // Matrix btop = other.Top(this->getrows()/2);
        // Matrix bbot = other.Bot(this->getrows()/2);

        Matrix atl = this->Left(this->getcols()/2).Top(this->getrows()/2);
        Matrix atr = this->Right(this->getcols()/2).Top(this->getrows()/2);
        Matrix abl = this->Left(this->getcols()/2).Bot(this->getrows()/2);
        Matrix abr = this->Right(this->getcols()/2).Bot(this->getrows()/2);

        Matrix btl = other.Left(other.getcols()/2).Top(other.getrows()/2);
        Matrix btr = other.Right(other.getcols()/2).Top(other.getrows()/2);
        Matrix bbl = other.Left(other.getcols()/2).Bot(other.getrows()/2);
        Matrix bbr = other.Right(other.getcols()/2).Bot(other.getrows()/2);

        Matrix otl(atl.getrows(),atl.getrows(),btl.getcols(),vector<double>(atl.getrows()*btl.getcols(),0).data());
        addMatrices(atl.MatMult(btl,otl),atr.MatMult(bbl,otl),otl);
        otl.print();
        
    }
    //Ex 60.7
    void RecursiveMatMult(Matrix& other, Matrix& out) {
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

//Addition method (ex. 60.4)
void addMatrices(Matrix A, Matrix B, Matrix& out) {
    if (A.getrows() != B.getrows() || A.getcols() != B.getcols()) {
        cout << "Error using addMatrices: Matrices do no have the same dimensions" << endl;
        throw(1);
    }

    //vector<double> cdata(A.getrows()*B.getrows(),0);
    auto adata = A.get_double_data();
    auto bdata = B.get_double_data();
    auto cdata = out.get_double_data();
    for(int j = 0; j < A.getcols(); j++) {
        for(int i = 0; i < A.getrows(); i++) {
            #ifdef DEBUG
                cdata[INDEX(j,A.getrows(),i)] = A.at(i,j) + B.at(i,j);
            #else
                cdata[INDEX(j,A.getrows(),i)] = adata[INDEX(j,A.getlda(),i)] + bdata[INDEX(j,B.getlda(),i)];
            #endif
        }
    }
    //Matrix C(A.getrows(),A.getrows(),A.getcols(),cdata.data());
    //out = C;
}

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
    addMatrices(m1,m2,m3);
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



    // vector<double> data9 = {1,2,3,4};
    // vector<double> data10 = {1,2,3,4};
    // Matrix m9(2,2,2,data9.data());
    // Matrix m10(2,2,2,data10.data());
    // Matrix m11(2,2,2,vector<double>(4,0).data());
    // m9.BlockedMatMult(m10,m11);
    // m9.print();
    // m10.print();
    // m11.print();

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

    //m3.print();
    //m3.at(0,0);
    //m3.printdata();
    /* METHOD TO CHANGE ELEMENTS IN A MATRIX
    double& x = mat.at(1,1);
    x = 5;
    cout << mat.at(1,1) << endl;
    */
    return 0;
}
