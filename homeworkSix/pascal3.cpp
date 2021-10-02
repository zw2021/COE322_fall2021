#include <iostream>
#include <vector>
using namespace std;

class pascal {
public:
	vector<vector<int>> y;
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
	pascal(int n) {
		y = vals(n); 
}
};

int main() {
	int n =6;
	pascal num(n);	
	for (int p=0;p<n;p++){
		for (int q=0;q<n;q++){
			cout << num.y[p][q] << " ";
		}
	cout << endl;
	
	}
	return 0;
}

