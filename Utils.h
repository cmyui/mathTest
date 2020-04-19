#ifndef CMYUI_UTILS_H__
#define CMYUI_UTILS_H__

#include <vector>

namespace cmyui {
    ::std::vector<int> generateTable(int limit);
    int getInt();
    int getIntInRange(const int min, const int max);
    /*inline */void clearScreen();
}

#endif