// 01:30:06 #5874 (0*) | difficulty curve much?

#include "newcore.h"

int main() {
    aoc::vector<aoc::string> lines = aoc::vector<aoc::string>::from(aoc::split(aoc::read_file("input.txt"), "\n", false));

    int xm = lines[0].length(), ym = lines.size();
    int sx = 0, sy = 0;

    for (int xx = 0; xx < lines.size(); xx++) {
        for (int yy = 0; yy < lines[xx].size(); yy++) {
            char c = lines[xx].at(yy);
            if (c == '^') {
                sx = yy;
                sy = xx;
                break;
            }
        }
    }

    auto test = [&](int x, int y) {
        int dy = -1, dx = 0;

        std::set<aoc::vector<int>> map;
        while (true) {
            map.insert(aoc::vector<int>({ x, y, dy, dx }));
            if (x + dx < 0 || y + dy < 0 || x + dx >= xm || y + dy >= ym) return false;
            if (lines[y + dy][x + dx] == '#') {
                int temp = dy;
                dy = dx;
                dx = -temp;
            } else {
                x += dx;
                y += dy;
            }

            if (map.find(aoc::vector<int>({ x, y, dy, dx })) != map.end()) {
                return true;
            }
        }
    };

    int total = 0;
    for (int y = 0; y < ym; y++) {
        for (int x = 0; x < xm; x++) {
            if (lines[y][x] != '.') continue;
            lines[y][x] = '#';
            if (test(sx, sy)) total++;
            lines[y][x] = '.';
        }
    }

    std::cout << total << "\n";

    return 0;
}

