
#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>
#include <ctime>

#include "Utils.h"
#include "Leaderboard.h"
#include "Score.h"

#define KGRN "\x1B[1;32m"
#define KRED "\x1B[1;31m"
#define KYEL "\x1B[1;33m"
#define KRESET "\033[0m"

typedef unsigned char byte;

int main() {
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);
    cmyui::Score s;
     
    s.maxNumber = (std::cout << "Max: ", cmyui::getIntInRange(0, 99));
    s.time = time(0); // start time, will be changed to end time at end.
    cmyui::clearScreen();

    cmyui::Leaderboard lb("scores.db");
    std::vector<int> x = cmyui::generateTable(s.maxNumber), y = cmyui::generateTable(s.maxNumber), input;

    for (byte i = 0; i < s.maxNumber; i++) {
        std::cout << "Score: " << s.correct << " : " << s.incorrect << " (" << (s.correct + s.incorrect ? ((float)s.correct / (s.correct + s.incorrect)) * 100 : 100.0f) << "%)" << std::endl
                  << "Completion: " << s.correct + s.incorrect << " / " << s.maxNumber << " (" << (((float)s.correct + s.incorrect) / s.maxNumber) * 100 << "%)" << std::endl << std::endl
                  << "Whats " << x[i] << " * " << y[i] << "?" << std::endl
                  << "Ans: ";

        input.push_back(cmyui::getInt());
        std::cout << (input[i] == x[i] * y[i] ? "\x1B[1;32mCorrect!" : "\x1B[1;31mIncorrect!\033[0m - \x1B[1;32m" + std::to_string(x[i] * y[i])) << KRESET << std::endl;
        if (input[i] == x[i] * y[i]) s.correct++; else s.incorrect++;

        std::cout << std::endl << "Press and key to continue..";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore();

        cmyui::clearScreen();
    }

    lb += (s.date = time(0), s.time = s.date - s.time, s); // change start time to end time

    std::cout << "Walkthrough" << std::endl
              << "=---------=" << std::endl;
    for (byte i = 0; i < s.maxNumber; i++)
        std::cout << std::setw(2) << std::left << x[i] << '*' << std::setw(2) << std::right << y[i] << " = " << std::setw(3) << (input[i] == x[i] * y[i] ? KGRN : KRED) << input[i] << KRESET << " : " << std::setw(4) << std::left << x[i] * y[i] << std::endl;
  
    std::cout << std::endl << "Elapsed: " << s.getTimeFormatted(s.time) << std::endl << std::endl;
    lb.display(s.maxNumber);

    std::cout << std::endl << "Press enter to continue..";
    std::cin.ignore();

    return 0;
}
