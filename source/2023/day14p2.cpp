#include "core.h"

std::vector<std::string> grid{};

void cycle() {
    for (size_t i = 0; i < 4; i++) {
        grid = AOC::rezip(grid);

        for (auto &row : grid) {
            std::vector<std::string> groups = AOC::split(row, "#", false);
            std::string nrow = "";
            for (auto &group : groups) {
                std::sort(group.begin(), group.end(), std::greater<char>());
                nrow += group + "#";
            }

            row = nrow.substr(0, nrow.size() - 1);
        }

        for (auto &row : grid)
            row = AOC::reverse(row);
    }
}

int main() {
    grid = AOC::split(AOC::readfile("input.txt"), "\n");
    std::vector<std::vector<std::string>> seen{grid};

    size_t iter = 0;
    while (true) {
        iter++;
        cycle();
        bool already = false;
        for (const auto &g : seen) {
            if (AOC::vecEquals(g, grid)) {
                already = true;
                break;
            }
        }

        if (already)
            break;

        seen.push_back(grid);
    }

    size_t first = 0;
    for (size_t i = 0; i < seen.size(); i++) {
        if (AOC::vecEquals(seen[i], grid)) {
            first = i;
            break;
        }
    }

    grid = seen[(1000000000 - first) % (iter - first) + first];

    size_t total = 0;
    for (size_t r = 0; r < grid.size(); r++)
        total += std::count(grid[r].begin(), grid[r].end(), 'O') * (grid.size() - r);

    std::cout << total << "\n";
}