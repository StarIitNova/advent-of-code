// 00:11:48 #1552 (0*)

#include "newcore.h"

int main() {
    aoc::vector<aoc::string> lines = aoc::vector<aoc::string>::from(aoc::split(aoc::read_file("input.txt"), "\n", false));

    int xm = lines[0].length(), ym = lines.size();
    int x = 0, y = 0;
    int dy = -1, dx = 0;

    for (int xx = 0; xx < lines.size(); xx++) {
        for (int yy = 0; yy < lines[xx].size(); yy++) {
            char c = lines[xx].at(yy);
            if (c == '^') {
                x = yy;
                y = xx;
                break;
            }
        }
    }

    std::set<aoc::vector<int>> map;
    while (x >= 0 && x < xm && y >= 0 && y < ym) {
        map.insert(aoc::vector<int>({ x, y }));
        if (x + dx < 0 || y + dy < 0 || x + dx >= xm || y + dy >= ym) break;
        if (lines[y + dy][x + dx] == '#') {
            int temp = dy;
            dy = dx;
            dx = -temp;
        } else {
            x += dx;
            y += dy;
        }
    }

    std::cout << map.size() << "\n";

    return 0;
}

