// 00:08:40 #1986 (0*) | ~3 minute load time on question

#include "newcore.h"

int main() {
    aoc::vector<aoc::string> lines = aoc::vector<aoc::string>::from(aoc::split(aoc::read_file("input.txt"), "\n"));

    auto safe = [](const aoc::vector<int> &levels) -> bool {
        aoc::vector<int> diffs {};
        for (int i = 1; i < levels.size(); i++) {
            diffs.push_back(levels[i] - levels[i - 1]);
        }

        return aoc::all(aoc::map([](int x) { return aoc::within(1, x, 3); }, diffs)) |
               aoc::all(aoc::map([](int x) { return aoc::within(-3, x, -1); }, diffs));
    };

    int count = 0;
    for (const auto &line : lines) {
        aoc::vector<int> levels = aoc::map(_aoc_strtoi, line.split());
        if (safe(levels)) count++;
    }

    std::cout << count << "\n";

    return 0;
}

