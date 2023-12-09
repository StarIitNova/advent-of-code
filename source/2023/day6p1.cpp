#include "core.h"

int main() {
    std::vector<std::string> data = AOC::split(AOC::readfile("input.txt"), "\n");
    std::string timestr = AOC::split(data[0], ":")[1];
    std::string diststr = AOC::split(data[1], ":")[1];

    std::vector<size_t> times = AOC::map<size_t, std::string>(_aoc_strtoull, AOC::split(timestr));
    std::vector<size_t> dists = AOC::map<size_t, std::string>(_aoc_strtoull, AOC::split(diststr));

    size_t minTime = 1;
    for (size_t i = 0; i < times.size(); i++) {
        size_t time = times[i], dist = dists[i];

        size_t minzTime = 0;
        for (size_t i = 0; i < time; i++) {
            if ((time - i) * i > dist) {
                minzTime = i;
                break;
            }
        }

        minTime *= (time - minzTime * 2 + 1);
    }

    printf("%d\n", minTime);
}