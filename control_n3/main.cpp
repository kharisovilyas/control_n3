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
    cout << "��� ��������� ������ ��� ����� ��������� ��������� ����� ?" << endl;
    cout << "������� :" << endl;
    cout << "[1] - ����� ����� ������ �� �����" << endl;
    cout << "[2] - ����� ������ ������ � �������" << endl;
    cout << "[3] - ����� ��������� ������� ���������� ����������" << endl;
    cout << "[4] - ����� ��������� ��������� �����" << endl;
    cout << "[0] - ����� ����� �� ���������" << endl << endl;
}

void printAction() {
    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "������� :" << endl;
    cout << "[1] - ����� ������ ����������" << endl;
    cout << "[0] - ����� ����� � �������� ������" << endl;
}

void printOutputWays() {
    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "���������� ��������, ��� �� ������ �������� ���������� ?" << endl;
    cout << "����������: �������� � �������������� ������� � ������������� ������� ����������" << endl;
    cout << "������ ���� :" << endl;
    cout << "[1] - � ����" << endl;
    cout << "[0] - � �������" << endl;
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
        cout << "�� �����!" << endl;
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

        //����� �������� �������
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
    cout << "����� ���������� � ���������� ���������� ����������� ������ �2" << endl;
    cout << "������������ ������ ��������: ������� ����� ���������, 424 ������, 21 �������" << endl << endl;
    cout << "��� ����� ���� ������� ?" << endl;
    cout << "����������� ������ � 2. ������������" << endl
        << "� ����������� ������ �������� ������� � ����������� �����." << endl
        << "���������� ����������� ���� � ������, ����������� �� �������� ������." << endl
        << "A ����� ����������� ���������� ����������� �������.������� ����� ����� ���� �����������." << endl
        << "����������� ����������� ��������� ������ �������� � ����������." << endl;
    cout << "������� ����� � ��������; ���� � �������, �����. ����������� ����� � �������." << endl;
}


int main() {
    system("chcp 1251");
    setlocale(LC_ALL, "Rus");
    outGretting();
    launchMenu();
    system("pause");
}
