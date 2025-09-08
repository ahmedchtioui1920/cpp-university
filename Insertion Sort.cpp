#include <iostream>
#include <cassert>

class B2A1 {
public:
    int compare_cnt; // Counts number of element comparisons

    // Check if array is sorted ascending
    bool isSorted(const int array[], int n) {
        for (int i = 0; i < n - 1; i++) {
            if (array[i] > array[i + 1]) return false;
        }
        return true;
    }

    // Insertion Sort algorithm with comparison counting
    void insertionSort(int numbers[], int size) {
        compare_cnt = 0;
        for (int i = 1; i < size; ++i) {
            int key = numbers[i];
            int j = i - 1;
            while (j >= 0) {
                compare_cnt++;
                if (numbers[j] > key) {
                    numbers[j + 1] = numbers[j];
                    j--;
                } else {
                    break;
                }
            }
            numbers[j + 1] = key;
        }
    }
};

int main() {
    B2A1 sorter;
    int n;
    std::cin >> n;
    int* numbers = new int[n];

    for (int i = 0; i < n; i++) {
        std::cin >> numbers[i];
    }

    // Print unsorted array if size <= 100
    if (n <= 100) {
        for (int i = 0; i < n; i++) {
            std::cout << numbers[i] << " ";
        }
        std::cout << std::endl;
    }

    sorter.insertionSort(numbers, n);

    // Validate sorting correctness
    assert(sorter.isSorted(numbers, n));

    // Print sorted array if size <= 100
    if (n <= 100) {
        for (int i = 0; i < n; i++) {
            std::cout << numbers[i] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Feld ist sortiert!" << std::endl;
    std::cout << "Das Sortieren des Arrays hat " << sorter.compare_cnt << " Vergleiche benoetigt." << std::endl;

    delete[] numbers;
    return 0;
}
