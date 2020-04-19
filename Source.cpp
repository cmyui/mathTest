
#include <iostream>
#include <sstream>
#include <limits>
#include <vector>
#include <iomanip>
#include <ctime>

#include "Utils.h"
#include "Leaderboard.h"
#include "Score.h"
#include "Menu.h"
#include "MenuItem.h"

#define KGRN "\x1B[1;32m"
#define KRED "\x1B[1;31m"
#define KYEL "\x1B[1;33m"
#define KRESET "\033[0m"

typedef unsigned char byte;


cmyui::Score playGame(int limit) {
    cmyui::Score s;

    s.maxNumber = limit;
    s.time = time(0); // start time, will be changed to end time at end.
    cmyui::clearScreen();

    std::vector<int> x = cmyui::generateTable(s.maxNumber), y = cmyui::generateTable(s.maxNumber), input;

    for (byte i = 0; i < s.maxNumber; i++) { // question loop
        std::cout << "Score: " << s.correct << " : " << s.incorrect << " (" << (s.correct + s.incorrect ? ((float)s.correct / (s.correct + s.incorrect)) * 100 : 100.0f) << "%)" << std::endl
                  << "Completion: " << s.correct + s.incorrect << " / " << s.maxNumber << " (" << (((float)s.correct + s.incorrect) / s.maxNumber) * 100 << "%)" << std::endl << std::endl
                  << "Whats " << x[i] << " * " << y[i] << "?" << std::endl
                  << "Ans: ";

        input.push_back(cmyui::getInt());
        std::cout << (input[i] == x[i] * y[i] ? "\x1B[1;32mCorrect!" : "\x1B[1;31mIncorrect!\033[0m - \x1B[1;32m" + std::to_string(x[i] * y[i])) << KRESET << std::endl;
        if (input[i] == x[i] * y[i]) s.correct++; else s.incorrect++;

        std::cout << std::endl << "Press enter to continue..";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore();

        cmyui::clearScreen();
    }

    s.date = time(0), s.time = s.date - s.time; // set the score's date to now.

    std::cout << "Walkthrough" << std::endl
              << "=---------=" << std::endl;
    for (byte i = 0; i < s.maxNumber; i++)
        std::cout << std::setw(2) << std::left << x[i] << '*' << std::setw(2) << std::right << y[i] << " = " << std::setw(3) << (input[i] == x[i] * y[i] ? KGRN : KRED) << input[i] << KRESET << " : " << std::setw(4) << std::left << x[i] * y[i] << std::endl;

    std::cout << std::endl << "Elapsed: " << s.getTimeFormatted(s.time) << std::endl << std::endl;

    return s;
}

int main() {
    const float __version = 2.23;

    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);

    std::stringstream __name;
    __name << std::fixed << std::setprecision(2) << __version;
    cmyui::Menu m("mathTest v" + __name.str());

    cmyui::Leaderboard lb("scores.db");

    m.addItem("Play mathTest.");
    m.addItem("Check leaderboards.");

    for (;;) { // game loop
        // Main menu
        switch (m.run()) {
        case 1: {
            int limit = (std::cout << "Max: ", cmyui::getIntInRange(0, 99));
            lb += playGame(limit);
            lb.display(limit);
            break;
        }
        case 2: {
            lb.display((std::cout << "Max: ", cmyui::getIntInRange(0, 99)));
            std::cin.ignore();
            break;
        }
        case 0: return 0;
        }

        std::cout << std::endl << "Press enter to continue..";
        std::cin.ignore();
        cmyui::clearScreen();
    }
    return 0;
}
