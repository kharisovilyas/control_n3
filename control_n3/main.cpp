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
    cout << "��� ��������� ������ ?" << endl;
    cout << "������� :" << endl;
    cout << "[1] - ����� ����� ������ �� �����" << endl;
    cout << "[2] - ����� ������ ������ � �������" << endl;
    cout << "[3] - ����� ��������� ������� ���������� ����������" << endl;
    cout << "[0] - ����� ����� �� ���������" << endl << endl;
}

void printTestInfo() {
    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "������� :" << endl;
    cout << "[1] - ����� ��������� ��������� �����" << endl;
    cout << "[0] - ����� ���������� ��������" << endl;
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
        cout << "�� �����!" << endl;
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
            cout << "�� �����!" << endl;
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
