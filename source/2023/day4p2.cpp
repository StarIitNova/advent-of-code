#include "core.h"

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");

    std::map<size_t, size_t> map;
    for (size_t i = 0; i < inputs.size(); i++) {
        std::string line = inputs[i];
        if (!map.count(i))
            map[i] = 1;

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

        for (size_t n = i + 1; n < i + count + 1; n++) {
            if (!map.count(n))
                map[n] = 1;
            map[n] += map[i];
        }
    }

    size_t total = 0;
    for (const auto &[a, val] : map)
        total += val;

    printf("%d\n", total);
}