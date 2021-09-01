#include <iostream>
#include <vector>

using namespace std;

//## <SUMMARY> #############################################################################
/*This code implements two functions: "sumEvenElem" and "sumEles_EvenInd", which sums the elements within a user specified
vector of integers. Details are as follows:

    "sumEvenElem" sums all even elements in the user specified vector
    "sumEles_EvenInd" sums all elements with even indices in the user specified vector

While the homework statement specifies writing 2 loops per task, these tasks are specified into individual function
handles for conciseness and usability.*/
//##########################################################################################

int sumEvenElem(vector<int> vec){
            int vecSize = vec.size();
            int runningSum = 0;
            int dummy;

            for(int ii = 0; ii < vecSize; ii++){

                if(vec[ii]%2 == 0){ // find all even elements
                    dummy = vec[ii];
                    runningSum = dummy+runningSum;
                }
            }

            cout << "Sum of all Even Elements in Given Vector: " << runningSum << endl;
            return runningSum;
}

int sumEles_EvenInd(vector<int> vec){
            int vecSize = vec.size();
            int runningSum = 0;
            int dummy;

            for(int ii = 0; ii < vecSize; ii++){

                if(ii%2 == 0){ // find all even indices; assume 0 == 2
                    dummy = vec[ii];
                    runningSum = dummy+runningSum;
                }
            }

            cout << "Sum of all Elements with Even Indices in Given Vector: " << runningSum << endl;
            return runningSum;
}

int main() {

    //vector<int> myVec{-2, 4, 3, 6, 8};
    vector<int> myVec;
    int input, size;

    cout << "Enter Size of Vector: " << endl;
    cin >> size;
    for(int ii = 0; ii < size; ii++){
        cout << "Enter Number: " << endl;
        cin >> input;
        myVec.push_back(input);
    }

    sumEvenElem(myVec);
    sumEles_EvenInd(myVec);
    std::cout << "End of Computation" << std::endl;
    return 0;
}
