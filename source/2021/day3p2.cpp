#include "newcore.h"

int main() {
    aoc::vector<aoc::string> lines = aoc::vector<aoc::string>::from(aoc::split(aoc::read_file("input.txt"), "\n"));
    lines = aoc::rotate(lines);

    std::string binary = "", eps = "";
    for (const auto &line : lines) {
        int ones = std::count(line.begin(), line.end(), '1'), zeros = std::count(line.begin(), line.end(), '0');
        binary += (ones > zeros ? '1' : '0');
        eps += (ones > zeros ? '0' : '1');
    }

    std::cout << std::strtoull(binary.c_str(), nullptr, 2) * std::strtoull(eps.c_str(), nullptr, 2) << "\n";

    return 0;
}
