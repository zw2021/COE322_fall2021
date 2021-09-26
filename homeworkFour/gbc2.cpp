//
// Created by huang on 9/18/2021.
//
/*
 * AUTHORS
 *Nick Delurgio, npd429
 *Pavan Shulkla, pas3488
 *Zoelle Wong, zfw65
 * */
#include <iostream>
#include <vector>
using namespace std;

class primegenerator {
private:
    int how_many_primes_found;
    int last_number_tested;
public:
    primegenerator() {
        how_many_primes_found = 0;
        last_number_tested = 1;
    }
    int nextprime() {
        bool foundprime = false;
        while(!foundprime) {
            last_number_tested++;
            foundprime = true;
            for (int i = 2; i < last_number_tested; i++) {
            if (last_number_tested % i == 0) {
            foundprime = false;
            break; }
            }
        }
        how_many_primes_found++;
        return last_number_tested;
    }
    int number_of_primes_found() {
        return how_many_primes_found;
    }

    int primes_found(){
        return last_number_tested;
    }
    int clear_values(){
        how_many_primes_found = 0;
        last_number_tested = 1;
        return how_many_primes_found, last_number_tested;
    }

    // recursive algorithm that sums each element in prime vector to test conjecture
    int checkPrime(vector<int> vec, int idx, int jdx, int pivot, int even_num){
    // counters int idx = 0; int jdx = 1; and when i switches - "pivot"
        if (jdx > vec.size()-1){
            pivot ++;
            idx = pivot;
            jdx = pivot + 1;
        }
            if(vec[idx] + vec[jdx] == even_num){ // base case 2 numbers sum to even number
            cout << "These primes sum to "<<even_num<<" : " << vec[idx] << " and " << vec[jdx] << endl;
            return vec[idx], vec[jdx];
        }else if (vec[idx] + vec[idx] == even_num){ // a prime plus itself sums to even number
            cout << "These primes sums to " <<even_num <<" : "<< vec[idx] <<" and "<<vec[idx]<< endl;
        }else if (vec[idx] + vec[jdx] > even_num  || vec[idx] + vec[jdx] < even_num){ // doesn't sum to even number
            jdx++;
            return checkPrime(vec, idx, jdx, pivot, even_num);
        }else if (vec[pivot] == vec.back()){ // reach end of vector and never reaches sum to even number
            cout << "None of the primes in the given vector will sum to the selected even number" << endl;
            return -1; // arbitrary number to show error
    }
    return  0;
    }
	// generate vector of even numbers up to bound
    vector<int> evengen(int bound){
        int i =0;
        int vlen = ((bound-(bound % 2))/2)-1;
        vector<int> even_numbers;//(0,vlen);
        while (i<vlen){
                even_numbers.push_back(4+2*i);// = 4+2*i;
                i++;
        }
	return even_numbers;
        
	}
 
    // where the magic happens; finds all the prime numbers for a given vector of even numbers
    int goldbachConjecture(int bound){
	vector<int> even_numbers = evengen(bound);
        for(int jj = 0; jj < even_numbers.size(); jj++){
            int prime = 0;
            vector<int> prime_vec;
            while(prime < even_numbers[jj]){
                    prime = nextprime();
                  //  cout << "this is prime: " << prime << endl;
                  //  if (prime <= even_numbers[jj]){
                        prime_vec.push_back(prime);
                   // }
                }
                clear_values();
                int idx = 0; int jdx = 1; int pivot = 0;
                checkPrime(prime_vec, idx, jdx, pivot, even_numbers[jj]);
         }
         return 0;
        }
};

int main() {
    int bound;
    cin >> bound;
    primegenerator sequence;
    sequence.goldbachConjecture(bound);
            return  0;
}
