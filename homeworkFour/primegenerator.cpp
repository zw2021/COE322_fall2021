#include <iostream>
#include <cmath>
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

};
/*
int main() {
    int nprimes;
    cout << "Enter Number of Primes: " << endl;
    cin >> nprimes;
    primegenerator sequence;
    while (sequence.number_of_primes_found()<nprimes) {
        int number = sequence.nextprime();
        cout << "Number " << number << " is prime" << endl;
    }

}
*/