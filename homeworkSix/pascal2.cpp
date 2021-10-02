#include <iostream>
#include <vector>
using namespace std;

class pascal {
//private:
//    int how_many_primes_found;
//    int last_number_tested;
public:

	int factorial(int x) {
		int k=1;
		while (x>0){
			k=k*x;
			x--;
		}
		return k;
	}
    	vector<vector<int>> vals(int n) {
        	vector<vector<int>> mat(n,vector<int>(n));
		for (int i=0;i<n;i++){
			int j=0;
			while (j<i+1){
				mat[i][j] = factorial(i)/factorial(j)/factorial(i-j);
				j++;
			}

		}
		return mat;
    }
};

int main() {
	int n =6;
	pascal num;
	vector<vector<int>> mat;
	mat = num.vals(6);	
	for (int p=0;p<n;p++){
		for (int q=0;q<n;q++){
			cout << mat[p][q] << " ";
		}
	cout << endl;
	
	}
	return 0;
}

