#include <iostream>
#include <vector>
#include <cmath>
#include "find_outer.cpp"
using namespace std;


double find_zero(vector<double> coeff) {
 // vector<double> coeff = {3,2,0,1};
  vector<double> outer = find_outer(coeff);
  double xl = outer[0];  // left bound
  double xr = outer[1];  // right bound
  double c = 0;  //midpoint initialization
  double tol = pow(10,-4);  // tolerance
  //bisection method
  while (abs(evaluate_at(coeff,c))>tol){
     c = (xl+xr)/2;
     if (evaluate_at(coeff,c)*evaluate_at(coeff,xl)>0){
	xl = c;
     }
     else {
        xr=c;
     }
	
  }
  cout << "Found root " << c << " with value " << evaluate_at(coeff, 0) << "\n";

  return c;
}


//int main(){
//    vector<double> coeff = {2,0,0,4,0,3};
//    double sol = find_zero(coeff);
//    cout << "x = " << sol << endl;
//    cout << "f(x) = " << evaluate_at(coeff,sol)<< endl;
//}

