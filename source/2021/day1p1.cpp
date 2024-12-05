#include "newcore.h"

int main() {
    aoc::vector<aoc::string> lines = aoc::vector<aoc::string>::from(aoc::split(aoc::read_file("input.txt"), "\n"));

    int prev = -1, c = 0;
    for (const auto &line : lines) {
        if (prev < _aoc_strtoi(line)) c++;
        prev = _aoc_strtoi(line);
    }

    std::cout << c - 1 << "\n";

    return 0;
}
