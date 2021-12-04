/*
 * Header file with simple subroutines to compute mean, standard deviation
 * couldn't find a C++ stats library that made sense:(
 */

// source code courtesy of stack overflow
#include <iostream>
#include <vector>
#include <numeric>

double average(std:: vector<double> v){
    if(v.empty()){
        return 0;
    }
    double sum = 0;
        for(int ii = 0; ii<v.size(); ii++){
            sum = sum + v[ii];
    }
    double mean = sum / v.size();

    return mean;
}
/*
double standard_dev(std::vector<double> const& v){
    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    double mean = sum / v.size();

    double sq_sum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / v.size() - mean * mean);
    return stdev;
}
*/