// EX 7
#include <iostream>
#include <vector>
using namespace std;

double evaluate_at(vector<double> v, double x) {
    if(v.size() == 1) { return v[0]; } //check for length 1 vector
    else if(v.size() <= 2) { return v[v.size()-1] + x*v[0]; } //ends recursion
    double y = v[v.size()-1];
    v.pop_back(); //remove last array element
    return y + x*(evaluate_at(v,x)); //recursion to evaluate next vector subset
}

//int main() {
//    vector<double> v = {4,3,2,1};
//    double ans = evaluate_at(v,5);
//    cout << ans << endl;
//}