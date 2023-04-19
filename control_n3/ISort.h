#pragma once
#include <atomic>
#include <mutex>
#include <vector>
#include "Matrix.h"

using namespace std;

class ISort {
protected:
    virtual void Sort(unique_ptr<Matrix>&) = 0;
public:
    void SetIncrementComparisonCount(int comprasions) {
        comparisonCount = comprasions;
    }

    void SetIncrementSwapCount(int swaps) {
        swapCount = swaps;
    }

    int GetComparisonCount() const {
        return comparisonCount;
    }

    int GetSwapCount() const {
        return swapCount;
    }

    bool possibleSort(int num) {
        return num % 2 == 0;
    }

    void sortPossible(unique_ptr<Matrix>&, void (*function)(vector<int>&, pair<int, int>&));

    virtual ~ISort() {} 

private:
    int comparisonCount = 0;
    int swapCount = 0;
};
