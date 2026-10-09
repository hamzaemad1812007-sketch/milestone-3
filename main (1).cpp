#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Sorter {
public:

    void mergeSort(int arr[], int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;

            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);

            merge(arr, l, m, r);
        }
    }

    void quickSort(int arr[], int low, int high, long long& counter) {
        if (low < high) {
            int pi = partition(arr, low, high, counter);

            quickSort(arr, low, pi - 1, counter);
            quickSort(arr, pi + 1, high, counter);
        }
    }

    void quickSortM3(int arr[], int low, int high, long long& counter) {
        if (low < high) {
            int pi = partitionM3(arr, low, high, counter);

            quickSortM3(arr, low, pi - 1, counter);
            quickSortM3(arr, pi + 1, high, counter);
        }
    }

private:

    void merge(int arr[], int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;

        vector<int> L(n1), R(n2);

        for (int i = 0; i < n1; i++) {
            L[i] = arr[l + i];
        }

        for (int j = 0; j < n2; j++) {
            R[j] = arr[m + 1 + j];
        }

        int i = 0;
        int j = 0;
        int k = l;

        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
        }

        while (i < n1) {
            arr[k++] = L[i++];
        }

        while (j < n2) {
            arr[k++] = R[j++];
        }
    }

    int partition(int arr[], int low, int high, long long& counter) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            counter++;

            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }

        swap(arr[i + 1], arr[high]);

        return i + 1;
    }

    int medianOfThree(
        int arr[], int low, int high, long long& counter
    ) {
        int mid = low + (high - low) / 2;

        // Sort the three candidate values.
        counter++;
        if (arr[low] > arr[mid]) {
            swap(arr[low], arr[mid]);
        }

        counter++;
        if (arr[low] > arr[high]) {
            swap(arr[low], arr[high]);
        }

        counter++;
        if (arr[mid] > arr[high]) {
            swap(arr[mid], arr[high]);
        }

        // The median is now at arr[mid].
        // Move it to the last position for partition().
        swap(arr[mid], arr[high]);

        return high;
    }

    int partitionM3(
        int arr[], int low, int high, long long& counter
    ) {
        medianOfThree(arr, low, high, counter);

        return partition(arr, low, high, counter);
    }
};

void printArr(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    Sorter s;

    const int n = 8;

    int a[] = {64, 25, 12, 22, 11, 90, 45, 34};
    int tmp[n];

    // Merge Sort
    copy(a, a + n, tmp);
    s.mergeSort(tmp, 0, n - 1);

    cout << "MS: ";
    printArr(tmp, n);

    // Quick Sort using last-element pivot
    long long c1 = 0;

    copy(a, a + n, tmp);
    s.quickSort(tmp, 0, n - 1, c1);

    cout << "QS: ";
    printArr(tmp, n);
    cout << "QS comparisons: " << c1 << endl;

    // Sorted array
    int sorted[] = {1, 2, 3, 4, 5, 6, 7, 8};

    // Standard Quick Sort on sorted array
    c1 = 0;

    copy(sorted, sorted + n, tmp);
    s.quickSort(tmp, 0, n - 1, c1);

    cout << "QS sorted: ";
    printArr(tmp, n);
    cout << "QS sorted comparisons: " << c1 << endl;

    // Median-of-three Quick Sort on sorted array
    long long c2 = 0;

    copy(sorted, sorted + n, tmp);
    s.quickSortM3(tmp, 0, n - 1, c2);

    cout << "QSM3 sorted: ";
    printArr(tmp, n);
    cout << "QSM3 sorted comparisons: " << c2 << endl;

    return 0;
}