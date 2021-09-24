//
// Created by huang on 9/24/2021.
//

#include <iostream>
#include <vector>
using namespace std;

int checkPrime(vector<int> vec, int idx = 0, int jdx = 0, int pivot = 0){
    // inputs int idx = 0; int jdx = 1;
    if (idx > vec.size()){
        //need to reset the index to the next element
        pivot ++;
        idx = pivot;
    }
    if(jdx > vec.size()){
        // need to reset the index to 0
        jdx = 0;
    }
    if((vec[idx] + vec[jdx + 1] == 12) || vec[idx-1] == vec.back()){
        return vec[idx], vec[jdx];
    }else if ((vec[idx] + vec[jdx] > 12 ) || (vec[idx] + vec[jdx+1] < 12)){
        idx++; jdx++;
        checkPrime(vec, idx, jdx, pivot);
    }
}
int main(){
    vector<int> myVec{3,8,9};
    cout << myVec[5] << endl;
    return 0;
}