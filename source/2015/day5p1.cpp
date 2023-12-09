#include "core.h"

std::vector<std::string> banned = {"ab", "cd", "pq", "xy"};

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");

    size_t nice = 0;
    for (const auto &input : inputs) {
        short vowels = 0;
        size_t i = 0;
        while ((i = input.find_first_of("aeiou", i)) != std::string::npos) {
            vowels++;
            i++;
        }

        if (vowels < 3)
            continue;

        short doubles = 0;
        for (i = 1; i < input.size(); i++)
            if (input[i] == input[i - 1])
                doubles++;

        if (doubles == 0)
            continue;

        bool fail = false;
        for (const auto &ban : banned) {
            if (input.find(ban) != std::string::npos) {
                fail = true;
                break;
            }
        }

        if (fail)
            continue;

        nice++;
    }

    printf("%d\n", nice);
}