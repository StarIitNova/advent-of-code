#include "core.h"

int main() {
    std::vector<std::string> data = AOC::split(AOC::readfile("input.txt"), "\n");
    std::string times = AOC::split(data[0], ":")[1];
    std::string dists = AOC::split(data[1], ":")[1];

    times = AOC::removeAll(times, " "), dists = AOC::removeAll(dists, " ");
    size_t time = std::stoll(times), dist = std::stoll(dists);

    size_t minTime = 0;
    for (size_t i = 0; i < time; i++) {
        if ((time - i) * i > dist) {
            minTime = i;
            break;
        }
    }

    std::cout << time - minTime * 2 + 1 << "\n";
}