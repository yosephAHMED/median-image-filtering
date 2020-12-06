#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cstdlib>

using namespace std;

/* The generateRandomInput() function generates n random 
numbers in the range of [1..N], which are unordered.
*/
void generateRandomInput(int* arr, int N, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % N + 1;
    }
}

//int main() {
//
//    ofstream outFile;
//    outFile.open("results.txt");
//
//    // computer internal clock controls the choice of the seed
//    srand(unsigned(time(NULL)));
//
//    int* arr = new int[10];
//    generateRandomInput(arr, 10);
//
//	system("pause");
//	return 0;
//}