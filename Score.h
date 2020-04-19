#ifndef CMYUI_SCORE_H__
#define CMYUI_SCORE_H__

#include <string>

namespace cmyui {
    struct Score {
        int correct;
        int incorrect;
        int maxNumber;
        int time;
        int date;

        Score() : correct(0), incorrect(0), maxNumber(0), time(0), date(0) {}
        Score(int _correct, int _incorrect, int _maxNumber, int _time, int _date)
            : correct(_correct), incorrect(_incorrect), maxNumber(_maxNumber), time(_time), date(_date) {
        }

        std::string getTimeFormatted(int input) const;
    };
}

#endif