//
// Created by huang on 9/18/2021.
//

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
    };
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
            cout << "These primes sum to the selected even number: " << vec[idx] << " and " << vec[jdx] << endl;
            return vec[idx], vec[jdx];
        }else if (vec[idx] + vec[idx] == even_num){ // a prime plus itself sums to even number
            cout << "This prime sums to the selected even number: " << vec[idx] << endl;
        }else if (vec[idx] + vec[jdx] > even_num  || vec[idx] + vec[jdx] < even_num){ // doesn't sum to even number
            jdx++;
            return checkPrime(vec, idx, jdx, pivot, even_num);
        }else if (vec[pivot] == vec.back()){ // reach end of vector and never reaches sum to even number
            cout << "None of the primes in the given vector will sum to the selected even number" << endl;
            return -1; // arbitrary number to show error
    }
    return  0;
    }

    // where the magic happens; finds all the prime numbers for a given vector of even numbers
    int goldbackConjecture(vector<int> even_numbers){
        for(int jj = 0; jj < even_numbers.size(); jj++){
            int prime = 0;
            vector<int> prime_vec;
            while(prime < even_numbers[jj]){
                    prime = nextprime();
                    cout << "this is prime: " << prime << endl;
                    if (prime <= even_numbers[jj]){
                        prime_vec.push_back(prime);
                    }
                }
                clear_values();
                int idx = 0; int jdx = 1; int pivot = 0;
                checkPrime(prime_vec, idx, jdx, pivot, even_numbers[jj]);
         }
         return 0;
        }
};

int main() {

    vector<int> even_numbers{8,4,6, 10, 12};// just can't use 2
    primegenerator sequence;
    sequence.goldbackConjecture(even_numbers);
            return  0;
}