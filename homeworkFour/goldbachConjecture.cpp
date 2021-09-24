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
        last_number_tested = 0;
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
        last_number_tested = 0;
        return how_many_primes_found, last_number_tested;
    }
};

int main() {

    // run next prime until last number tested = input number
    vector<int> even_numbers{10, 4, 8, 12 , 20};

    primegenerator sequence;
    for(int jj = 0; jj <= even_numbers.size(); jj++){//even_number = 4;
        int prime = 0;
        vector<int> prime_vec;
        while(prime < even_numbers[jj]){
                prime = sequence.nextprime();
                if (prime < even_numbers[jj]){
                    prime_vec.push_back(prime);
                }
            }
        sequence.clear_values();

        for(int ii = 0; ii < prime_vec.size(); ii++){
            int num = prime_vec.back() + prime_vec[ii];
            if(num == even_numbers[jj]){
                    cout << prime_vec[ii] << " and " << prime_vec.back() << endl;
                }
            }
        }
            return  0;

}