#ifndef CMYUI_LEADERBOARD_H__
#define CMYUI_LEADERBOARD_H__

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

#include "Score.h"

#define KGRN "\x1B[1;32m"
#define KRED "\x1B[1;31m"
#define KYEL "\x1B[1;33m"
#define KRESET "\033[0m"

namespace cmyui {
    const int MAX_FILENAME = 20;
    class Leaderboard {
        char _fileName[MAX_FILENAME + 1];
        std::vector<Score> _scores;

        // for internal use
        void _loadScores();
        void _saveScores();
        inline void _sortScores();

    public:
        Leaderboard(const char* fileName = "scores.db");
        ~Leaderboard() { _saveScores(); }

        void addScore(Score& s);
        void display(const int maxNumber) const;

        void operator+=(Score& s) { addScore(s); }
        Score& operator[](int i) { return _scores[i]; }
    };
}

#endif