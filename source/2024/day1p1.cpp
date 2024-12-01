// 00:12:10 #4921 (0*)

#include "core.h"

int main() {
    auto [a, b] = AOC::dualmapby(_aoc_strtoi, AOC::split(AOC::readfile("input.txt"), "\n"), "   ");
    AOC::sort(a, b);

    std::cout << AOC::apply(_aoc_sum<int>, AOC::maptwo(_aoc_dist<int>, a, b), 0) << "\n";

    return 0;
}

