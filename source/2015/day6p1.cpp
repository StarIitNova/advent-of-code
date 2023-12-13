#include "core.h"

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");

    std::map<size_t, bool> toggled{};

    for (const auto &input : inputs) {
        auto info = AOC::split(input.substr(input.find_first_of("0123456789")), " through ");
        // 0 = off, 1 = on, 2 = toggle
        short mode = input.find("toggle") != std::string::npos ? 2 : (input.find("on") != std::string::npos ? 1 : 0);

        auto point1 = AOC::map<size_t, std::string>(_aoc_strtoull, AOC::split(info[0], ","));
        auto point2 = AOC::map<size_t, std::string>(_aoc_strtoull, AOC::split(info[1], ","));

        for (size_t x = point1[0]; x <= point2[0]; x++) {
            for (size_t y = point1[1]; y <= point2[1]; y++) {
                if (!toggled.count(x + y * 1000))
                    toggled[x + y * 1000] = false;

                if (mode == 0)
                    toggled[x + y * 1000] = false;
                else if (mode == 1)
                    toggled[x + y * 1000] = true;
                else
                    toggled[x + y * 1000] = !toggled[x + y * 1000];
            }
        }
    }

    size_t lights = 0;
    for (const auto &[_k, lit] : toggled)
        if (lit)
            lights++;

    std::cout << lights << "\n";
}