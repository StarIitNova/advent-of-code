// redo

#include "core.h"

std::vector<std::vector<int>> points = {{0, 0}};
std::map<std::string, std::vector<int>> dirs = {{"U", {-1, 0}}, {"D", {1, 0}}, {"L", {0, -1}}, {"R", {0, 1}}};

int main() {
    int b = 0;

    for (const auto &line : AOC::split(AOC::readfile("input.txt"), "\n")) {
        auto contents = AOC::split(line);
        auto d = contents[0], n = contents[1];
        auto dir = dirs[d];
        auto dr = dir[0], dc = dir[1];
        int n2 = std::stoi(n);

        b += n2;

        auto r = points.back()[0], c = points.back()[1];
        points.push_back({r + dr * n2, c + dc * n2});
    }

    int A = 0;
    for (int i = 0; i < points.size(); i++) {
        A += points[i][0] * (points[i - 1][1] - points[(i + 1) % points.size()][1]);
    }
    A = std::abs(A);
    int i = A - b;
    std::cout << i + b << "\n";
}