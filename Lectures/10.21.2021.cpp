#include<iostream>
using namespace std;

void swap(int *i, int *j) {
    int temp = *i;
    *i = *j;
    *j = temp;
}

int main() {
    int i=1, j=2;
    swap(&i,&j);
    cout << "check that i is 2: " << i << endl;
    cout << "check that j is 1: " << j << endl;
    return 0; 
}