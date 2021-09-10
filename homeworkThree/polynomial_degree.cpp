#include <iostream>
#include <vector>
#include <cmath>
#include "evaluate_at.cpp"
using namespace std;

// check if polynomial is even or odd degree
// odd if f(-x) = -f(x);

int is_odd(vector<double> coefficients_vector) {
    try {
        double x = 1; // arbitrary number- can honestly be any value x
        double y_posInput = -1*(evaluate_at(coefficients_vector, x)); // compute -1*f(x)
        double y_negInput = evaluate_at(coefficients_vector, -1*x); // compute f(-x);
            if (y_posInput != y_negInput){
                // -1*f(x) != f(-x); Polynomial is Even
                cout << "Polynomial is Even" << endl;
                throw(coefficients_vector);
               // return coefficients_vector;
                }
        return 20;
}
    catch(...) {
        cout << "Rejecting Polynomial, Please input New Polynomial " << endl;
    }

    }


int main(){
    vector<double> v = {2,0,-4,0};
    is_odd(v);
}
