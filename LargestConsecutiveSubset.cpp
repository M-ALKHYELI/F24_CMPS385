#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

// Function to find the largest subset of consecutive numbers
int findLargestConsecutiveSubset(vector<int>& inputSet) {
    // Create an unordered_set (hash table) to store numbers for O(1) lookup
    unordered_set<int> hash;
    int maxLength = 0; // Variable to store the length of the largest subset

    // Insert all numbers into the hash table
    for (int num : inputSet) {
        hash.insert(num);
    }

    // Iterate through each number in the input set
    for (int num : inputSet) {
        // Check if the current number is the start of a sequence
        if (hash.find(num - 1) == hash.end()) { // If `num - 1` is not in the hash table
            int currentNum = num;
            int currentLength = 1; // Length of the current sequence

            // Check for consecutive numbers
            while (hash.find(currentNum + 1) != hash.end()) {
                currentNum++; // Move to the next number
                currentLength++; // Increment the length of the sequence
            }

            // Update the maximum length found so far
            maxLength = max(maxLength, currentLength);
        }
    }

    return maxLength; // Return the largest subset length
}

int main() {
    // Input vector containing the numbers
    vector<int> inputSet = {1, 3, 8, 14, 4, 10, 2, 11};

    // Find and print the largest subset of consecutive numbers
    cout << "Length of the largest subset of consecutive numbers: "
         << findLargestConsecutiveSubset(inputSet) << endl;

    return 0;
}
