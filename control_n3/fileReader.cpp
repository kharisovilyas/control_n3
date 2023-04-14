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
		cout << "Обратите внимание! Что данные об одном студенте должны быть записаны на одной строке через ; и без пробелов !" << endl;
		cout << "Если данные записаны иначе, программа укажет на ошибку, прекратит выполнение и попросит исправить исходный файл" << endl;
		cout << "-----..........-----..........-----..........-----" << endl;
		cout << "Загрузить из: ";
	}
	if (way == mOutput) {
		cout << "Введите название файла в который вы хотите сохранить результат" << endl;
	}
}

// Разбиваем строку на подстроки, используя символ ';' в качестве разделителя
void filling(unique_ptr<Matrix>& matrix, const char* str_ptr, int i) {
	int j = 0;
	char* str_copy = new char[strlen(str_ptr) + 1];
	strcpy_s(str_copy, strlen(str_ptr) + 1, str_ptr);
	char* context = nullptr;
	char* token = strtok_s(str_copy, "\t", &context);
	while (token != nullptr) {
		matrix->setElement(i, j, stoi(token));
		token = strtok_s(nullptr, "\t", &context);
		j++;
	}
	delete[] str_copy;
}


void fileReader::implFile(unique_ptr<Matrix>& matrix, string name) {
	int i = 0;
	string data{};
	ifstream input;
	input.open(name);

	if (input.is_open()) {
		getline(input, data);
		istringstream iss(data);
		int a, b;
		iss >> a >> b;
		if (a <= 0 || b <= 0) {
			cout << "Файл содержит неположительные количество строк или столбцов" << endl;
			throw runtime_error("error");
		}
		while (getline(input, data)) {
			//продумать сообщение об ошибке при вводе не int 
			if (data.empty()) {
				cout << "Ввод данных на " << i + 1 << " строке не был произведен! Исправьте файл и введите данные заново" << endl;
				i++;
				continue;
			}
			else {
				filling(matrix, data.c_str(), i);
			}
			i++;
		}
		input.close();
	}
	else {
		cout << endl << "Файла с таким именем не существует!" << endl << endl;
		throw runtime_error("error");
	}
}

void fileReader::readFile(unique_ptr<Matrix>& matrix, string name) {
	printInform(mInput);
	cin >> name;
	implFile(matrix, name);
}


void fileReader::fillFile(unique_ptr<Matrix>& matrix, map<string, pair<int, int>>& results) const {
	printInform(mOutput);
	string filePath = "";
	bool isDataSaved = false;
	correctness check;
	do {
		cout << "Сохранить в: ";
		getline(cin, filePath);

		if (ifstream(filePath)) {
			cout << "Файл уже существует." << endl;
			cout << "[0] - Перезаписать существующий файл." << endl;
			cout << "[1] - Повторить ввод." << endl;
			int tryAnotherFile = check.getBool();
			if (tryAnotherFile) {
				continue;
			}
		}

		ofstream myFile(filePath, ofstream::app);

		error_code ec{};

		if (!myFile) {
			cout << "Запись запрещена. Повторите ввод." << endl;
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
		myFile << endl;
		myFile << "Сравнительная таблица сортировок:" << endl;
		myFile << "Сортировка\tКоличество перестановок\tКоличество сравнений" << endl;
		for (auto& pair : results) {
			myFile << pair.first << "\t" << pair.second.first << "\t" << pair.second.second << endl;
		}

		myFile.close();
		cout << "Запись завершена." << endl;
		isDataSaved = true;
	} while (!isDataSaved);
}



void fileReader::fillFile(unique_ptr<Matrix>& matrix) const {
	printInform(mOutput);
	string filePath = "";
	bool isDataSaved = false;
	correctness check;
	do {
		cout << "Сохранить в: ";
		getline(cin, filePath);

		if (ifstream(filePath)) {
			cout << "Файл уже существует." << endl;
			cout << "[0] - Перезаписать существующий файл." << endl;
			cout << "[1] - Повторить ввод." << endl;
			int tryAnotherFile = check.getBool();
			if (tryAnotherFile) {
				continue;
			}
		}

		ofstream myFile(filePath, ofstream::app);

		error_code ec{};

		if (!myFile) {
			cout << "Запись запрещена. Повторите ввод." << endl;
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
		cout << "Запись завершена." << endl;
		isDataSaved = true;
	} while (!isDataSaved);
}
