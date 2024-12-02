// 00:08:40 #1986 (0*) | ~3 minute load time on question

#include "core.h"

int main() {
    std::vector<std::string> lines = AOC::split(AOC::readfile("input.txt"), "\n");

    int t = 0;
    for (size_t i = 0; i < lines.size(); i++) {
        const auto &line = lines[i];
        std::vector<int> data = AOC::map(_aoc_strtoi, AOC::split(line, " "));

        int lock = 0;
        int prev = data[0];
        bool fail = false;
        for (int x = 1; x < data.size(); x++) {
            int dif = data[x] - prev;
            if ((lock == -1 && dif <= 0) || (lock == 1 && dif >= 0) || dif == 0 || std::abs(dif) < 1 || std::abs(dif) > 3) {
                fail = true;
                break;
            }

            if (lock == 0)
                lock = dif < 0 ? 1 : -1;
            prev = data[x];
        }

        if (!fail) t++;
    }

    std::cout << t << "\n";

    return 0;
}

