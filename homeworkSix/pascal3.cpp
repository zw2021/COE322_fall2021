#include <iostream>
#include <vector>
#include <iomanip>
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

    vector<int> modulos(int bound){
        int i =0;
        vector<int> modulos_vec;
        while (i<modulos_vec.size()){
                modulos_vec.push_back(i);
                i++;
        }
	return modulos_vec;

	}
    	vector<vector<int>> vals(int n) {
        	vector<vector<int>> mat(n,vector<int>(n));
		for (int i=0;i<n;i++){
			int j=0;
			while (j<i+1){
				//mat[i][j] = factorial(i)/factorial(j)/factorial(i-j);
				if (j == 0 || j == i) {
					mat[i][j] = 1;
				}
				else {
					mat[i][j] = mat[i-1][j-1] + mat[i-1][j];
				}
				j++;
			}

		}
		return mat;
    }
	pascal(int n) {
		y = vals(n); 
}

	int get(int i,int j) {
		return y[i][j];
	}

	void print() {
		for(int i = 0; i < y.size(); i++) {
			cout << "Row" << setw(3) << i+1 << ":	";
			for(int j = i; j < y.size() - 1; j++) {
				cout << "   ";
			}
			for(int j = 0; j < 1 + i; j++) {
				cout << y[i][j] << setw(6);
			}
			cout << setw(0);
			cout << endl;
		}
	}
	void print(vector<int> m) {
		for(int tnum = 0; tnum < m.size(); tnum++) {
			cout << endl;
			for(int i = 0; i < y.size(); i++) {
				//cout << "Row " << i << endl;
				for(int j = i; j < y.size() - 1; j++) {
					//cout << "j = " << j << endl;
					cout << " ";
				}
				for(int j = 0; j < y[i].size(); j++) {
					if(y[i][j] % m[tnum] != 0) {
						cout << "* ";
					}
					else {
						cout << "  ";
					}
				}
				cout << endl;
			}
		}
	}
};

int main() {
	int n;
    cin >> n;
	int input;
	vector<int> m;
	int val;

	while (cin >> val && val != 0) {
		m.push_back(val);
	}

	// while (m[m.size()-1] != 0) {
	// 	cin >> val;
	// 	cout << endl << val << endl;
	// 	m.push_back(val);
	// }
    cout << "done" << endl;
    /*vector<int> modulus;
    for (int ii = 0; ii <2; ii++)
        cin >> input;
        modulus.push_back(input);
*/
    pascal num(n);

    //for(int ii = 0; ii < modulus.size(); ii++){
        // for (int p=0;p<n;p++){
        //     for (int q=0;q<n;q++){
        //         cout << num.y[p][q] << " ";
        //     }
	    //     cout << endl;

	    // }
    num.print();
    num.print(m);
    //}

	return 0;
}