#include <iostream>
#include "test.h"
#include "ui.h"
#include "sort.h"
#include <cassert>
#include <fstream>
#include <sstream>

using namespace std;
using namespace ui;
using namespace sort;


enum {
    sizeOfTest = 5
};

enum {
    withoutEnd = 1, countTest = 6
};

template<typename T, typename U>

void printInvalid(T received, U expected, string message) {
    cout << message << endl;
    cout << "Ожидалось: " << expected << endl << "Было получено: " << received << endl;
}

void printInvalidResults(StringEnumHelper _expected, StringEnumHelper _received, string message) {
    string received = static_cast<string> (_received);
    string expected = static_cast<string> (_expected);
    cout << message << endl;
    cout << "Ожидалось: " << expected << endl << "Было получено: " << received << endl;
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
    out2 << "9\t3\t4\t5\t6" << endl;
    out2 << "1\t3\t7\t5\t9" << endl;
    out2 << "1\t8\t4\t3\t6" << endl;
    out2 << "8\t2\t2\t51\t9" << endl;
    out2 << "69\t63\t64\t65\t66" << endl;
    out2.close();

    ofstream out3("test3.txt");
    out3 << "5 5" << endl;
    out3 << "9\t3\t4\t5\t6" << endl;
    out3 << "1\t3\t7\t5\t9" << endl;
    out3 << "1\t8\t4\t3 6" << endl;
    out3 << "8\t2\t2\t51\t9" << endl;
    out3 << "69\t63\t64\t65\t66" << endl;
    out3.close();

    ofstream out4("test4.txt");
    out4 << "5 5" << endl;
    out4 << "9\t3\t4\t5\t6" << endl;
    out4 << "" << endl;
    out4 << "1\t8\t4\t3\t6" << endl;
    out4 << "" << endl;
    out4 << "8\t2\t2\t51\t9" << endl;
    out4.close();

    ofstream out5("test5.txt");
    out5 << "5 5" << endl;
    out5 << "9\t3\t5\t6\t10\t5" << endl;
    out5 << "1\t7\t5\t9\t10\t6" << endl;
    out5 << "1\t4\t3\t6\t67\t7" << endl;
    out5 << "8\t2\t51\t9\t66\t67" << endl;
    out5 << "8\t2\t51\t9\t66\t67" << endl;
    out5 << "8\t2\t51\t9\t66\t67" << endl;
    out5 << "8\t2\t51\t9\t66\t67" << endl;
    out5.close();

}

bool testFillFromFile(){
	bool correct = true;
    int rows{};
    int column{};
    string myOutput = {};
    string message = {};
    fileReader reader;
    unique_ptr<Matrix> matrix{};
    StringEnumHelper null_column = StringEnumHelper(StringEnum::null_column);
    StringEnumHelper null_row = StringEnumHelper(StringEnum::null_row);
    StringEnumHelper invalid_rows = StringEnumHelper(StringEnum::invalid_rows);
    StringEnumHelper invalid_columns = StringEnumHelper(StringEnum::invalid_columns);
    StringEnumHelper nonexist = StringEnumHelper(StringEnum::nonexist);
    StringEnumHelper negative_size = StringEnumHelper(StringEnum::negative_size);
    StringEnumHelper correctInput = StringEnumHelper(StringEnum::correct);
    

    generateSynth();

    message = "\nБыл не пройден тест с корректными данными\n";
    // Тест с корректными данными
    StringEnumHelper errorType = reader.implFile(matrix, "test1.txt");

    rows = matrix->getRows();
    column = matrix->getColumn();
    message = "Был не пройден тест на проверку коректных данных\n";

    if (errorType != correctInput) {
        printInvalidResults(errorType, correctInput, message);
        correct = false;
    }

    if (rows != sizeOfTest) {
        printInvalid(rows, sizeOfTest, message);
        correct = false;
    }

    message = "\nБыл не пройден тест на отрицательные размеры матрицы\n";
    //Тест на отрицательные размеры матрицы
    errorType = reader.implFile(matrix, "test2.txt");

    if (errorType != negative_size) {
        printInvalidResults(errorType, negative_size, message);
        correct = false;
    }

    message = "\nБыл не пройден тест на некорректные данные в столбце\n";
    //Тест на некорректные данные в столбце
    errorType = reader.implFile(matrix, "test3.txt");

    if (errorType != null_column) {
        printInvalidResults(errorType, null_column, message);
        correct = false;
    }

    message = "\nБыл не пройден тест на некорректные данные в строке\n";
    //Тест на некорректные данные в строке
    errorType = reader.implFile(matrix, "test4.txt");

    if (errorType != null_row) {
        printInvalidResults(errorType, null_row, message);
        correct = false;
    }

    message = "\nБыл не пройден тест на несоотвествие указанных и фактических размеров\n";
    //Тест на несоотвествие указанных и фактических размеров
    errorType = reader.implFile(matrix, "test5.txt");

    if (errorType != invalid_rows) {
        printInvalidResults(errorType, invalid_rows, message);
        correct = false;
    }

	return correct;
}

void generateSynthMatrix(unique_ptr<Matrix>& matrix) {
    int element_1 = 1, element_2 = 18;
    int step = 1;
    for (int i = 0; i < sizeOfTest; i++) {
        for (int j = 1; j <= sizeOfTest; j++) {
            if (i % 2 == 0 && j % 2 == 0) {
                matrix->setElement(i, j - 1, element_2);
                element_2 -= 2;
            }
            else if (i % 2 != 0 && j % 2 != 0) {
                matrix->setElement(i, j - 1, element_2);
                element_2 -= 2;
            }
            else {
                matrix->setElement(i, j - 1, element_1);
                element_1 += step;
                step = (step > 0) ? -1 : 2;
            }
        }
        element_1 = 1;
        element_2 = 18;
        step = 1;

    }
}

bool checkValidDataSort(unique_ptr<Matrix>& matrix) {
    bool correct = true;
    int correctData_1[sizeOfTest] = {
        1, 18, 2, 16, 1
    };
    int correctData_2[sizeOfTest] = {
        18, 1, 16, 2, 14
    };
    if (matrix->getElement(0, 0) != correctData_1[0]) {
        correct = false;
        printInvalid(matrix->getElement(0, 0), correctData_1[0], {});
    }

    if (matrix->getElement(0, 1) != correctData_1[2]) {
        correct = false;
        printInvalid(matrix->getElement(0, 1), correctData_1[2], {});
    }

    if (matrix->getElement(0, 2) != correctData_1[3]) {
        correct = false;
        printInvalid(matrix->getElement(0, 2), correctData_1[3], {});
    }

    if (matrix->getElement(0, 3) != correctData_1[1]) {
        correct = false;
        printInvalid(matrix->getElement(0, 3), correctData_1[1], {});

    }

    if (matrix->getElement(0, 4) != correctData_1[4]) {
        correct = false;
        printInvalid(matrix->getElement(0, 4), correctData_1[4], {});
    }

    if (matrix->getElement(1, 0) != correctData_2[3]) {
        correct = false;
        printInvalid(matrix->getElement(1, 0), correctData_2[3], {});
    }

    if (matrix->getElement(1, 1) != correctData_2[1]) {
        correct = false;
        printInvalid(matrix->getElement(1, 1), correctData_2[1], {});
    }

    if (matrix->getElement(1, 2) != correctData_2[4]) {
        correct = false;
        printInvalid(matrix->getElement(1, 2), correctData_2[4], {});
    }
    if (matrix->getElement(1, 3) != correctData_2[2]) {
        correct = false;
        printInvalid(matrix->getElement(1, 3), correctData_2[2], {});
    }
    if (matrix->getElement(1, 4) != correctData_2[0]) {
        correct = false;
        printInvalid(matrix->getElement(1, 4), correctData_2[0], {});
    }

    return correct;
}

bool testInsertionSort() {
	bool correct = true;
    insertion insert{};
    unique_ptr<Matrix> matrix = make_unique<Matrix>(sizeOfTest, sizeOfTest);
    generateSynthMatrix(matrix);
    insert.Sort(matrix);

	return checkValidDataSort(matrix);
}
bool testBubbleSort() {
	bool correct = true;    
    bubbleSelection bubble{};
    unique_ptr<Matrix> matrix = make_unique<Matrix>(sizeOfTest, sizeOfTest);
    generateSynthMatrix(matrix);
    bubble.Sort(matrix);
    
    return checkValidDataSort(matrix);
}
bool testQuickSort() {
	bool correct = true;    
    quickSort qs{};
    unique_ptr<Matrix> matrix = make_unique<Matrix>(sizeOfTest, sizeOfTest);
    generateSynthMatrix(matrix);
    qs.Sort(matrix);

    return checkValidDataSort(matrix);
}
bool testShellSort() {
	bool correct = true;    
    shell shellSort{};
    unique_ptr<Matrix> matrix = make_unique<Matrix>(sizeOfTest, sizeOfTest);
    generateSynthMatrix(matrix);
    shellSort.Sort(matrix);
    return checkValidDataSort(matrix);
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