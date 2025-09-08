#include <iostream>
#include <cassert> 

class B2A2 {
public:
    int compare_cnt = 0; // Counts number of element comparisons

    // Public interface to run merge sort
    void mergeSort(int arr[], int n) {
        int* tmpArray = new int[n];
        for(int i = 0; i < n; ++i) {
            tmpArray[i] = arr[i];
        }
        mergeSort(arr, tmpArray, 0, n);
        delete[] tmpArray;
    }

private:
    // Recursive merge sort on subarray [left, right)
    void mergeSort(int target[], int source[], int left, int right) {
        if (right - left <= 1) return;  // Base case: single element is sorted

        int mid = (left + right) / 2;
        // Recursive calls, swap roles of source and target arrays
        mergeSort(source, target, left, mid);
        mergeSort(source, target, mid, right);

        int i = left, j = mid, k = left;
        while (i < mid && j < right) {
            compare_cnt++;
            if (source[i] < source[j]) {
                target[k++] = source[i++];
            } else {
                target[k++] = source[j++];
            }
        }
        while (i < mid) {
            target[k++] = source[i++];
        }
        while (j < right) {
            target[k++] = source[j++];
        }
    }

public:
    // Utility to print arrays
    void printArray(int arr[], int n) {
        for (int i = 0; i < n; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    B2A2 sorter;
    int n;
    std::cin >> n;
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    sorter.mergeSort(arr, n);

    sorter.printArray(arr, n);

    // Validate sorting correctness after merge sort
    for (int i = 0; i < n - 1; i++) {
        assert(arr[i] <= arr[i + 1]);
    }

    std::cout << "\nFeld ist sortiert!" << std::endl;
    std::cout << "Das Sortieren des Arrays hat " << sorter.compare_cnt << " Vergleiche benoetigt." << std::endl;

    delete[] arr;
    return 0;
}
