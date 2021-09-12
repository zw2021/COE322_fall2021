//EX 10
#include <iostream>
#include <vector>
#include "evaluate_at.cpp"  
#include "find_zero.cpp"
using namespace std;

int main() {
    vector<double> coefficients = {}; //Add from other problems
    double zero = find_zero(coefficients); //Pavan will add find_zero function

    cout << "Found Root: " << zero << endl;
    cout << "With Value: " << evaluate_at(coefficients, zero);
}