/*
 * Authors
 * Nick Delurgio npd429
 * Pavan Shukla pas3488
 * Zoelle Wong zfw65
 */


/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2021 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** newton1.cxx : newton scalar example
 ****
 ****************************************************************/
/* Helpful Sources for learning about NR method for square root estimation:
 * http://www.sosmath.com/calculus/diff/der07/der07.html
 * https://www.quora.com/What-is-the-Newton-Rapson-method-for-finding-a-square-root-of-an-integer-number-How-does-one-use-it
 *
 * */
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <cmath>
#include <functional>
using std::function;
// finds root with one lambda argument
double newton_root(function <double(double)> f){
    double x =1;
    double h = .01;
        while ( true ) {
            auto fx = f(x);
            auto fxh = f(x+h);
            auto f_prime = (fxh-fx)/h;
                if (std::abs(fx)<1.e-10 ) break;
                x = x - fx/f_prime;
        }
        cout << "The root of this number is " << x << "\n";
    return x;
    }
int main() {
    int n;
    cin >> n;
    auto f = [n] (double x) -> double{return x*x - n; };
    newton_root(f);
    return 0;
}
