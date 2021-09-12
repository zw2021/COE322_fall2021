#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double find_zero(vector<double>);
double evaluate_at(vector<double>, double);
vector<double> find_outer (vector<double>);
vector<double> set_coefficients(int);
void print(vector <double>);
int proper_polynomial();

int main() {
    return 0;
}

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

double evaluate_at(vector<double> v, double x) {
    if(v.size() == 1) { return v[0]; } //check for length 1 vector
    else if(v.size() <= 2) { return v[v.size()-1] + x*v[0]; } //ends recursion
    double y = v[v.size()-1];
    v.pop_back(); //remove last array element
    return y + x*(evaluate_at(v,x)); //recursion to evaluate next vector subset
}

vector<double> find_outer (vector<double> coeff) {
  double xr= 1;   //initial guess for bracket size
  double xl = -xr;
  // find brackets with positive and negative function values
  while (evaluate_at(coeff,xr)*evaluate_at(coeff,xl) >= 0){
          xr = xr*2;
          xl = xl*2;
  }
  vector<double> outer = {xl,xr};
  return outer;
}

vector<double> set_coefficients(int degree){
    vector<double> coefficients(degree+1);
    for(int ii = 0; ii<degree; ii++){
        double num;
        cout << "Enter " << ii << "st Coefficient: " << endl;
        cin >>  num;
        coefficients.at(ii) = num;
    }
    return coefficients;
}

void print(vector <double> a) {
   std::cout << "Your Coefficient Vector Contains Elements: ";
   for(int i=0; i < a.size(); i++)
   std::cout << a.at(i) << ',' << endl;
}

int proper_polynomial(){
    // check if the power of the variable is a non negtative value
    // power of the variable is raised to a fraction

    // check if size of vector is degree n+1
    // e.g cubic function x^3 has 4 elements: x^3 + 0x^2 +0x +0

    //REQUIRE();
    return 0;
}

int is_odd(vector<double> coefficients_vector) {
    try {
        if (coefficients_vector.size() %2 != 0){
            // Highest Ordered Term is not Odd Degree
            cout << "Highest Ordered Term is Even" << endl;
            throw(coefficients_vector);
           // return coefficients_vector;
            }
        return 20;
    }
    catch(...) {
        cout << "Rejecting Polynomial, Please input New Polynomial with Odd Degree Terms" << endl;
    }

}