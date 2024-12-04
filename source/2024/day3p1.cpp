// >24h #102778 (0*) | I'm so good at javascript regex and std::regex matches ecmascript's standard

#include "newcore.h"

int main() {
    aoc::vector<aoc::string> lines = aoc::vector<aoc::string>::from(aoc::split(aoc::read_file("input.txt"), "\n"));

    std::regex pattern("mul\\((\\d{1,3}),(\\d{1,3})\\)");

    int total = 0;
    for (const auto &line : lines) {
        std::sregex_iterator it(line.begin(), line.end(), pattern);
        std::sregex_iterator end;

        while (it != end) {
            std::smatch match = *it;
            total += std::stoi(match[1]) * std::stoi(match[2]);
            ++it;
        }
    }

    std::cout << total << "\n";

    return 0;
}
