#include <iostream>
#include <vector>
#include "sort.h"
#include "matrix.h"

using namespace sort;

void bubbleSelection::Sort(unique_ptr<Matrix>& matrix) {
    int rows = matrix->getRows();
    int column = matrix->getColumn();
    for (int i = 0; i < rows; i++) {
        vector<int> evenElements;
        // Собираем все четные элементы в строке
        for (int j = 0; j < column; j++) {
            if (matrix->getElement(i, j) % 2 == 0) {
                evenElements.push_back(matrix->getElement(i, j));
            }
        }
        // Сортируем четные элементы методом пузырька
        for (int j = 0; j < evenElements.size() - 1; j++) {
            for (int k = 0; k < evenElements.size() - j - 1; k++) {
                IncrementComparisonCountInThread(); // Увеличиваем счетчик сравнений в текущем потоке
                if (evenElements[k] > evenElements[k + 1]) {
                    int temp = evenElements[k];
                    evenElements[k] = evenElements[k + 1];
                    evenElements[k + 1] = temp;
                    IncrementSwapCountInThread(); // Увеличиваем счетчик перестановок в текущем потоке
                }
            }
        }
        // Заменяем четные элементы в строке на отсортированные
        int evenIndex = 0;
        for (int j = 0; j < column; j++) {
            if (matrix->getElement(i, j) % 2 == 0) {
                matrix->setElement(i, j, evenElements[evenIndex]);
                evenIndex++;
            }
        }
    }
}
