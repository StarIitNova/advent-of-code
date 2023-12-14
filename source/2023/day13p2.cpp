#include "core.h"

size_t getMirror(const std::vector<std::string> &grid) {
    for (size_t r = 1; r < grid.size(); r++) {
        auto above = AOC::subvec(AOC::subvec(grid, 0, r), -1, 0, -1);
        auto below = AOC::subvec(grid, r);

        size_t added = 0;
        for (size_t i = 0; i < AOC::min(above.size(), below.size()); ++i) {
            const auto &x = above[i];
            const auto &y = below[i];

            for (size_t j = 0; j < AOC::min(x.size(), y.size()); ++j) {
                added += (x[j] == y[j]) ? 0 : 1;
            }
        }

        if (added == 1)
            return r;
    }

    return 0;
}

int main() {
    std::vector<std::string> blocks = AOC::split(AOC::readfile("input.txt"), "\n\n");

    size_t total = 0;
    for (const auto &block : blocks) {
        std::vector<std::string> grid = AOC::split(block, "\n");

        size_t row = getMirror(grid);
        size_t col = getMirror(AOC::rezip(grid));

        total += col + row * 100;
    }

    std::cout << total << "\n";
}