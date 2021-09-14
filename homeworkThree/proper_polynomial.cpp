#include <iostream>
#include <vector>
#include <cmath>
#include "evaluate_at.cpp"
using namespace std;


bool proper_polynomial(vector<double> coefficients_vector){
    // check if the power of the variable is a non negtative value
    // power of the variable is raised to a fraction

    // check if size of vector is degree n+1
    // e.g cubic function x^3 has 4 elements: x^3 + 0x^2 +0x +0
    try{
        if (coefficients_vector.size() <= 0){
          cout << " Coefficeint Vector is Less than or Equal to 0" << endl;
          throw(coefficients_vector);
        }
        if (coefficients_vector.front() == 0){
          throw(coefficients_vector);
        }
        //return false;
    }
    catch(...){
    	  cout << "Rejecting Polynomial, Please input New Polynomial" << endl;
          return false;
    }
     cout << "Finished Checks for Proper Polynomial" << endl;
    return  true;
}

int main(){
    vector<double> vec = {0, 0,0,0};
    proper_polynomial(vec);
    double left{11};
    return 0;

}