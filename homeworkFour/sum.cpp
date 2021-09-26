//
// Created by huang on 9/24/2021.
//

#include <iostream>
#include <vector>
using namespace std;

int checkPrime(vector<int> vec, int idx, int jdx, int pivot, int even_num){
    // counters int idx = 0; int jdx = 1; and when i switches - "pivot"
    if (jdx > vec.size()-1){
        pivot ++;
        idx = pivot;
        jdx = pivot + 1;
    }
    if(vec[idx] + vec[jdx] == even_num){ // base case 2 numbers sum to even number
        cout << "These primes sum to the selected even number: " << vec[idx] << " and " << vec[jdx] << endl;
        return vec[idx], vec[jdx];
    }else if (vec[idx] + vec[idx] == even_num){ // a prime plus itself sums to even number
        cout << "This prime sums to the selected even number: " << vec[idx] << endl;
    }else if (vec[idx] + vec[jdx] > even_num  || vec[idx] + vec[jdx] < even_num){ // doesn't sum to even number
        jdx++;
        return checkPrime(vec, idx, jdx, pivot, even_num);
    }else if (vec[pivot] == vec.back()){ // reach end of vector and never reaches sum to even number
        cout << "None of the primes in the given vector will sum to the selected even number" << endl;
        return -1; // arbitrary number to show error
    }
    return  0;
}
int main(){
    vector<int> myVec{2,3,5};
    int idx = 0; int jdx = 1; int pivot = 0; int even_num = 6;
    checkPrime(myVec, idx, jdx, pivot, even_num);
    return 0;
}

