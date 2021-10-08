/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2021 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** newton1.cxx : newton scalar example
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <cmath>

#include <functional>
using std::function;

auto ff = [] (double x) -> double{return x*x-2;}; // lambda functions
auto gg = [] (double x) -> double{return 2*x; };

double find_zero
( function<double(double)> f, function<double(double)> f_prime){
// tells c++ that you're making a class of functions
// function indicates class of special type; <> indicates vector of integers
    double x =1;
    while ( true ) {

        auto fx = ff(x);
        cout << "f( " << x << " ) = " << fx << "\n";
        if (std::abs(fx)<1.e-10 ) break;
            x = x - fx/f_prime(x);
    }
    return x;
}

int main() {

    for(int n=2; n<=8; n++){
        auto f_prime = [n] (double x) -> double{return (n)*pow(x, (n-1)); };
        auto f = [n] (double x) -> double{return pow(x, (n))-2; };
        cout << "sqrt(" << n << ") = " << find_zero(f, f_prime) << "\n";
    }
return 0;
}
