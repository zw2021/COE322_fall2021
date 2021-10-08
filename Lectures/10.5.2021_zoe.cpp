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

double f(double x) { return x*x-2; }; // static function
double g(double x) { return 2*x; };

auto ff = [] (double x) -> double{return x*x-2;}; // anonymous function
auto gg = [] (double x) -> double{return 2*x; };

double find_zero
    ( function<double(double)> ff, function<double(double)> fprime ){
        // tells c++ that you're making a class of functions
        // function indicates class of special type; <> indicates vector of integers
        double x{1.};
        while ( true ) {
            auto fx = ff(x);
            cout << "f( " << x << " ) = " << fx << "\n";
            if (std::abs(fx)<1.e-10 ) break;
            x = x - fx/gg(x);
        }
        return x;
}
int main() {

    double root = find_zero(ff,gg);
    double zero = find_zero([](double x){return x*x-2;}, [](double x){return 2*x;}) ;

/*double x{1.};
while ( true ) {
    auto fx = ff(x);
    cout << "f( " << x << " ) = " << fx << "\n";
    if (std::abs(fx)<1.e-10 ) break;
    x = x - fx/gg(x);
}
*/
return 0;
}
