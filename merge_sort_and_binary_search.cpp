#include <iostream>
using namespace std;

// Function to merge two sorted subarrays into a single sorted array
void merge(int arr[], int left, int mid, int right) {
    // Calculate the sizes of two subarrays
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays to hold the values
    int leftArr[n1], rightArr[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into the original array
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elements from leftArr
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy any remaining elements from rightArr
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Recursive function to implement Merge Sort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Find the midpoint to divide the array into two halves
        int mid = left + (right - left) / 2;

        // Recursively sort the two halves
        mergeSort(arr, left, mid);      // Sort the left half
        mergeSort(arr, mid + 1, right); // Sort the right half

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Function to implement Binary Search
int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;

    // Continue searching as long as the left index is less than or equal to the right index
    while (left <= right) {
        // Find the midpoint
        int mid = left + (right - left) / 2;

        // Check if the target is at the midpoint
        if (arr[mid] == target)
            return mid;

        // If the target is smaller, it must be in the left half
        if (arr[mid] > target)
            right = mid - 1;

        // If the target is larger, it must be in the right half
        else
            left = mid + 1;
    }

    // If the target is not found, return -1
    return -1;
}

int main() {
    // Example array for testing Merge Sort
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Display the original array
    cout << "Original array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Call Merge Sort to sort the array
    mergeSort(arr, 0, n - 1);

    // Display the sorted array
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Example Binary Search
    int target = 43;
    int result = binarySearch(arr, n, target);

    // Display the result of Binary Search
    if (result != -1)
        cout << "Element " << target << " found at index " << result << endl;
    else
        cout << "Element " << target << " not found in the array." << endl;

    return 0;
}
