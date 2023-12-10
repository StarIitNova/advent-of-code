#include "core.h"

int main() {
    std::vector<std::string> grid = AOC::split(AOC::trim(AOC::readfile("input.txt")), "\n");

    size_t sr = 0, sc = 0;
    for (size_t r = 0; r < grid.size(); r++) {
        bool found = false;
        for (size_t c = 0; c < grid[r].size(); c++) {
            if (grid[r][c] == 'S') {
                sr = r;
                sc = c;
                found = true;
                break;
            }
        }

        if (found)
            break;
    }

    std::vector<std::vector<size_t>> loop = {{sr, sc}};
    std::deque<std::vector<size_t>> deq = {{sr, sc}};

    const auto in = [](const std::vector<std::vector<size_t>> &vec, std::vector<size_t> v) -> bool {
        for (const auto &vec2 : vec)
            if (vec2[0] == v[0] && vec2[1] == v[1])
                return true;
        return false;
    };

    while (deq.size() > 0) {
        std::vector<size_t> vs = AOC::popf(deq);
        size_t r = vs[0], c = vs[1];
        char ch = grid[r][c];

        if (r > 0 && "S|JL"s.find(ch) != std::string::npos && "|7F"s.find(grid[r - 1][c]) != std::string::npos &&
            !in(loop, {r - 1, c})) {
            loop.push_back({r - 1, c});
            deq.push_back({r - 1, c});
        }

        if (r < grid.size() - 1 && "S|7F"s.find(ch) != std::string::npos &&
            "|JL"s.find(grid[r + 1][c]) != std::string::npos && !in(loop, {r + 1, c})) {
            loop.push_back({r + 1, c});
            deq.push_back({r + 1, c});
        }

        if (c > 0 && "S-J7"s.find(ch) != std::string::npos && "-LF"s.find(grid[r][c - 1]) != std::string::npos &&
            !in(loop, {r, c - 1})) {
            loop.push_back({r, c - 1});
            deq.push_back({r, c - 1});
        }

        if (c < grid[r].size() - 1 && "S-LF"s.find(ch) != std::string::npos &&
            "-J7"s.find(grid[r][c + 1]) != std::string::npos && !in(loop, {r, c + 1})) {
            loop.push_back({r, c + 1});
            deq.push_back({r, c + 1});
        }
    }

    printf("%d\n", loop.size() / 2);
}