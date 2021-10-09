//
// Created by huang on 10/8/2021.
//


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

double find_zero
( function<double(double)> f, function<double(double)> f_prime){
// tells c++ that you're making a class of functions
// function indicates class of special type; <> indicates vector of integers
    double x =1;
    while ( true ) {

    auto fx = f(x);
    //cout << "f( " << x << " ) = " << fx << "\n";
    if (std::abs(fx)<1.e-10 ) break;
        x = x - fx/f_prime(x);
    }
    cout << "The root of this number is " << x << "\n";
    return x;
}


double find_grad
( function<double(double)> f, function<double(double)> f_prime, double h){
// tells c++ that you're making a class of functions
// function indicates class of special type; <> indicates vector of integers
double x = 1;
double f_prime_it;
while ( true ) {

auto fx = f(x);
auto fxh = f(x+h);
cout << "f_prime( " << x << " ) = " << fx << "\n";
    if (std::abs(f_prime(x)) - std:: abs(f_prime_it) <1.e-10 ) break;
        f_prime_it = (fxh - fx)/ h;
    }
return f_prime_it;
}

int main() {

    // basically merge exercises 3 and 4:(  see slide 7
    double n;
    cin >> n;
    auto f_prime = [] (double x) -> double{return 2*x; };
    auto f = [n] (double x) -> double{return x*x - n; };
    find_zero(f, f_prime);

return 0;
}
