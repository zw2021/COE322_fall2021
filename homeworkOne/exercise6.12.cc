#include<iostream>

using namespace std;

int main(){
	int dummy, counter, num;
    int num_iterations[1000];

    /*cout << "Enter a number: ";
	cin >> num;
	cout << "You entered: " << num << ",Commencing Collatz conjecture" << endl;*/
	
	dummy = 10; // arbitrary number for placeholder
    counter = 0;
    /*for(int ii=2; ii<=1000; ii++)
    {
        cout << ii << endl;
        counter = 0; // reset counter after every iteration
        num = ii;

        while (num != 1){
            if ((num % 2) == 0){
                dummy = num/2;
                // cout << "this is even" << endl;  // sanity checks
            }else if ((num % 2) != 0){
                dummy = 3*num + 1;
                // cout << "this is odd" << endl; // sanity checks
            }
            num = dummy;
            ++counter;
        }

        num_iterations[ii] = counter;
       // cout << "Number: " << ii << endl;
       // cout << "Number of Iterations: " << num_iterations[ii] << endl;
    }*/

    //cout << "Congratulations! Your Number Became " << num << endl;
    //cout << "Number of Iterations: " << counter << endl;
	//cout << "End of Computation" << endl;
	return 0;
}
