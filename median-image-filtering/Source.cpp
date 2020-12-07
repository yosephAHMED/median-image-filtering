#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cstdlib>

using namespace std;

// random input function prototype
void generateRandomInput(int* arr, int N, int n);

// OrderStatistic function prototype
int kthSmallest(int* arr, int l, int r, int k);

int main() {

    ofstream outFile;
    outFile.open("results.txt");

    // computer internal clock controls the choice of the seed
    srand(unsigned(time(NULL)));

    // variables to determine running time of algorithms
    using namespace std::chrono;
    high_resolution_clock::time_point t1, t2;
    chrono::duration<double, milli> runningTime;

    // Population size array
    int N[3] = { 5000, 8000, 10000 };

    // Sample size array
    int n[6] = { 100, 300, 500, 1000, 2000, 4000 };
    
    // variable to store k, ith smallest number
    int k;

    // the pointer that will be used in dynamic array allocation
    int* arr;

    // variable to store the value returned from kthSmallest
    int result;

    for (int sampleSizeIndex = 0; sampleSizeIndex < 6; sampleSizeIndex++) {
        outFile << "Sample size: " << n[sampleSizeIndex] << endl;

        for (int populationSizeIndex = 0; populationSizeIndex < 3; populationSizeIndex++) {
            outFile << setw(18) << "\tPopulation size: " << N[populationSizeIndex] << endl;

            // find the kth smallest value 5 times for the boundaries
            for (int i = 0; i < 5; i++) {
                // allocate a dynamic array of size n
                arr = new int[n[sampleSizeIndex]];

                // generate n number of random, unordered inputs from [1..N]
                generateRandomInput(arr, N[populationSizeIndex], n[sampleSizeIndex]);

                // pick a random value from 1..n
                k = rand() % n[sampleSizeIndex] + 1;

                // find kth smallest number and obtain running time
                t1 = high_resolution_clock::now();
                result = kthSmallest(arr, 0, n[sampleSizeIndex] - 1, k);
                t2 = high_resolution_clock::now();
                runningTime = t2 - t1;

                // output result to file
                outFile << setw(12) << right << k << "th smallest: " << setw(5) << result;
                outFile << setw(18) << right << "Running time: " << setw(5) << runningTime.count() << endl;

                // delete the dynamic array for re-initialization
                delete[] arr;
            }
        }
    }

	system("pause");
	return 0;
}