#include "ui.h"
#include <iostream>
#include <map>

using namespace ui;
using namespace std;



StringEnumHelper inOutConsole::readConsole(unique_ptr<Matrix>& matrix) {
	correctness check{};
	fileReader toFile{};
	int n = 0, m = 0;
	int element;
	cout << "������� ���������� �����" << endl;
	n = check.getIntField();
	cout << "������� ���������� ��������" << endl;
	m = check.getIntField();
	matrix = make_unique<Matrix>(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << "������� [ " << i + 1 << " ][ " << j + 1 << " ] �������" << endl;
			element = check.getInt();
			matrix->setElement(i, j, element);
		}
	}
	toFile.outInitialDataInFile(matrix);
	return StringEnumHelper(StringEnum::correct);
}

void inOutConsole::outConsole(unique_ptr<Matrix>& matrix) const {
	cout << "���� ������� [" << matrix->getRows() << "]x[" << matrix->getColumn() << "] ���������: " << endl;
	for (int i = 0; i < matrix->getRows(); i++) {
		for (int j = 0; j < matrix->getColumn(); j++) {
			cout << matrix->getElement(i, j) << "\t";
		}
		cout << endl;
	}
}


void inOutConsole::outConsole(unique_ptr<Matrix>& matrix, map<string, pair<int, int>>& results) const{
	cout << "���� ��������������� ������� [" << matrix->getRows() << "]x[" << matrix->getColumn() << "] ���������: " << endl;
	for (int i = 0; i < matrix->getRows(); i++) {
		for (int j = 0; j < matrix->getColumn(); j++) {
			cout << matrix->getElement(i, j) << "\t";
		}
		cout << endl;
	}

	cout << endl << "������������� ������� ����������:" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "|\t����������\t|\t���������� ������������\t\t|\t���������� ���������\t|" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	for (auto& pair : results) {
		cout << "|" << pair.first << "\t|\t\t" << pair.second.first << "\t\t\t|\t\t" << pair.second.second << "\t\t|" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;

	}
}