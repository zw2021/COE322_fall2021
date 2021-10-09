//
// Created by huang on 10/8/2021.
//

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <cmath>

#include <functional>
using std::function;

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
        double h = 0.001;
        auto f_prime = [] (double x) -> double{return 3*x*x + 2*x; }; // "actual derivative"
        auto f = [] (double x) -> double{return x*x*x + x*x - 2; }; // function
        cout << "Gradient of f with h: " << h << " = " << find_grad(f, f_prime, h) << "\n";

    return 0;
}