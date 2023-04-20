#include <iostream>
#include "ui.h"
#include "sort.h"

using namespace sort;
using namespace ui;
using namespace std;

void waitForEnter() {
    while (true) {
        int ch = getchar();
        if (ch == EOF || ch == '\n') {
            break;
        }
    }
}

void controlSort::startSort(unique_ptr<Matrix>& matrix, unique_ptr<Matrix>& sortMatrix, map<string, pair<int, int>>& results) {
    bubbleSelection bubble{};
    insertion insert{};
    quickSort qSorting{};
    shell shell{};

    inOutConsole inout;

    int rows = matrix->getRows();
    int column = matrix->getColumn();
    sortMatrix = make_unique<Matrix>(rows, column);
    *sortMatrix = *matrix;
    bubble.Sort(sortMatrix);
    results["Сортировка пузырьком"] = make_pair(bubble.GetSwapCount(), bubble.GetComparisonCount());
    inout.outConsole(sortMatrix);
    sortMatrix = nullptr;
    cout << "Сортировка пузыриком прошла успешно! Нажмите enter для продолжения..." << endl;
    waitForEnter();


    sortMatrix = make_unique<Matrix>(rows, column);
    *sortMatrix = *matrix;
    insert.Sort(sortMatrix);
    results["Сортировка вставками"] = make_pair(insert.GetSwapCount(), insert.GetComparisonCount());
    inout.outConsole(sortMatrix);
    sortMatrix = nullptr;
    cout << "Сортировка вставками прошла успешно! Нажмите enter для продолжения..." << endl;
    waitForEnter();


    sortMatrix = make_unique<Matrix>(rows, column);
    *sortMatrix = *matrix;
    qSorting.Sort(sortMatrix);
    results["Быстрая сортировка"] = make_pair(qSorting.GetSwapCount(), qSorting.GetComparisonCount());
    inout.outConsole(sortMatrix);
    sortMatrix = nullptr;
    cout << "Быстрая сортировка прошла успешно! Нажмите enter для продолжения..." << endl;
    waitForEnter();


    sortMatrix = make_unique<Matrix>(rows, column);
    *sortMatrix = *matrix;
    shell.Sort(sortMatrix);
    results["Сортировка Шелла"] = make_pair(shell.GetSwapCount(), shell.GetComparisonCount());
    inout.outConsole(sortMatrix);
    cout << "Сортировка методом Шелла прошла успешно! Нажмите enter для продолжения..." << endl;
    waitForEnter();
}