//EX 10
#include <iostream>
#include <vector>
#include "evaluate_at.cpp"
using namespace std;

int main() {
    vector<double> coefficients; //Add from other problems
    double left;
    double right;
    double zero = find_zero(coefficients,left,right); //Pavan will add find_zero function

    cout << "Found Root: " << zero << endl;
    cout << "With Value: " << evaluate_at(coefficients, zero);
}