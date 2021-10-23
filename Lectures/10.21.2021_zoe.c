//
// Created by huang on 10/21/2021.
//
#include <iostream>
//using namespace std

void swap( int i, int j) {
/* your code */
    i = &j;
}
int main() {
    int i=1,j=2;
    swap( i, j);
    cout << "check that i is 2: " << i << endl;
    cout << "check that j is 1: " << i << endl;
    return 0;
}
