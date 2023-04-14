#pragma once
#include <vector>
using namespace std;

class Matrix {
private:
    int n{};
    int m{};
    vector<vector<int>> elements{};
public:
    Matrix() = default;
    Matrix(int, int);
    int getElement(int, int) const;
    void swapElements(int, int, int, int);
    int getRows() const;
    int getColumn() const; // סעמכבצû
    void setElement(int, int, int);
    Matrix& operator=(const Matrix& other);
    ~Matrix() = default;
};