#include <iostream>
#include <algorithm>

/**
 * Removes duplicates from the array.
 * After sorting, it moves unique elements to the front of the array.
 * @param data Array of integers (will be modified in-place)
 * @param n Number of elements in the array
 * @return Number of unique elements remaining
 */
int removeDuplicates(int data[], int n) {
    if (n == 0) // If array is empty, return zero
        return 0;

    // Sort the array so duplicates come together
    std::sort(data, data + n);

    int m = 1; // At least one unique element (the first one)

    // Traverse array, moving unique elements forward
    for (int i = 1; i < n; i++) {
        if (data[i] != data[m - 1]) {
            data[m] = data[i];
            m++;
        }
    }

    return m; // Return count of unique elements
}

/**
 * Recursively generates and prints all k-element subsets of the data array.
 * Uses backtracking to build subsets efficiently.
 * @param data Sorted array without duplicates
 * @param n Number of unique elements in data
 * @param k Desired subset size
 * @param start Current index in data to consider
 * @param subset Temporary array holding current subset elements
 * @param subsetSize Current number of elements selected in subset
 * @param count Reference to total count of subsets printed
 */
void printSubsets(int data[], int n, int k, int start, int subset[], int subsetSize, int &count) {
    // Base case: if subset size reached k, print the subset
    if (subsetSize == k) {
        for (int i = 0; i < k; i++) {
            std::cout << subset[i] << " ";
        }
        std::cout << std::endl;
        count++; // Increment subsets count
        return;
    }

    // Iterate over remaining elements ensuring enough left to fill subset
    for (int i = start; i <= n - (k - subsetSize); i++) {
        subset[subsetSize] = data[i]; // Choose element data[i]
        // Recurse picking next element from index i+1
        printSubsets(data, n, k, i + 1, subset, subsetSize + 1, count);
        // Backtracking occurs automatically as subsetSize is increased/decreased through recursion
    }
}

int main() {
    int n, k; // n = number of elements, k = subset size
    std::cin >> n >> k; // Read input values from standard input

    int *array = new int[n]; // Dynamically allocate array for input numbers

    // Read n integers into array
    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }

    // Print array before removing duplicates
    std::cout << "Before removing duplicates: ";
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    // Remove duplicates and get the new count of unique elements
    int distinct = removeDuplicates(array, n);

    // Print array after duplicate removal
    std::cout << "After removing duplicates: ";
    for (int i = 0; i < distinct; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    // Adjust k if it is greater than number of unique elements
    if (k > distinct) {
        k = distinct;
    }

    // If k is zero, no subsets to generate
    if (k == 0) {
        std::cout << "Number of subsets: 0" << std::endl;
        delete[] array;
        return 0;
    }

    int *subset = new int[k]; // Temporary array to hold the current subset during recursion
    int count = 0;            // Counter for the number of subsets printed

    // Generate and print all k-element subsets of the distinct elements
    printSubsets(array, distinct, k, 0, subset, 0, count);

    // Print total number of subsets generated
    std::cout << "Number of subsets: " << count << std::endl;

    // Clean up dynamically allocated memory
    delete[] subset;
    delete[] array;

    return 0;
}
