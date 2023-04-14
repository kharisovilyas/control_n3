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
    // ������� ������ ������ ������� � ����������
    int firstEvenIndex = left;
    while (firstEvenIndex <= right && matrix->getElement(row, firstEvenIndex) % 2 != 0) {
        firstEvenIndex++;
    }
    if (firstEvenIndex > right) {
        return; // ���� � ���������� ��� ������ ���������, �� ��������� ��� ������������
    }
    int pivotIndex = firstEvenIndex;
    int pivotValue = matrix->getElement(row, pivotIndex);
    // �������� �� ���������� � ���������� ��� ������ �������� � ����� �����, � �������� - � ������ �����
    for (int j = firstEvenIndex + 1; j <= right; j++) {
        IncrementComparisonCountInThread(); // ����������� ������� ��������� � ������� ������
        int currentValue = matrix->getElement(row, j);
        if (possibleSort(currentValue) && currentValue < pivotValue) {
            pivotIndex++;
            matrix->swapElements(row, pivotIndex, row, j);
            IncrementSwapCountInThread(); // ����������� ������� ������������ � ������� ������
        }
    }
    // ���������� ������� ������� �� �����, ��� ������������� ����� ����� ������� � ������� ����������
    matrix->swapElements(row, pivotIndex, row, left + pivotIndex - firstEvenIndex);
    IncrementSwapCountInThread(); // ����������� ������� ������������ � ������� ������
    // ���������� �������� QuickSortRecursive ��� ����� � ������ ������ �������
    QuickSortRecursive(matrix, left, left + pivotIndex - firstEvenIndex - 1, row);
    QuickSortRecursive(matrix, left + pivotIndex - firstEvenIndex + 1, right, row);
}