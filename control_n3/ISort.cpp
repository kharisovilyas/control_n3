#include "ISort.h"

void ISort::sortPossible(
    unique_ptr<Matrix>& matrix,
    void (*function)(vector<int>&, pair<int, int>&)
){

    int rows = matrix->getRows();
    int column = matrix->getColumn();
    vector<int> row{};
    pair<int, int> counts{};
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < column; j++) {
            int element = matrix->getElement(i, j);
            if (possibleSort(element)) {
                row.push_back(element);
            }
        }
        (*function)(row, counts);
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

    SetIncrementSwapCount(counts.first);
    SetIncrementComparisonCount(counts.second);

}
