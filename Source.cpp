
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

#define VERSION "2.23"

#define KGRN "\x1B[1;32m"
#define KRED "\x1B[1;31m"
#define KYEL "\x1B[1;33m"
#define KRESET "\033[0m"

cmyui::Score playGame(int limit, int num_questions) {
    cmyui::Score s{};

    s.maxNumber = limit;
    s.time = time(0); // start time, will be changed to end time at end.
    cmyui::clearScreen();

    std::vector<int> x = cmyui::generateTable(s.maxNumber);
    std::vector<int> y = cmyui::generateTable(s.maxNumber);
    std::vector<int> input{};

    for (auto i = 0; i < s.maxNumber; i++) { // question loop
        s.printStats();

        // read an int from user (stdin)
        std::cout << "Whats " << x[i] << " * " << y[i] << "?" << std::endl
                  << "Ans: ";

        input.push_back(cmyui::getInt()); // repeats until it gets one

        if (input[i] == x[i] * y[i]) {
            s.correct++;
            std::cout << KGRN "Correct!" KRESET << std::endl;
        } else {
            s.incorrect++;
            std::cout << KRED << "Incorrect! " KRESET + std::to_string(x[i] * y[i]) << std::endl;
        }

        std::cout << std::endl << "Press enter to continue..";

        // wait for user to press enter
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore();

        cmyui::clearScreen();
    }

    s.date = time(0), s.time = s.date - s.time; // set the score's date to now.

    std::cout << "Walkthrough" << std::endl
              << "=---------=" << std::endl;
    for (auto i = 0; i < s.maxNumber; i++)
        std::cout << std::setw(2) << std::left << x[i] << '*' << std::setw(2) << std::right << y[i] << " = " << std::setw(3) << (input[i] == x[i] * y[i] ? KGRN : KRED) << input[i] << KRESET << " : " << std::setw(4) << std::left << x[i] * y[i] << std::endl;

    std::cout << std::endl << "Elapsed: " << s.getTimeFormatted(s.time) << std::endl << std::endl;

    return s;
}

int main() {
    cmyui::Menu m("mathTest v" VERSION);

    // load leaderboards from db on disk
    cmyui::Leaderboard lb("scores.db");

    m.addItem("Play mathTest.");
    m.addItem("Check leaderboards.");

    int max_number{}, num_questions{};
    cmyui::Score score;

    for (;;) { // game loop
        // Main menu
        switch (m.run()) {
        case 1: {
            // get game configuration from user
            std::cout << "Max number: ";
            max_number = cmyui::getIntInRange(0, 99);
            std::cout << "Number of questions: ";
            num_questions = cmyui::getIntInRange(0, 99);

            // play through the game, returning the users scores
            score = playGame(max_number, num_questions);

            // add the score to the leaderboard & display it to user
            lb.addScore(score);
            lb.display(max_number);
            break;
        }
        case 2: {
            std::cout << "Max number: ";
            max_number = cmyui::getIntInRange(0, 99);

            lb.display(max_number);
            std::cin.ignore();
            break;
        }
        case 0:
            return 0;
        }

        std::cout << std::endl << "Press enter to continue..";
        std::cin.ignore();
        cmyui::clearScreen();
    }
    return 0;
}
