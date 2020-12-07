/* The generateRandomInput() function generates n random
numbers in the range of [1..N], which are unordered.
*/
#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
using namespace std;

void generateRandomInput(int* arr, int N, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % N + 1;
    }
}