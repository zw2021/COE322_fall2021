#include <iostream>
#include <vector>
#include <random>
using namespace std;

// shear sub-routines
double calculate_exx(double x, double y, double z, double mu) {
    return (2*x*z*z*z);
}

double calculate_eyy(double x, double y, double z, double mu) {
    return (3*y*y + 1);
}

double calculate_ezz(double x, double y, double z, double mu) {
    return 0;
}

double calculate_exy(double x, double y, double z, double mu) {
    return (2*y - 1)/(4*mu);
}

double calculate_ezx(double x, double y, double z, double mu) {
    return (3*x*x*z*z)/2 + 1/2;
}

double calculate_ezy(double x, double y, double z, double mu) {
    return (3*y*y)/2;
}

vector<double> perturbedShear_calculator(double LDA, double y_max, double x, double z, double mu) {
    /*
    double LDA = 8; // number of rows or columns in a matrix
    double y_max = 50; // radius of the pipe, [m]
    double x = 100.0;
    double z = 50.0;
    double mu = 1e-4;
    */
    vector<double> input;
    double step = y_max/((LDA*LDA)-1); // denominator should always be total number of elements divided 1 - LDA
    int counter = 0;

    // initialize random number for perturbations in the flow
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(0, 1e-5);

    for(double y = 0; y < y_max; y += step ){
        // cout << (y) << endl;
        //input.push_back(ii);
        // insert shear matrix
        if (counter == 0){
            input.push_back(calculate_exx(x, y, z, mu));
            counter++;
        }else if (counter == 1){
            input.push_back(calculate_exy(x, y, z, mu));
            counter++;
        }else if (counter == 2){
            input.push_back(calculate_ezx(x, y, z, mu));
            counter ++;
        }else if(counter == (LDA)){
            input.push_back(calculate_exy(x, y, z, mu));
            counter ++;
        }else if (counter == (LDA)+1){
            input.push_back(calculate_eyy(x, y, z, mu));
            counter ++;
        }else if (counter == (LDA)+2){
            input.push_back(calculate_ezy(x, y, z, mu));
            counter ++;
        }else if (counter == (LDA*2)){
            input.push_back(calculate_ezx(x, y, z, mu));
            counter ++;
        }else if (counter == (LDA*2)+1){
            input.push_back(calculate_ezy(x, y, z, mu));
            counter ++;
        }else if (counter == (LDA*2)+2){
            input.push_back(calculate_ezz(x, y, z, mu));
            counter ++;
        }else{
            double pert =  distr(eng);
            input.push_back(pert);
            counter ++;
        }
    }
return input;
}

