// The arrAverage() function returns the average for an array of size n
using namespace std;

double arrAverage(double arr[], int n) {
	float sum = 0;
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	return sum / n;
}