#include "Utils.h"

#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>

typedef unsigned char byte;

namespace cmyui {
    auto generateTable(int limit) -> std::vector<int> {
        std::vector<int> vec;
        for (byte i = 1; i <= limit; vec.push_back(i), i++);
        std::shuffle(vec.begin(), vec.end(), std::default_random_engine((unsigned int)(time(0) % rand())));
        return vec;
    }

    int getInt() {
        int val = 0;
        while (1)
            if (std::cin >> val; !std::cin) {
                std::cout << "Invalid, try again: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            } else break;
        return val;
    }

    int getIntInRange(const int min, const int max) {
        int val = 0;
        while (1)
            if (val = getInt(); val < min || val > max) {
                std::cout << "Please enter a number in range " << min << "-" << max << " (inclusive): ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            } else break;
        return val;
    }

    /*inline */void clearScreen() {
#ifdef __linux__
        system("clear");
#else
        system("cls");
#endif
    }
}