#include <iostream>
#include <vector>
#include "Matrix.h"

Matrix::Matrix(int newN, int newM) {
    n = newN;
    m = newM;
    elements = vector<vector<int>>(n, vector<int>(m, 0));
}

int Matrix::getElement(int i, int j) const {
    return elements[i][j];
}

void Matrix::swapElements(int row1, int col1, int row2, int col2){
    int temp = elements[row1][col1];
    elements[row1][col1] = elements[row2][col2];
    elements[row2][col2] = temp;
}

int Matrix::getRows() const {
    return n;
}

int Matrix::getColumn() const {
    return m;
}

void Matrix::setElement(int i, int j, int value) {
    elements[i][j] = value;
}

Matrix& Matrix::operator = (const Matrix& other) {
    if (this != &other) {
        n = other.n;
        m = other.m;
        elements = other.elements;
    }
    return *this;
}