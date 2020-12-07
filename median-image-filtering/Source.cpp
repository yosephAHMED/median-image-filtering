#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cstdlib>

using namespace std;

// random input function prototype
void generateRandomInput(int* arr, int N, int n);

// array average function prototype
double arrAverage(double arr[], int n);

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
    chrono::duration<double, nano> runningTime;

    // Population size array
    int N[3] = { 5000, 8000, 10000 };

    // Sample size array
    int n[6] = { 100, 300, 500, 1000, 2000, 4000 };
    
    // array to store random k, ith smallest number
    int* k = new int[5];

    // the pointer that will be used in dynamic array allocation
    int* arr;

    // variable to store the value returned from kthSmallest
    int result;

    // array to store running time on order i and average of averages
    double arrRT[5], averageRT[3];

    for (int sampleSizeIndex = 0; sampleSizeIndex < 6; sampleSizeIndex++) {
        outFile << "Sample size: " << n[sampleSizeIndex] << endl;
        
        // obtain 5 random values for k from [1..n]
        generateRandomInput(k, n[sampleSizeIndex], 5);

        for (int populationSizeIndex = 0; populationSizeIndex < 3; populationSizeIndex++) {
            outFile << setw(18) << "\tPopulation size: " << N[populationSizeIndex] << endl;

            // find the kth smallest value 5 times for the boundaries
            for (int i = 0; i < 5; i++) {
                // allocate a dynamic array of size n
                arr = new int[n[sampleSizeIndex]];

                // generate n number of random, unordered inputs from [1..N]
                generateRandomInput(arr, N[populationSizeIndex], n[sampleSizeIndex]);

                // find kth smallest number
                t1 = high_resolution_clock::now();
                result = kthSmallest(arr, 0, n[sampleSizeIndex] - 1, k[i]);
                t2 = high_resolution_clock::now();

                // obtain running time
                runningTime = t2 - t1;

                // store running time in array
                arrRT[i] = runningTime.count();

                // output result to file
                outFile << setw(12) << right << k[i] << "th smallest: " << setw(5) << result;
                outFile << setw(18) << right << "Running time: " << setw(5) << runningTime.count() << " ns" << endl;

                // delete the dynamic array for re-initialization
                delete[] arr;
            }

            // store the average running time for pop. size N of sample size n
            averageRT[populationSizeIndex] = arrAverage(arrRT, 5);

            // write average running time to file
            outFile << setw(48) << right << "Average Running time: " << setw(5) << arrAverage(arrRT, 5) << " ns" << endl;
        }
        // write average RT of averages to file
        outFile << setw(57) << "Average RT across Populations: " << arrAverage(averageRT, 3) << " ns" << endl;
    }

	system("pause");
	return 0;
}