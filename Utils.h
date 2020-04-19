#ifndef CMYUI_UTILS_H__
#define CMYUI_UTILS_H__

#include <vector>

namespace cmyui {
    ::std::vector<int> generateTable(int limit);
    int getInt();
    int getIntInRange(const int min, const int max);
    /*inline */void clearScreen();

#define dealloc(x) if (x) x = (delete x, nullptr);
#define deallocArray(x) if (x) x = (delete[] x, nullptr);
}

#endif
