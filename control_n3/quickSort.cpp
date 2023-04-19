#include "Isort.h"
#include "sort.h"

using namespace sort;

pair<int, int> quickSorting(vector<int>& row, int left, int right) {
    int i = left, j = right;
    pair<int, int> counts;
    int pivot = row[(left + right) / 2];
    while (i <= j) {
        while (row[i] < pivot) {
            counts.second++;
            i++;
        }
        while (row[j] > pivot) {
            counts.second++;
            j--;
        }
        if (i <= j) {
            swap(row[i], row[j]);
            counts.first++;
            i++;
            j--;
        }
    }
    if (left < j) {
        auto sub_counts = quickSorting(row, left, j);
        counts.first += sub_counts.first;
        counts.second += sub_counts.second;
    }
    if (i < right) {
        auto sub_counts = quickSorting(row, i, right);
        counts.first += sub_counts.first;
        counts.second += sub_counts.second;
    }
    return counts;
}


void quickSort::Sort(unique_ptr<Matrix>& matrix) {
    int rows = matrix->getRows();
    int column = matrix->getColumn();
    vector<int> row{};
    vector<pair<int, int>> countsVector;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < column; j++) {
            int element = matrix->getElement(i, j);
            if (possibleSort(element)) {
                row.push_back(element);
            }
        }
        pair<int, int> counts = quickSorting(row, 0, static_cast<int>(row.size()) - 1);
        countsVector.push_back(counts);
        int iter = 0;
        for (int j = 0; j < column; j++) {
            int element = matrix->getElement(i, j);
            if (possibleSort(element)) {
                matrix->setElement(i, j, row[iter]);
                iter++;
            }
        }
        row.clear();
    }
    int totalSwaps = 0;
    int totalComparisons = 0;
    for (const auto& counts : countsVector) {
        totalSwaps += counts.first;
        totalComparisons += counts.second;
    }
    ISort::SetIncrementSwapCount(totalSwaps);
    ISort::SetIncrementComparisonCount(totalComparisons);
}
