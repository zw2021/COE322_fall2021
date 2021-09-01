#include<iostream>
using namespace std;
//<SUMMARY>#################################################################
// "swap" is a void function that outputs the exchange of 2 input parameters
//##########################################################################

void swap(int x, int y){
    int dummy;

    dummy = x;
    x = y;
    y = dummy;

    cout << x << "," << y << endl;
}
int main() {
    int x, y;
    cout << "Enter a Number: " << endl;
    cin >> x;
    cout << "Enter a Second Number: " << endl;
    cin >> y;
    cout << "swap: " << endl;
    cout << x << "," << y << endl;
    swap(x, y);
    std::cout << "End of Computation" << std::endl;
    return 0;
}
