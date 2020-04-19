#include "Leaderboard.h"

namespace cmyui {
    void Leaderboard::_loadScores() { // omega unsafe
        std::ifstream ifs(_fileName, std::ifstream::in);
        if (ifs.fail()) { // file does not exist
            ifs.close();
            return;
        }

        ifs >> _noScores;
        if (_noScores > MAX_SCORES) {
            throw "Invalid db file! (size)";
            return exit(1);
        } 
        ifs.ignore();

        _scores = new Score[_noScores];

        for (int i = 0; !ifs.eof() && ifs.peek() != -1 && i < _noScores; i++) {
            ifs >> _scores[i].correct; // %2d
            ifs.ignore(); // ,
            ifs >> _scores[i].incorrect; // %2d
            ifs.ignore(); // ,
            _scores[i].maxNumber = _scores[i].correct + _scores[i].incorrect;
            ifs >> _scores[i].time; // %5d
            ifs.ignore(); // ,
            ifs >> _scores[i].date; // %10d
            ifs.ignore(); // \n
        }

        ifs.close();
	}

    void Leaderboard::_saveScores() {
        std::ofstream ofs(_fileName, std::ofstream::out | std::ios::trunc);
        if (!ofs.good()) {
            ofs.close();
            return;
        }

        ofs << _min(_noScores, MAX_SCORES) << '|';

        for (int i = 0; i < _min(_noScores, MAX_SCORES); i++)
            ofs << _scores[i].correct << ',' << _scores[i].incorrect << ',' << _scores[i].time << ',' << _scores[i].date << '|';

        ofs.close();
    }

    inline void Leaderboard::_sortScores() { cmyui::bubbleSort<Score>(_scores, _noScores); }

    Leaderboard::Leaderboard(const char* fileName) {
        if (!fileName || !*fileName)
            throw std::invalid_argument("Invalid filename!");
        else {
            strcpy(_fileName, fileName);
            _loadScores();
            _sortScores();
        }
    }

    void Leaderboard::addScore(Score& s) { // can go over MAX_SCORES, but won't save anything past it.
        if (s.correct || s.incorrect || s.maxNumber || s.date || s.time) {
            if (_noScores) {
                Score* tmp = new Score[_noScores];
                for (int i = 0; i < _noScores; tmp[i] = _scores[i], i++);// old->tmp
                deallocArray(_scores);// del old
                _scores = new Score[_noScores + 1];// new old
                for (int i = 0; i < _noScores; _scores[i] = tmp[i], i++);// tmp->old
            } else _scores = new Score[_noScores + 1];
            _scores[_noScores++] = s;
            _sortScores();
            _saveScores();
        }
    }

    void Leaderboard::display(const int maxNumber) const {
        std::cout << "Local leaderboards" << std::endl
                  << "=----------------=" << std::endl;

        for (int i = 0; i < _min(_noScores, 50); i++)
            if (_scores[i].maxNumber == maxNumber) // only display our current 'mode' board
                std::cout << "Date: " << std::setw(13) << std::right << _scores[i].getTimeFormatted(time(0) - _scores[i].date)
                          << " | Accuracy: " << KGRN << std::setw(2) << std::left << _scores[i].correct << KRESET << '/' << KRED << std::right << std::setw(2) << _scores[i].incorrect << KRESET
                          <<     " (" << std::setw(6) << (_scores[i].correct + _scores[i].incorrect ? ((float)_scores[i].correct / (_scores[i].correct + _scores[i].incorrect)) * 100 : 100.0f) << "%)"
                          << " | Speed: " << _scores[i].getTimeFormatted(_scores[i].time) << "." << std::endl;
    }
}
