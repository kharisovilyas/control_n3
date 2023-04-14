#include <iostream>
#include "sort.h"

using namespace sort;

void insertion::Sort(unique_ptr<Matrix>& matrix) {
    int rows = matrix->getRows();
    int column = matrix->getColumn();
    for (int i = 0; i < rows; i++) {
        bool hasEven = false;
        for (int j = 0; j < column; j++) {
            int element = matrix->getElement(i, j);
            if (possibleSort(element)) {
                hasEven = true;
                break;
            }
        }
        if (hasEven) {
            for (int j = 1; j < column; j++) {
                int key = matrix->getElement(i, j);
                if (possibleSort(key)) {
                    int k = j - 1;
                    while (k >= 0 && possibleSort(matrix->getElement(i, k)) && matrix->getElement(i, k) > key) {
                        IncrementComparisonCountInThread();
                        IncrementSwapCountInThread();
                        matrix->setElement(i, k + 1, matrix->getElement(i, k));
                        k--;
                    }
                    IncrementComparisonCountInThread();
                    matrix->setElement(i, k + 1, key);
                }
            }
        }
    }
}