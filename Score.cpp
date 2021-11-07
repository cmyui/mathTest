#include <iostream>

#include "Score.h"

namespace cmyui {
    std::string Score::getTimeFormatted(int seconds) const {
        if (!seconds) return "now";
        int days = int(seconds / 60 / 60 / 24);
        seconds %= (60 * 60 * 24);
        int hours = int(seconds / 60 / 60);
        seconds %= (60 * 60);
        int minutes = int(seconds / 60);
        seconds %= 60;

        std::string ret;
        if (days) ret += std::to_string(days) + "d ";
        if (hours) ret += std::to_string(hours) + "h ";
        return (ret += std::to_string(minutes) + "m " + std::to_string(seconds) + "s", ret);
    }

    void Score::printStats() const {
        std::cout << "Score: " << this->correct << " : " << this->incorrect << " (" << (this->correct + this->incorrect ? ((float)this->correct / (this->correct + this->incorrect)) * 100 : 100.0f) << "%)" << std::endl
                  << "Completion: " << this->correct + this->incorrect << " / " << this->maxNumber << " (" << (((float)this->correct + this->incorrect) / this->maxNumber) * 100 << "%)" << std::endl << std::endl;
    }

    bool Score::operator>(Score& s) {
        return time > s.time;
    }

    bool Score::operator<(Score& s) {
        return time < s.time;
    }

    bool Score::operator>=(Score& s) {
        return time >= s.time;
    }

    bool Score::operator<=(Score& s) {
        return time <= s.time;
    }
}
