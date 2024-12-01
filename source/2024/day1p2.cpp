// 00:14:11 #3977 (0*)

#include "core.h"

int main() {
    auto [a, b] = AOC::dualmapby(_aoc_strtoi, AOC::split(AOC::readfile("input.txt"), "\n"), "   ");

    int sim = 0;
    for (const auto &ab : a)
        sim += AOC::count(ab, b) * ab;
    std::cout << sim << "\n";

    return 0;
}
