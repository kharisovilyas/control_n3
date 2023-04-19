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
enum { exitp = 0, rfile = 1, rconsole = 2, random = 3, unitTest = 4 };
enum { fileOutput = 1, coutput = 2, outreturn = 3 };


void printInputWays() {
    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "Как заполнить данные или может запустить модульные тесты ?" << endl;
    cout << "Нажмите :" << endl;
    cout << "[1] - чтобы взять данные из файла" << endl;
    cout << "[2] - чтобы ввести данные в консоли" << endl;
    cout << "[3] - чтобы заполнить матрицу случайными значениями" << endl;
    cout << "[4] - чтобы запустить модульные тесты" << endl;
    cout << "[0] - чтобы выйти из программы" << endl << endl;
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


void selectInput(int variant, unique_ptr<Matrix>& matrix) {
    fileReader mReader{};
    correctness check{};
    inOutConsole inOut{};
    fillingRandom fill{};
    test testing{};
    auto cinBuf = cin.rdbuf();
    switch (variant)
    {
    case rfile:
        mReader.readFile(matrix, {});
        break;
    case rconsole:
        inOut.readConsole(matrix);
        break;
    case random:
        fill.filling(matrix);
        break;
    case unitTest:
        testing.startTest();
        cin.rdbuf(cinBuf);
        break;
    case exitp:
        cout << "Вы вышли!" << endl;
        break;
    }
}

void selectOutput(bool needOutconsole, unique_ptr<Matrix>& sortMatrix, map<string, pair<int, int>>& results) {
    correctness check{};
    inOutConsole cInOut{};
    fileReader mReader{};
    if (!needOutconsole) {
        cInOut.outConsole(sortMatrix, results);
    }
    else {
        mReader.fillFile(sortMatrix, results);
    }
}

void launchMenu() {
    correctness check{};
    controlSort control{};
    int variant = 0;
    bool isStart{};
    bool outConsole{};
    int boardMenu = unitTest;
    unique_ptr<Matrix> matrix;
    unique_ptr<Matrix> sortMatrix;
    map<string, pair<int,int>> results;
    do
    {
        printInputWays();
        variant = check.getMenuVar(exitp, unitTest);
        try {
            selectInput(variant, matrix);
        }
        catch (const exception& e) {
            cout << e.what() << endl;
            continue;
        }
        if (variant == exitp) break;
        if (variant == unitTest) continue;

        //вывод исходной матрицы
        inOutConsole out{};
        out.outConsole(matrix);

        printAction();
        isStart = check.getBool();
        if (!isStart) continue;
        try {
            control.startSort(matrix, sortMatrix, results);
        }
        catch (const exception& e) {
            cout << e.what() << endl;
            continue;
        }

        printOutputWays();
        outConsole = check.getBool();
        try {
            selectOutput(outConsole, sortMatrix, results);
        }
        catch (const exception& e) {
            cout << e.what() << endl;
            continue;
        }
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
