#include "core.h"

std::vector<std::string> banned = {"ab", "cd", "pq", "xy"};

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");

    size_t nice = 0;
    for (const auto &input : inputs) {
        bool hasRepBet = false, hasDoubleDouble = false;
        for (size_t i = 2; i < input.size(); i++) {
            if (input[i - 2] == input[i])
                hasRepBet = true;
            if (input.find(input.substr(i - 2, 2), i) != std::string::npos)
                hasDoubleDouble = true;
        }

        if (hasRepBet && hasDoubleDouble)
            nice++;
    }

    printf("%d\n", nice);
}