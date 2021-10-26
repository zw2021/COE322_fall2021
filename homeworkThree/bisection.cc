//Nicholas Delurgio (npd429)
//Zoelle Wong (zfw65)
//Pavan Shukla (pas3488)






/*#include <iostream>
#include <vector>
using namespace std;
*/
double find_zero(vector<double>, double, double);
double evaluate_at(vector<double>, double);
void find_outer (vector<double>, double &, double &);
vector<double> set_coefficients(int);
void print(vector<double>);
bool proper_polynomial(vector<double>);
bool is_odd(vector<double>);

/*int main() {
    return 0;
}
*/
double find_zero(vector<double> coeff, double left, double right) {
// vector<double> coeff = {3,2,0,1};
  find_outer(coeff,left,right);
  double xl = left;  // left bound
  double xr = right;  // right bound
  double c = 0;  //midpoint initialization
  double tol = 0.0001;  // tolerance
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
  cout << "Found root " << c << " with value " << evaluate_at(coeff, c) << "\n";

  return c;
}

double evaluate_at(vector<double> v, double x) {
    if(v.size() == 1) { return v[0]; } //check for length 1 vector
    else if(v.size() <= 2) { return v[v.size()-1] + x*v[0]; } //ends recursion
    double y = v[v.size()-1];
    v.pop_back(); //remove last array element
    return y + x*(evaluate_at(v,x)); //recursion to evaluate next vector subset
}

void find_outer (vector<double> coeff,double &left, double &right) {
  if (!is_odd(coeff)) {
      throw("Error");
      return;
  }
  //double xr= 1;   //initial guess for bracket size
  //double xl = -xr;
  // find brackets with positive and negative function values
  while (evaluate_at(coeff,right)*evaluate_at(coeff,left) >= 0){
      if (right > left && right < 0) {
        right = right + 1;
      }
      else if (right < left && left < 0) {
        left  = left - 1;
      }
      else if (right > left && right > 0) {
          left = left - 1;
      }
      else if (right < left && left > 0) {
          right = right + 1;
      }
  }
  //vector<double> outer = {xl,xr};
  //return outer;
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
    }
    catch(...){
        cout << "Rejecting Polynomial, Please input New Polynomial" << endl;
        return false;
    }
    cout << "Finished Checks for Proper Polynomial" << endl;
    return true;
}

bool is_odd(vector<double> coefficients_vector) {
    try {
        if (coefficients_vector.size() %2 != 0){
            // Highest Ordered Term is not Odd Degree
            cout << "Highest Ordered Term is Even" << endl;
            throw(coefficients_vector);
           // return coefficients_vector;
            }
    }
    catch(...) {
        cout << "Rejecting Polynomial, Please input New Polynomial with Odd Degree Terms" << endl;
        return false;
    }

    return true;
}
