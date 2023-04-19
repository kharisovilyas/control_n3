#include <iostream>
#include "sort.h"

using namespace sort;

void sortRowByShell(vector<int>& row, pair<int, int>& counts) {
    int n = static_cast<int> (row.size());
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = row[i];
            int j;
            for (j = i; j >= gap && row[j - gap] > temp; j -= gap) {
                counts.second++;
                row[j] = row[j - gap];
                counts.first++;
            }
            row[j] = temp;
            counts.first++;
        }
    }
}


void shell::Sort(unique_ptr<Matrix>& matrix) {
    int rows = matrix->getRows();
    int column = matrix->getColumn();
    vector<int> row{};
    sortPossible(matrix, &sortRowByShell);
}