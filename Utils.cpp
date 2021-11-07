#include "Utils.h"

#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>

namespace cmyui {
    std::vector<int> generateTable(int limit) {
        std::vector<int> vec{};
        for (auto i = 1; i <= limit; i++)
            vec.push_back(i);
        std::shuffle(vec.begin(), vec.end(), std::default_random_engine((unsigned int)(time(0) % rand())));
        return vec;
    }

    int getInt() {
        int val{};
        while (1) {
            std::cin >> val;
            if (!std::cin) {
                std::cout << "Invalid, try again: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            } else {
                break;
            }
        }
        return val;
    }

    int getIntInRange(const int min, const int max) {
        int val{};
        while (1) {
            val = getInt();
            if (val < min || val > max) {
                std::cout << "Please enter a number in range " << min << "-" << max << " (inclusive): ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            } else {
                break;
            }
        }
        return val;
    }

    void clearScreen() {
#ifdef __linux__
        system("clear");
#else
        system("cls");
#endif
    }
}
