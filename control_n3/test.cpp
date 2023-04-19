#include <iostream>
#include "test.h"
#include "ui.h"
#include <cassert>
#include <fstream>
#include <sstream>

using namespace std;
using namespace ui;


enum {
    sizeOfTest = 5
};

enum {
    withoutEnd = 1, countTest = 6
};

template<typename T, typename U>

void printInvalid(U expected, T received, string message) {
    cout << message << endl;
    cout << "Ожидалось: " << expected << endl << "Было получено: " << received << endl;
}


bool printCorrect(void (*function)(), int count) {
    stringstream buffer{};
    streambuf* old_cout_buf = cout.rdbuf(buffer.rdbuf());
    (*function)();
    cout.rdbuf(old_cout_buf);
    string output = buffer.str();
    if (output.empty()) {
        return true;
    }
    else {
        cout << "Не был пройден тест №" << count << endl;
        cout << "Подробности об ошибке: " << endl;
        cout << output;
        return false;
    }
}

void creatingTestFiled(unique_ptr<Matrix>& matrix) {
    fillingRandom synt;
    matrix = make_unique<Matrix>(sizeOfTest, sizeOfTest);
    synt.filling(matrix);
}

void generateSynth() {
    ofstream out("test1.txt");
    out << "5 5" << endl;
    out << "9\t3\t4\t5\t6" << endl;
    out << "1\t3\t7\t5\t9" << endl;
    out << "1\t8\t4\t3\t6" << endl;
    out << "8\t2\t2\t51\t9" << endl;
    out << "69\t63\t64\t65\t66" << endl;
    out.close();

    ofstream out2("test2.txt");
    out2 << "-8 5" << endl;
    out2 << "9   3   4   5   6" << endl;
    out2 << "1   3   7   5   9" << endl;
    out2 << "1   8   4   3   6" << endl;
    out2 << "8   2   2   51   69" << endl;
    out2 << "69   63   64   65   66" << endl;
    out2.close();

    ofstream out3("test3.txt");
    out3 << "5 5" << endl;
    out3 << "9   3   5   6" << endl;
    out3 << "1   3   5   9" << endl;
    out3 << "1   8   3   6" << endl;
    out3 << "8   2   51   69" << endl;
    out3 << "69   63    65   66" << endl;
    out3.close();

    ofstream out4("test4.txt");
    out4 << "5 5" << endl;
    out4 << "9   3   11   5   6" << endl;
    out4 << "" << endl;
    out4 << "1   8   78   3   6" << endl;
    out4 << "8   2   23   51   69" << endl;
    out4 << "" << endl;
    out4 << "69   63   7   65   66" << endl;
    out4.close();

    ofstream out5("test5.txt");
    out5 << "5 5" << endl;
    out5 << "9   3   11   5   6" << endl;
    out5 << "1  3   89   5   9" << endl;
    out5 << "1   8   78   3   6" << endl;
    out5 << "8   2   23   51   69" << endl;
    out5 << "69   63   7   65   66" << endl;
    out5.close();

}

bool testFillFromFile(){
	bool correct = true;

    string myOutput = {};
    string message = {};
    fileReader reader;
    unique_ptr<Matrix> matrix;
    string outputDataError = "Слишком много данных в одной строке! Данные будут проигнорированы\n";
    string outputNegative = "Некорректный средний балл студента!Исправьте данные в файле!В 2 строке\n";
    string outputInputError3 = "Ввод данных о студенте на 3 строке не был произведен! Исправьте файл и введите данные заново\n";
    string outputNullString = "Ввод данных о студенте на 1 строке не был произведен! Исправьте файл и введите данные заново\nВвод данных о студенте на 2 строке не был произведен! Исправьте файл и введите данные заново\n";

    generateSynth();

    // Тест с корректными данными
    stringstream buffer{};
    streambuf* old_cout_buf = cout.rdbuf(buffer.rdbuf());
    reader.implFile(matrix, "test1.txt");
    int rows = matrix->getRows();
    int column = matrix->getColumn();
    message = "Был не пройден тест на проверку коректных данных\n";
    if (rows != sizeOfTest) {
        printInvalid(rows, sizeOfTest, message);
        correct = false;
    }
    reader.implFile(matrix, "test2.txt");
	return correct;
}
bool testInsertionSort() {
	bool correct = true;
	return correct;
}
bool testBubbleSort() {
	bool correct = true;
	return correct;
}
bool testQuickSort() {
	bool correct = true;
	return correct;
}
bool testShellSort() {
	bool correct = true;
	return correct;
}

void test::startTest() {
	if (
		testFillFromFile() &&
		testInsertionSort() &&
		testBubbleSort() &&
		testQuickSort() &&
		testShellSort()
		) {
		cout << endl << "Все тесты были пройдены" << endl << endl;
	}
	else {
		cout << "К глубокому сожалению не все тесты были пройдены" << endl;
	}
}