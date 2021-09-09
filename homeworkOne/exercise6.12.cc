#include<iostream>
#include<cassert>

//#define NDEBUG // disables all "asserts"
using namespace std;

//## <SUMMARY> #############################################################################
/*This code uses the Collatz Conjecture, which states that no matter the starting guess u_1,
the sequence as n approaches u_n will always terminate at 1. This is true when:

    u_n+1 = u_n/2 when u_n is even
    u_n+1 = 3*u_n+1 when u_n is odd

This code tries all starting values u_1 = 1,....,1000 to the values that leads to the
longest sequence and prints the previous maximum everytime a sequence is longer than
a previous starting number */
//##########################################################################################
int main(){
	int dummy, counter, num, max;
    int num_iterations[9999]; // will need to make this a dynamic array later; hard coded bc of hw
	
	dummy = 10; // arbitrary number for placeholder
    counter = 0;


    for(int ii=1; ii<=1000; ii++)
    {
        counter = 0; // reset counter after every iteration
        num = ii;
        // Take care of the special case when ii = 1
        if (ii == 1){
            dummy = 3*num + 1; // we can do this bc we already know 1 is od
            assert(dummy != 1); // check if this is
            while(dummy != 1){
                if ((dummy % 2) == 0){
                    dummy = dummy/2;
                }else if ((num % 2) != 0){
                    dummy = 3*dummy + 1;
                }
                ++counter;
            }
            num_iterations[ii] = counter;
        }

        // for all other numbers not equal to 1
        while (num != 1){
            if ((num % 2) == 0){
                dummy = num/2;
            }else if ((num % 2) != 0){
                dummy = 3*num + 1;
            }
            num = dummy;
            ++counter;
        }

        num_iterations[ii] = counter;

        for (int jj = 1; jj <= 1000; jj++)  // Find Running Maximum Value in Array
            if (num_iterations[jj] > max){
                max = num_iterations[jj];
                cout << "Current Maximum Starting Number: " << jj << endl;
            }
    }

	cout << "End of Computation" << endl;
	return 0;
}
