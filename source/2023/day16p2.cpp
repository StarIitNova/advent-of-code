// this takes like 4 minutes to run, please be patient

#include "core.h"

std::vector<std::string> grid{};
size_t calc(long long r, long long c, long long dr, long long dc) {
    std::vector<std::vector<long long>> seen{};
    std::deque<std::vector<long long>> q{{r, c, dr, dc}};

    while (q.size() > 0) {
        std::vector<long long> vs = AOC::popf(q);
        r = vs[0], c = vs[1], dr = vs[2], dc = vs[3];

        r += dr;
        c += dc;

        if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size())
            continue;

        char ch = grid[r][c];
        if (ch == '.' || (ch == '-' && dc != 0) || (ch == '|' && dr != 0)) {
            if (std::find(seen.begin(), seen.end(), std::vector<long long>{r, c, dr, dc}) == seen.end()) {
                seen.push_back(std::vector<long long>{r, c, dr, dc});
                q.push_back(std::vector<long long>{r, c, dr, dc});
            }
        } else if (ch == '/') {
            long long temp = dc;
            dc = -dr;
            dr = -temp;
            if (std::find(seen.begin(), seen.end(), std::vector<long long>{r, c, dr, dc}) == seen.end()) {
                seen.push_back(std::vector<long long>{r, c, dr, dc});
                q.push_back(std::vector<long long>{r, c, dr, dc});
            }
        } else if (ch == '\\') {
            long long temp = dc;
            dc = dr;
            dr = temp;
            if (std::find(seen.begin(), seen.end(), std::vector<long long>{r, c, dr, dc}) == seen.end()) {
                seen.push_back(std::vector<long long>{r, c, dr, dc});
                q.push_back(std::vector<long long>{r, c, dr, dc});
            }
        } else {
            for (const auto &cont : (ch == '|' ? std::vector<std::vector<long long>>{{1, 0}, {-1, 0}}
                                               : std::vector<std::vector<long long>>{{0, 1}, {0, -1}})) {
                dr = cont[0], dc = cont[1];
                if (std::find(seen.begin(), seen.end(), std::vector<long long>{r, c, dr, dc}) == seen.end()) {
                    seen.push_back(std::vector<long long>{r, c, dr, dc});
                    q.push_back(std::vector<long long>{r, c, dr, dc});
                }
            }
        }
    }

    std::vector<std::vector<long long>> coords{};
    for (const auto &v : seen) {
        if (std::find(coords.begin(), coords.end(), std::vector<long long>{v[0], v[1]}) == coords.end())
            coords.push_back(std::vector<long long>{v[0], v[1]});
    }

    return coords.size();
}

int main() {
    grid = AOC::split(AOC::readfile("input.txt"), "\n");

    size_t maxVal = 0;

    for (size_t r = 0; r < grid.size(); r++) {
        maxVal = AOC::max(maxVal, calc(r, -1, 0, 1));
        maxVal = AOC::max(maxVal, calc(r, grid[0].size(), 0, -1));
    }

    for (size_t c = 0; c < grid.size(); c++) {
        maxVal = AOC::max(maxVal, calc(-1, c, 1, 0));
        maxVal = AOC::max(maxVal, calc(grid.size(), c, -1, 0));
    }

    std::cout << maxVal << "\n";
}