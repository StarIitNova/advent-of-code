// 00:33:29 #5180 (0*) | pretty huge difficulty spike, 30 minutes and still top 5K. Trick is you can't just remove a fail

#include "core.h"

bool fails(std::vector<int> data, int skipIdx = -1) {
    int lock = 0;
    int prev = data[0];
    int start = 1;
    if (skipIdx == 0) {
        prev = data[1];
        start = 2;
    }

    for (int x = start; x < data.size(); x++) {
        if (x == skipIdx) continue;
        int dif = data[x] - prev;
        if (std::abs(dif) < 1 || std::abs(dif) > 3 || (dif < 0 && lock > 0) || (dif > 0 && lock < 0)) {
            return true;
        }

        lock = lock == 0 ? (dif < 0 ? -1 : 1) : lock;
        prev = data[x];
    }

    return false;
}

int main() {
    std::vector<std::string> lines = AOC::split(AOC::readfile("input.txt"), "\n");

    int t = 0;
    std::vector<std::vector<int>> failures{};
    for (size_t i = 0; i < lines.size(); i++) {
        const auto &line = lines[i];
        std::vector<int> data = AOC::map(_aoc_strtoi, AOC::split(line, " "));

        if (!fails(data)) t++;
        else failures.push_back(data);
    }

    for (const auto &fail : failures) {
        for (int i = 0; i < fail.size(); i++) {
            if (!fails(fail, i)) {
                t++;
                break;
            }
        }
    }

    std::cout << t << "\n";

    return 0;
}

