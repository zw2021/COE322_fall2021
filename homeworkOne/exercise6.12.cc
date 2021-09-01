#include<iostream>

using namespace std;

int main(){
	int num;
	int dummy;

	cout << "Enter a number: ";
	cin >> num;
	cout << "You entered: " << num << ",Commencing Collatz conjecture" << endl;

	if (num == 1){
		cout << "Answer is 1" << endl;
	}
	
	dummy = 10; // random number
	while (num != 1){				
		if (num % 2) == 0{
			dummy = num/2;				
		}else if (num % 2) != 0{
			dummy = 3*num + 1;
		}
	
		num = dummy;
	}
	//cout << "Hello World!" << endl;
	return 0;
}
