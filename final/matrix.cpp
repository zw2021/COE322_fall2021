#include <iostream>
#include <vector>
#include <array>
//#include <..\GSL-main\include\gsl\span>
#include <span>


using namespace std;
using gsl::span;

class Matrix {

    private:

    int m,m,lda;
    span<double> data;

    public:

    Matrix(int m, int lda, int n, double *data) {

    }
}

int main {
    return 0;
}