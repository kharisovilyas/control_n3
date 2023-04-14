#include "Isort.h"
#include "sort.h"

using namespace sort;

void quickSort::Sort(unique_ptr<Matrix>& matrix) {
    int rows = matrix->getRows();
    for (int i = 0; i < rows; i++) {
        QuickSortRecursive(matrix, 0, matrix->getColumn() - 1, i);
    }
}

void quickSort::QuickSortRecursive(unique_ptr<Matrix>& matrix, int left, int right, int row) {
    if (left >= right) {
        return;
    }
    // Находим первый четный элемент в подмассиве
    int firstEvenIndex = left;
    while (firstEvenIndex <= right && matrix->getElement(row, firstEvenIndex) % 2 != 0) {
        firstEvenIndex++;
    }
    if (firstEvenIndex > right) {
        return; // Если в подмассиве нет четных элементов, то подмассив уже отсортирован
    }
    int pivotIndex = firstEvenIndex;
    int pivotValue = matrix->getElement(row, pivotIndex);
    // Проходим по подмассиву и перемещаем все четные элементы в левую часть, а нечетные - в правую часть
    for (int j = firstEvenIndex + 1; j <= right; j++) {
        IncrementComparisonCountInThread(); // Увеличиваем счетчик сравнений в текущем потоке
        int currentValue = matrix->getElement(row, j);
        if (possibleSort(currentValue) && currentValue < pivotValue) {
            pivotIndex++;
            matrix->swapElements(row, pivotIndex, row, j);
            IncrementSwapCountInThread(); // Увеличиваем счетчик перестановок в текущем потоке
        }
    }
    // Перемещаем опорный элемент на место, где заканчивается левая часть массива с четными элементами
    matrix->swapElements(row, pivotIndex, row, left + pivotIndex - firstEvenIndex);
    IncrementSwapCountInThread(); // Увеличиваем счетчик перестановок в текущем потоке
    // Рекурсивно вызываем QuickSortRecursive для левой и правой частей массива
    QuickSortRecursive(matrix, left, left + pivotIndex - firstEvenIndex - 1, row);
    QuickSortRecursive(matrix, left + pivotIndex - firstEvenIndex + 1, right, row);
}