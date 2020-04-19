#include "Score.h"

namespace cmyui {
    std::string Score::getTimeFormatted(int input) const {
        if (!input) return "now";
        int seconds = input;
        int hours = seconds / 60.f / 60.f;
        seconds = input % (60 * 60);
        int minutes = seconds / 60.f;
        seconds = input % 60;
        return std::to_string(hours) + "h " + std::to_string(minutes) + "m " + std::to_string(seconds) + "s";
    }
}