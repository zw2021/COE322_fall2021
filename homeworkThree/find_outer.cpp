#include <iostream>
#include <vector>
#include <cmath>
#include "evaluate_at.cpp"
using namespace std;

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

