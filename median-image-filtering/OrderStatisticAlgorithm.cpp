#include<iostream> 
#include<climits> 
#include<cstdlib> 
using namespace std;

int randomPartition(int* arr, int l, int r);

/* 
kthSmallest returns k'th smallest element in arr[l..r] using QuickSort based method
ASSUMPTION: ALL ELEMENTS IN arr[] ARE DISTINCT
*/
int kthSmallest(int* arr, int l, int r, int k)
{
    // Check If k(the element we are looking for) is smaller than number of elements in array 
    if (k > 0 && k <= r - l + 1)
    {
        // Partition the array around last element and get 
        // position of pivot element in sorted array 
        int pos = randomPartition(arr, l, r);

        // If position is same as k 
        if (pos - l == k - 1)
            return arr[pos];
        if (pos - l > k - 1)  // If position is more, recur for left subarray 
            return kthSmallest(arr, l, pos - 1, k);

        // Else recur for right subarray 
        return kthSmallest(arr, pos + 1, r, k - pos + l - 1);
    }

    // If k is more than number of elements in array 
    return INT_MAX;
}

/* 
Standard partition process of QuickSort(). 
It considers the last element as pivot 
moves all smaller element to left of it and greater elements to right 
*/
int partition(int* arr, int l, int r)
{
    // x is pivot element
    int x = arr[r], i = l, temp;

    // going from left to right
    for (int j = l; j <= r - 1; j++)
    {
        if (arr[j] <= x)
        {
            // temp is equal to first element at left
            temp = arr[i];
            
            // element smaller than pivot is shifted to the left
            arr[i] = arr[j];

            // first element is copied
            arr[j] = temp;

            // increment i
            i++;
        }
    }

    // swapping pivot into place
    temp = arr[i];
    arr[i] = arr[r];
    arr[r] = temp;
    return i;
}

int randomPartition(int* arr, int l, int r)
{
    // n corresponds to the number of elements
    int n = r - l + 1;

    // pivot element is randomized within the range of n
    int pivot = rand() % n;

    // swap pivot with element at right most index
    int temp = arr[l + pivot];
    arr[l + pivot] = arr[r];
    arr[r] = temp;

    // partition arr into sorted sublists based on pivot element
    return partition(arr, l, r);
}