#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <cstdlib>

extern "C" {
#include "imageio.h"
}

using namespace std;

// random input function prototype
void generateRandomInput(int* arr, int N, int n);

// array average function prototype
double arrAverage(double arr[], int n);

// OrderStatistic function prototype
int kthSmallest(int* arr, int l, int r, int k);

void orderStatisticExperiment() {
    cout << "Running Order Statistic Experiment" << endl;

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
    outFile.close();
}

void medianImageFiltering() {
    int windowSize;
    int imageArr[2000][2000];
    int medArr[2000][2000];

    cout << "Median image filtering selected" << endl;
    cout << "Enter window size: ";
    cin >> windowSize;

    // (n x n) window
    int* window = new int[windowSize*windowSize];
    int numWindowEle = windowSize * windowSize;

    int row = 0, col = 0, numRows = 0, numCols = 0, max = 0;

    ifstream infile("noisyImageFiftyHundred.pgm");
    stringstream ss;
    string inputLine = "";

    // First line of .pgm file contains version 
    getline(infile, inputLine);
    if (inputLine.compare("P2") != 0) cerr << "Version error" << endl;
    else cout << "Version : " << inputLine << endl;

    // Continue with a stringstream 
    ss << infile.rdbuf();

    // Secondline : size of image (cols by rows)
    // Thirdline : max intensity of a pixel (0-255)
    ss >> numCols >> numRows >> max;

    //print total number of rows, columns and maximum intensity of image 
    cout << numCols << " columns and " << numRows << " rows" << endl << "Maximium Intesity "<< max <<endl;  

    //Initialize a new array of same size of image with 0 
    for (row = 0; row <= numRows; ++row)
        imageArr[row][0] = 0;
    for (col = 0; col <= numCols; ++col)
        imageArr[0][col] = 0;

    // Copying the data from .pgm to imageArr
    for (row = 1; row <= numRows; ++row)
    {
        for (col = 1; col <= numCols; ++col)
        {
            //original data store in new array 
            ss >> imageArr[row][col];
        }
    }

    for (int row = 1; row < numRows - windowSize + 1; ++row)
    {
        for (int col = 1; col < numCols - windowSize + 1; ++col)
        {
            // Copy window
            for (int y = 0; y < windowSize; ++y)
            {
                for (int x = 0; x < windowSize; ++x)
                {
                    window[y * windowSize + x] = imageArr[row + y][col + x];
                }
            }

            // window's "center"
            int cx = col + windowSize / 2;
            int cy = row + windowSize / 2;

            // apply order statistic to window array and store the median in the new array 
            medArr[row][col] = kthSmallest(window, 0, numWindowEle - 1, numWindowEle / 2);
        }
    }

    ofstream outfile;

    //new file open to stroe the output image 
    outfile.open("Medianfilter.pnm");
    outfile << "P2" << endl;
    outfile << numCols << " " << numRows << endl;
    outfile << "255" << endl;

    for (row = 1; row <= numRows; ++row)
    {
        for (col = 1; col <= numCols; ++col)
        {
            //store resultant pixel values to the output file 
            outfile << medArr[row][col] << " ";
        }
    }

    outfile.close();
    infile.close();
}

int main() {
    int userChoice = -1, windowSize;

    cout << "1: Run order statistic experiment" << endl;
    cout << "2: Apply median image filtering" << endl;
    cin >> userChoice;

    switch (userChoice) {
    case 1:
        orderStatisticExperiment();
        break;
    case 2:
        medianImageFiltering();
        break;
    }

	system("pause");
	return 0;
}