#include "Leaderboard.h"

namespace cmyui {
	void Leaderboard::_loadScores() {
        std::ifstream ifs(_fileName, std::ifstream::in);
        if (ifs.fail()) { // file does not exist
            ifs.close();
            return;
        }

        while (!ifs.eof() && ifs.peek() != -1) {
            Score tmp;

            ifs >> tmp.correct; // %2d
            ifs.ignore(1); // ,
            ifs >> tmp.incorrect; // %2d
            ifs.ignore(1); // ,
            tmp.maxNumber = tmp.correct + tmp.incorrect;
            ifs >> tmp.time; // %5d
            ifs.ignore(1); // ,
            ifs >> tmp.date; // %10d
            ifs.ignore(1); // \n

            _scores.push_back(tmp);
        }

        ifs.close();
	}

    void Leaderboard::_saveScores() {
        std::ofstream ofs(_fileName, std::ofstream::out | std::ios::trunc);
        if (!ofs.good()) {
            ofs.close();
            return;
        }

        for (Score& s : _scores)
            ofs << s.correct << ',' << s.incorrect << ',' << s.time << ',' << s.date << '\n';

        ofs.close();
    }

    inline void Leaderboard::_sortScores() {
        std::sort(_scores.begin(), _scores.end(), [&](const Score& x, const Score& y) { return x.time < y.time; });
    }

    Leaderboard::Leaderboard(const char* fileName) {
        if (!fileName || !*fileName) {
            throw std::invalid_argument("Invalid filename!");
        } else {
            strcpy(_fileName, fileName);
            _loadScores();
            _sortScores();
        }
    }

    void Leaderboard::addScore(Score s) {
        if (s.correct || s.incorrect || s.maxNumber || s.date || s.time) {
            _scores.push_back(s);
            _sortScores();
            _saveScores();
        }
    }

    void Leaderboard::display(const int maxNumber) const {
        std::cout << "Local leaderboards" << std::endl
            << "=----------------=" << std::endl;
        for (const Score& s : _scores)
            if (maxNumber == s.maxNumber) // only display our current 'mode' board
                std::cout << "Date: " << std::setw(13) << std::right << s.getTimeFormatted(time(0) - s.date) << " | Accuracy: " << KGRN << std::setw(2) << std::left << s.correct << KRESET << '/' << KRED << std::right << std::setw(2) << s.incorrect << KRESET << " (" << std::setw(6) << (s.correct + s.incorrect ? ((float)s.correct / (s.correct + s.incorrect)) * 100 : 100.0f) << "%)" << " | Speed: " << s.getTimeFormatted(s.time) << "." << std::endl;
    }
}
