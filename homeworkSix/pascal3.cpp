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
	void print(int m) {
		for(int i = 0; i < y.size(); i++) {
			//cout << "Row " << i << endl;
			for(int j = i; j < y.size() - 1; j++) {
				//cout << "j = " << j << endl;
				cout << " ";
			}
			for(int j = 0; j < y[i].size(); j++) {
				if(y[i][j] % m != 0) {
					cout << "* ";
				}
				else {
					cout << "  ";
				}
			}
			cout << endl;
		}
	}
};

int main() {
	int n = 8;
	int m = 2;
	pascal num(n);	
	for (int p=0;p<n;p++){
		for (int q=0;q<n;q++){
			cout << num.y[p][q] << " ";
		}
	cout << endl;
	
	}
	num.print(m);
	return 0;
}