#include <iostream>
#include "ui.h"
#include "Matrix.h"
#include "time.h"

using namespace ui;

StringEnumHelper fillingRandom::filling(unique_ptr<Matrix>& matrix) {
	correctness check{};
	fileReader toFile{};
	cout << "Введите количество строк" << endl;
	int n = 0, m = 0;
	n = check.getIntField();
	cout << "Введите количество столбцов" << endl;
	m = check.getIntField();
	int element{};
	srand(static_cast<unsigned int>(time(NULL)));
	matrix = make_unique<Matrix>(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			element = rand() / 100;
			matrix->setElement(i, j, element);
		}
	}
	toFile.outInitialDataInFile(matrix);
	return StringEnumHelper(StringEnum::correct);
}