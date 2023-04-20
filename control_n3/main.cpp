#include <iostream>
#include <vector>
#include <memory>
#include <locale>
#include <cstdlib> 
#include <map>
#include "ui.h"
#include "test.h"
#include "sort.h"

using namespace ui;
using namespace sort;
using namespace std;

enum { start = 1, taskreturn = 0 };
enum { exitp = 0, rfile = 1, rconsole = 2, random = 3};
enum { fileOutput = 1, coutput = 2, outreturn = 3 };


void printInputWays() {
    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "Как заполнить данные ?" << endl;
    cout << "Нажмите :" << endl;
    cout << "[1] - чтобы взять данные из файла" << endl;
    cout << "[2] - чтобы ввести данные в консоли" << endl;
    cout << "[3] - чтобы заполнить матрицу случайными значениями" << endl;
    cout << "[0] - чтобы выйти из программы" << endl << endl;
}

void printTestInfo() {
    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "Нажмите :" << endl;
    cout << "[1] - чтобы запустить модульные тесты" << endl;
    cout << "[0] - чтобы пропустить действие" << endl;
}

void printAction() {
    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "Нажмите :" << endl;
    cout << "[1] - чтобы начать сортировки" << endl;
    cout << "[0] - чтобы выйти и изменить данные" << endl;
}

void printOutputWays() {
    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "Пожалуйста выберете, как вы хотите получить результаты ?" << endl;
    cout << "Результаты: исходная и отсортированая матрицы и сравнительная таблица сортировок" << endl;
    cout << "Пункты меню :" << endl;
    cout << "[1] - в файл" << endl;
    cout << "[0] - в консоль" << endl;
}


StringEnumHelper selectInput(int variant, unique_ptr<Matrix>& matrix) {
    fileReader mReader{};
    correctness check{};
    inOutConsole inOut{};
    fillingRandom fill{};
    test testing{};
    string result{};
    auto cinBuf = cin.rdbuf();
    switch (variant)
    {
    case rfile:
        return mReader.readFile(matrix, {});
    case rconsole:
        return inOut.readConsole(matrix);
    case random:
        return fill.filling(matrix);
    case exitp:
        cout << "Вы вышли!" << endl;
        return StringEnumHelper(StringEnum::correct);
    default:
        return StringEnumHelper(StringEnum::correct);
    }
}

void selectOutput(bool needOutconsole, unique_ptr<Matrix>& oldMatrix, unique_ptr<Matrix>& sortMatrix, map<string, pair<int, int>>& results) {
    correctness check{};
    inOutConsole cInOut{};
    fileReader mReader{};
    if (!needOutconsole) {
        cInOut.outConsole(sortMatrix, results);
    }
    else {
        mReader.implFillFile(oldMatrix, sortMatrix, results);
    }
}

void launchMenu() {
    correctness check{};
    controlSort control{};
    test unitTest;
    string resultInput{};
    string resultInputCorrect = static_cast<string>(StringEnumHelper(StringEnum::correct));
    int variant = 0;
    bool isStart{};
    bool outConsole{};
    bool startUnitTest{};
    int boardMenu = random;
    unique_ptr<Matrix> matrix;
    unique_ptr<Matrix> sortMatrix;
    map<string, pair<int,int>> results;
    do
    {
        printTestInfo();
        startUnitTest = check.getBool();
        if (startUnitTest) unitTest.startTest();

        printInputWays();
        variant = check.getMenuVar(exitp, boardMenu);
        if (variant == exitp) {
            cout << "Вы вышли!" << endl;
            break;
        }
        resultInput = static_cast<string>(selectInput(variant, matrix));
        cout << endl << resultInput << endl;
        if (resultInput != resultInputCorrect) continue;

        inOutConsole out{};
        out.outConsole(matrix);

        printAction();
        isStart = check.getBool();
        if (!isStart) continue;
        control.startSort(matrix, sortMatrix, results);
        printOutputWays();
        outConsole = check.getBool();
        selectOutput(outConsole, matrix, sortMatrix, results);

    } while (variant != exitp);
}

void outGretting() {
    cout << "Добро пожаловать в програмную реализацию Контрольной работы №2" << endl;
    cout << "Лабораторную работу выполнил: Харисов Ильяс Ренатович, 424 группа, 21 вариант" << endl << endl;
    cout << "Что нужно было сделать ?" << endl;
    cout << "Контрольная работа № 2. Наследование" << endl
        << "В контрольной работе задается базовый и производный класс." << endl
        << "Необходимо разработать поля и методы, наследуемые из базового класса." << endl
        << "A также собственные компоненты производных классов.Базовый класс может быть абстрактным." << endl
        << "Реализовать возможность получения списка объектов в контейнере." << endl;
    cout << "Базовый класс – личность; поля – фамилия, адрес. Производный класс – студент." << endl;
}


int main() {
    system("chcp 1251");
    setlocale(LC_ALL, "Rus");
    outGretting();
    launchMenu();
    system("pause");
}
