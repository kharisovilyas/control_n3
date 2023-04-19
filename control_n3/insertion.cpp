#include <iostream>
#include "sort.h"
#include <vector>

using namespace sort;

void sortRowByInsert(vector<int>& row, pair<int, int>& counts){
    int n = static_cast<int>( row.size() );
    for (int i = 1; i < n; i++) {
        int key = row[i];
        int j = i - 1;
        while (j >= 0 && row[j] > key) {
            counts.second++;
            row[j + 1] = row[j];
            counts.first++;
            j--;
        }
        counts.first++;
        row[j + 1] = key;
    }
}

void insertion::Sort(unique_ptr<Matrix>& matrix) {
    int rows = matrix->getRows();
    int column = matrix->getColumn();
    vector<int> row{};
    sortPossible(matrix, &sortRowByInsert);
}
