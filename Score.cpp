#include "Score.h"

namespace cmyui {
    std::string Score::getTimeFormatted(int seconds) const {
        if (!seconds) return "now";
        std::string ret;
        int days = int(seconds / 60 / 60 / 24);
        seconds %= (60 * 60 * 24);
        int hours = int(seconds / 60 / 60);
        seconds %= (60 * 60);
        int minutes = int(seconds / 60);
        seconds %= 60;

        if (days) ret += std::to_string(days) + "d ";
        if (hours) ret += std::to_string(hours) + "h ";
        return (ret += std::to_string(minutes) + "m " + std::to_string(seconds) + "s", ret);
    }
}