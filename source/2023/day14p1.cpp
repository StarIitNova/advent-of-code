#include "core.h"

int main() {
    std::vector<std::string> grid = AOC::split(AOC::readfile("input.txt"), "\n");
    grid = AOC::rezip(grid);

    for (auto &row : grid) {
        std::vector<std::string> groups = AOC::split(row, "#", false);
        std::string nrow = "";
        for (auto &group : groups) {
            std::sort(group.begin(), group.end(), std::greater<char>());
            nrow += "#" + group;
        }

        row = nrow.substr(1);
    }

    grid = AOC::rezip(grid);

    size_t total = 0;
    for (size_t r = 0; r < grid.size(); r++)
        total += std::count(grid[r].begin(), grid[r].end(), 'O') * (grid.size() - r);

    std::cout << total << "\n";
}