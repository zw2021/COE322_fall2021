#include <iostream>
#include <vector>
using namespace std;

// Source code for making a vector w. random coefficients
vector<double> random_coefficients(int degree) {
  vector<double> coefficients(degree+1);
  for (int c=0; c<=degree; c++) {
      coefficients.at(c) = -4.5 + rand() % 10 ;
  }
  return coefficients;
};

// Code for making a user defined vector
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

// print function for displaying contents of vector
void print(vector <double> a) {
   std::cout << "Your Coefficient Vector Contains Elements: ";
   for(int i=0; i < a.size(); i++)
   std::cout << a.at(i) << ',' << endl;
}

//int main() {
//    int degree;
//    cout << "Enter Polynomial Degree: " << endl;
//    cin >> degree;
//    print(set_coefficients(degree));
//    return 0;
//}
