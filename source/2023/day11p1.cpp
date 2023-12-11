#include "core.h"

struct Point {
    size_t x = 0, y = 0;
};

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");

    std::vector<size_t> emptyRows = {};
    std::vector<size_t> emptyColumns = {};
    std::vector<Point> points = {};

    for (size_t r = 0; r < inputs.size(); r++) {
        std::string row = inputs[r];
        if (row.find_first_not_of('.') == std::string::npos)
            emptyRows.push_back(r);
    }

    for (size_t c = 0; c < inputs[0].size(); c++) {
        bool good = true;
        for (size_t r = 0; r < inputs.size(); r++) {
            if (inputs[r][c] != '.') {
                good = false;
                break;
            }
        }
        if (good)
            emptyColumns.push_back(c);
    }

    for (size_t r = 0; r < inputs.size(); r++) {
        for (size_t c = 0; c < inputs[r].size(); c++) {
            if (inputs[r][c] == '#')
                points.push_back(Point{r, c});
        }
    }

    const auto in = [](const std::vector<size_t> &vec, size_t v) -> bool {
        for (const auto &vv : vec)
            if (vv == v)
                return true;
        return false;
    };

    size_t total = 0, scale = 2;
    for (size_t i = 0; i < points.size(); i++) {
        Point p1 = points[i];
        for (size_t x = 0; x < i; x++) {
            Point p2 = points[x];
            for (size_t r = AOC::min(p1.x, p2.x); r < AOC::max(p1.x, p2.x); r++) {
                total += in(emptyRows, r) ? scale : 1;
            }

            for (size_t c = AOC::min(p1.y, p2.y); c < AOC::max(p1.y, p2.y); c++) {
                total += in(emptyColumns, c) ? scale : 1;
            }
        }
    }

    printf("%d\n", total);
}