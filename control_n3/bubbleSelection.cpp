#include <iostream>
#include <vector>
#include "sort.h"
#include "matrix.h"

using namespace sort;

void sortRowByBubble(vector<int>& row, pair<int, int>& counts) {
    int n = static_cast<int> (row.size());
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (row[j] > row[j + 1]) {
                counts.second++;
                int temp = row[j];
                row[j] = row[j + 1];
                counts.first++;
                row[j + 1] = temp;
                counts.first++;
            }
        }
    }
}


void bubbleSelection::Sort(unique_ptr<Matrix>& matrix) {
    int rows = matrix->getRows();
    int column = matrix->getColumn();
    vector<int> row{};
    sortPossible(matrix, &sortRowByBubble);
}
