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
    void IncrementComparisonCount() {
        comparisonCount++;
    }

    void IncrementSwapCount() {
        swapCount++;
    }

    void IncrementComparisonCountInThread() {
        lock_guard<mutex> lock(mutex_);
        comparisonCountInThread++;
    }

    void IncrementSwapCountInThread() {
        lock_guard<mutex> lock(mutex_);
        swapCountInThread++;
    }

    int GetComparisonCount() const {
        return comparisonCount.load() + comparisonCountInThread.load();
    }

    int GetSwapCount() const {
        return swapCount.load() + swapCountInThread.load();
    }

    bool possibleSort(int num) {
        return num % 2 == 0;
    }

    virtual ~ISort() {} 

private:
    atomic<int> comparisonCount = 0;
    atomic<int> swapCount = 0;
    atomic<int> comparisonCountInThread = 0;
    atomic<int> swapCountInThread = 0;
    mutex mutex_{};
};
