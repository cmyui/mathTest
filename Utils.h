#ifndef CMYUI_UTILS_H__
#define CMYUI_UTILS_H__

#include <vector>
#include <utility>

namespace cmyui {
    ::std::vector<int> generateTable(int limit);
    int getInt();
    int getIntInRange(const int min, const int max);
    void clearScreen();

    template<typename T>
    void bubbleSort(T arr[], int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++)
                if (arr[j] > arr[j + 1])
                    std::swap(arr[j], arr[j + 1]);
        }
    }

#define dealloc(x) if (x) x = (delete x, nullptr);
#define deallocArray(x) if (x) x = (delete[] x, nullptr);

#define _min(a, b) ((a) < (b) ? (a) : (b))
#define _max(a, b) ((a) > (b) ? (a) : (b))

}

#endif
