// 00:07:51 #1122 (0*)

#include "newcore.h"

int main() {
    aoc::vector<aoc::string> lines = aoc::vector<aoc::string>::from(aoc::split(aoc::read_file("input.txt"), "\n"));

    int res = 0;
    for (size_t y = 0; y < lines.size(); y++) {
        for (size_t x = 0; x < lines[y].size(); x++) {
            int xmas = 0;
            if (lines[y][x] == 'X') {
                if (x > 2) {
                    if (lines[y][x - 1] == 'M' && lines[y][x - 2] == 'A' && lines[y][x - 3] == 'S') xmas++;
                    if (y > 2)
                        if (lines[y - 1][x - 1] == 'M' && lines[y - 2][x - 2] == 'A' && lines[y - 3][x - 3] == 'S') xmas++;
                    if (y < lines.size() - 3)
                        if (lines[y + 1][x - 1] == 'M' && lines[y + 2][x - 2] == 'A' && lines[y + 3][x - 3] == 'S') xmas++;
                }

                if (x < lines[y].size() - 3) {
                    if (lines[y][x + 1] == 'M' && lines[y][x + 2] == 'A' && lines[y][x + 3] == 'S') xmas++;
                    if (y > 2)
                        if (lines[y - 1][x + 1] == 'M' && lines[y - 2][x + 2] == 'A' && lines[y - 3][x + 3] == 'S') xmas++;
                    if (y < lines.size() - 3)
                        if (lines[y + 1][x + 1] == 'M' && lines[y + 2][x + 2] == 'A' && lines[y + 3][x + 3] == 'S') xmas++;
                }

                if (y > 2)
                    if (lines[y - 1][x] == 'M' && lines[y - 2][x] == 'A' && lines[y - 3][x] == 'S') xmas++;
                if (y < lines.size() - 3)
                    if (lines[y + 1][x] == 'M' && lines[y + 2][x] == 'A' && lines[y + 3][x] == 'S') xmas++;
            }
            res += xmas;
        }
    }

    std::cout << res << "\n";

    return 0;
}

