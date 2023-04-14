#include <iostream>
#include "sort.h"

using namespace sort;

void shell::Sort(unique_ptr<Matrix>& matrix) {
    int rows = matrix->getRows();
    int column = matrix->getColumn();
    for (int i = 0; i < rows; i++) {
        int gap = column / 2;
        while (gap > 0) {
            for (int j = gap; j < column; j++) {
                int temp = matrix->getElement(i, j);
                int k = j;
                while (k >= gap && possibleSort(matrix->getElement(i, k - gap)) &&
                    (!possibleSort(temp) || matrix->getElement(i, k - gap) > temp)) {
                    IncrementComparisonCountInThread();
                    IncrementSwapCountInThread();
                    matrix->setElement(i, k, matrix->getElement(i, k - gap));
                    k -= gap;
                }
                IncrementComparisonCountInThread();
                matrix->setElement(i, k, temp);
            }
            gap /= 2;
        }
    }
}