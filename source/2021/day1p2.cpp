#include "newcore.h"

int main() {
    aoc::vector<aoc::string> lines = aoc::vector<aoc::string>::from(aoc::split(aoc::read_file("input.txt"), "\n"));

    int prev = -1, c = 0;
    for (int i = 0; i < lines.size() - 2; i++) {
        int val = _aoc_strtoi(lines[i]) + _aoc_strtoi(lines[i + 1]) + _aoc_strtoi(lines[i + 2]);
        if (prev < val) c++;
        prev = val;
    }

    std::cout << c - 1 << "\n";

    return 0;
}
