#include <iostream>
#include <filesystem>
#include "ui.h"
#include <string>
#include <fstream>
#include <map>
#include <cstring>
#include <iomanip>
#include <sstream>


using namespace std;
using namespace ui;

static const string mInput = "input";
static const string mOutput = "output";



enum { ch_surname = 0, ch_adress = 1, ch_group = 2, ch_gpa = 3 };

void printInform(string way) {
	if (way == mInput) {
		cout << "-----..........-----..........-----..........-----" << endl;
		cout << "�������� ��������! ��� � ������ ������ ����������: ����� ����� � ����� �������� ����� ������" << endl;
		cout << "�������� ��������! ��� � ������ ������ ������� ����� ������ ���� �������� ����� Tab" << endl;
		cout << "�������� ��������! ��� ���� �� ������� ���������� ����� ������ ��� �����������, �� ������ ������ ����� ������������� ��������� 0" << endl;
		cout << "���� ������ �������� �����, ��������� ������ �� ������, ��������� ���������� � �������� ��������� �������� ����" << endl;
		cout << "-----..........-----..........-----..........-----" << endl;
		cout << "��������� ��: ";
	}
	if (way == mOutput) {
		cout << "������� �������� ����� � ������� �� ������ ��������� ���������" << endl;
	}
}

void printInformOut() {
	cout << "-----..........-----..........-----..........-----" << endl;
	cout << "��� ������������ ������ �������� ������ � ����" << endl;
	cout << "����������� ������ ���� ��� ��������� � ���������, ������� :" << endl;
	cout << "[1] - ��������" << endl;
	cout << "[0] - �� ���������� � ���������� ���������� ���������" << endl;
	cout << "-----..........-----..........-----..........-----" << endl;
}

void fileReader::outInitialDataInFile(unique_ptr<Matrix>& matrix) const {
	correctness check{};
	printInformOut();
	bool variant = check.getBool();
	if (variant == 0) return;
	implFillFile(matrix);
}

// ��������� ������ �� ���������, ��������� ������ '\t' � �������� �����������
StringEnumHelper fillingColumns(unique_ptr<Matrix>& matrix, const char* str_ptr, int i, int m) {
	int j = 0;
	char* str_copy = new char[strlen(str_ptr) + 1];
	strcpy_s(str_copy, strlen(str_ptr) + 1, str_ptr);
	char* context = nullptr;
	char* token = strtok_s(str_copy, "\t", &context);
	for (int j = 0; j < m; j++) {
		if (token == nullptr) {
			return StringEnumHelper(StringEnum::null_column);
		}
		matrix->setElement(i, j, stoi(token));
		token = strtok_s(nullptr, "\t", &context);
		if (j + 1 > m) {
			return StringEnumHelper(StringEnum::invalid_columns);
		}
	}
	return StringEnumHelper(StringEnum::correct);
	delete[] str_copy;
}


StringEnumHelper fileReader::implFile(unique_ptr<Matrix>& matrix, string name) {
	int i = 0;
	string data{};
	ifstream input;
	input.open(name);

	if (input.is_open()) {
		getline(input, data);
		istringstream iss(data);
		int n = 0, m = 0;
		iss >> n >> m;
		if (n <= 0 || m <= 0) {
			return StringEnumHelper(StringEnum::negative_size);
		}
		matrix = make_unique<Matrix>(n, m);
		while (getline(input, data)) {
			//��������� ��������� �� ������ ��� ����� �� int 
			if (data.empty()) {
				return StringEnumHelper(StringEnum::null_row);
			}
			else if (i + 1 > n) {
				return StringEnumHelper(StringEnum::invalid_rows);
			}
			else {
				StringEnumHelper erorrType = fillingColumns(matrix, data.c_str(), i, m);
				StringEnumHelper correctType = StringEnumHelper(StringEnum::correct);
				if (!(erorrType == correctType)) {
					return erorrType;
				}
			}
			i++;
		}
		input.close();
	}
	else {
		return StringEnumHelper(StringEnum::nonexist);
	}
	return StringEnumHelper(StringEnum::correct);
}

StringEnumHelper fileReader::readFile(unique_ptr<Matrix>& matrix, string name) {
	printInform(mInput);
	cin >> name;
	cout << "-----..........-----..........-----..........-----" << endl;
	StringEnumHelper errorType = implFile(matrix, name);
	if (errorType == StringEnumHelper(StringEnum::correct)) {
		return StringEnumHelper(StringEnum::correct);
	}
	else {
		return errorType;
	}
}


void fileReader::implFillFile(
	unique_ptr<Matrix>& oldMatrix,
	unique_ptr<Matrix>& sortMatrix,
	map<string, pair<int, int>>& results
) const {
	printInform(mOutput);
	string filePath = "";
	bool isDataSaved = false;
	correctness check;
	do {
		cout << "��������� �: ";
		getline(cin, filePath);

		if (ifstream(filePath)) {
			cout << "-----..........-----..........-----..........-----" << endl;
			cout << "���� ��� ����������." << endl;
			cout << "[0] - ������������ ������������ ����." << endl;
			cout << "[1] - ��������� ����." << endl;
			cout << "-----..........-----..........-----..........-----" << endl;
			int tryAnotherFile = check.getBool();
			if (tryAnotherFile) {
				continue;
			}
		}

		ofstream myFile(filePath, ofstream::app);

		error_code ec{};

		if (!myFile) {
			cout << "������ ���������. ��������� ����." << endl;
			myFile.close();
			continue;
		}

		myFile.close();
		myFile.open(filePath, ofstream::trunc);
		
		myFile << "���� �������� ������� [" << oldMatrix->getRows() 
			<< "]x[" << oldMatrix->getColumn() << "] ���������: " << endl;
		for (int i = 0; i < oldMatrix->getRows(); i++) {
			for (int j = 0; j < oldMatrix->getColumn(); j++) {
				myFile << oldMatrix->getElement(i, j) << '\t';
			}
			myFile << endl;
		}
		myFile << "-------------------------------------------------------------------------------------------------" << endl;
		

		myFile << "���� ��������������� ������� [" << sortMatrix->getRows()
			<< "]x[" << sortMatrix->getColumn() << "] ���������: " << endl;
		for (int i = 0; i < sortMatrix->getRows(); i++) {
			for (int j = 0; j < sortMatrix->getColumn(); j++) {
				myFile << sortMatrix->getElement(i, j) << '\t';
			}
			myFile << endl;
		}
		myFile << "-------------------------------------------------------------------------------------------------" << endl;


		myFile << endl << "������������� ������� ����������:" << endl;
		myFile << "-------------------------------------------------------------------------------------------------" << endl;
		myFile << "|\t����������\t|\t���������� ������������\t\t|\t���������� ���������\t|" << endl;
		myFile << "-------------------------------------------------------------------------------------------------" << endl;
		for (auto& pair : results) {
			myFile << "|" << pair.first << "\t|\t\t" << pair.second.first << "\t\t\t|\t\t" << pair.second.second << "\t\t|" << endl;
			myFile << "-------------------------------------------------------------------------------------------------" << endl;

		}

		myFile.close();
		cout << "-----..........-----..........-----..........-----" << endl;
		cout << "������ ���������." << endl;

		isDataSaved = true;
	} while (!isDataSaved);
}


void fileReader::implFillFile(unique_ptr<Matrix>& matrix) const {
	printInform(mOutput);
	string filePath = "";
	bool isDataSaved = false;
	correctness check;
	do {
		cout << "��������� �: ";
		getline(cin, filePath);

		if (ifstream(filePath)) {
			cout << "���� ��� ����������." << endl;
			cout << "[0] - ������������ ������������ ����." << endl;
			cout << "[1] - ��������� ����." << endl;
			int tryAnotherFile = check.getBool();
			if (tryAnotherFile) {
				continue;
			}
		}

		ofstream myFile(filePath, ofstream::app);

		error_code ec{};

		if (!myFile) {
			cout << "������ ���������. ��������� ����." << endl;
			myFile.close();
			continue;
		}

		myFile.close();
		myFile.open(filePath, ofstream::trunc);
		for (int i = 0; i < matrix->getRows(); i++) {
			for (int j = 0; j < matrix->getColumn(); j++) {
				myFile << matrix->getElement(i, j) << '\t';
			}
			myFile << endl;
		}

		myFile.close();
		cout << "������ ���������." << endl;
		isDataSaved = true;
	} while (!isDataSaved);
}
