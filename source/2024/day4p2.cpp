// 00:21:03 #1917 (0*)

#include "newcore.h"

int main() {
    aoc::vector<aoc::string> lines = aoc::vector<aoc::string>::from(aoc::split(aoc::read_file("input.txt"), "\n"));

    int res = 0;
    for (size_t y = 0; y < lines.size(); y++) {
        for (size_t x = 0; x < lines[y].size(); x++) {
            int xmas = 0;
            if (lines[y][x] == 'A') {
                if (x > 0 && x < lines[y].size() - 1 && y > 0 && y < lines.size() - 1) {
                    if (lines[y - 1][x - 1] == 'M' && lines[y + 1][x + 1] == 'S') {
                        if (lines[y - 1][x + 1] == 'M' && lines[y + 1][x - 1] == 'S') xmas++;
                        else if (lines[y + 1][x - 1] == 'M' && lines[y - 1][x + 1] == 'S') xmas++;
                    } else if (lines[y + 1][x + 1] == 'M' && lines[y - 1][x - 1] == 'S') {
                        if (lines[y - 1][x + 1] == 'M' && lines[y + 1][x - 1] == 'S') xmas++;
                        else if (lines[y + 1][x - 1] == 'M' && lines[y - 1][x + 1] == 'S') xmas++;
                    }
                }
            }
            res += xmas;
        }
    }

    std::cout << res << "\n";

    return 0;
}


