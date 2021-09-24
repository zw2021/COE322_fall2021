//
// Created by huang on 9/24/2021.
//

#include <iostream>
#include <vector>
using namespace std;

int checkPrime(vector<int> vec, int idx = 0, int jdx = 1, int pivot = 0){
    // inputs int idx = 0; int jdx = 1;
    if (jdx > vec.size()){
        //need to reset the index to the next element
        pivot ++;
        idx = pivot;
        jdx = pivot + 1;
    }
    if((vec[idx] + vec[jdx] == 12) || vec[idx-1] == vec.back()){
        return vec[idx], vec[jdx];
    }else if ((vec[idx] + vec[jdx] > 12 ) || (vec[idx] + vec[jdx+1] < 12)){
        jdx++;
        checkPrime(vec, idx, jdx, pivot);
    }
}
int main(){
    vector<int> myVec{2,3,5,7,11};
    int a = checkPrime(myVec);
    cout << a << endl;
    cout << myVec[5] << endl;
    return 0;
}