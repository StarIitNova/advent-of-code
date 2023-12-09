#include "core.h"

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");

    size_t total = 0;
    for (const auto &line : inputs) {
        std::string x = AOC::trim(AOC::split(line, ":")[1]);
        std::vector<std::vector<size_t>> vals;
        for (const auto &spl : AOC::split(x, " | "))
            vals.push_back(AOC::map<size_t, std::string>(_aoc_strtoull, AOC::split(spl)));
        std::vector<size_t> a = vals[0], b = vals[1];

        size_t count = 0;
        for (const auto &bb : b)
            for (const auto &aa : a)
                if (aa == bb)
                    count++;

        if (count > 0)
            total += (size_t)std::pow(2ull, count - 1);
    }

    printf("%d\n", total);
}