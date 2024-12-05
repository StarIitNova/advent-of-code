#include "newcore.h"

int main() {
    aoc::vector<aoc::string> lines = aoc::vector<aoc::string>::from(aoc::split(aoc::read_file("input.txt"), "\n"));

    int horiz = 0, depth = 0;
    for (const auto &line : lines) {
        auto spl = line.split();
        if (spl[0] == "forward") horiz += _aoc_strtoi(spl[1]);
        else if (spl[0] == "down") depth += _aoc_strtoi(spl[1]);
        else if (spl[0] == "up") depth -= _aoc_strtoi(spl[1]);
    }

    std::cout << horiz * depth << "\n";

    return 0;
}
