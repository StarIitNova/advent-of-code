#include "core.h"

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");

    size_t total = 0;
    for (const auto &input : inputs) {
        std::vector<int> dimensions = AOC::sortip(AOC::map<int, std::string>(_aoc_strtoi, AOC::split(input, "x")));
        total += dimensions[0] * dimensions[1] * dimensions[2] + dimensions[0] * 2 + dimensions[1] * 2;
    }

    std::cout << total << "\n";
}