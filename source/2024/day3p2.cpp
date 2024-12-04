// >24h #91814 (0*) | so add another regex condition?

#include "newcore.h"

int main() {
    aoc::vector<aoc::string> lines = aoc::vector<aoc::string>::from(aoc::split(aoc::read_file("input.txt"), "\n"));

    std::regex pattern("mul\\((\\d{1,3}),(\\d{1,3})\\)|do\\(\\)|don't\\(\\)");

    int total = 0;
    bool on = true;
    for (const auto &line : lines) {
        std::sregex_iterator it(line.begin(), line.end(), pattern);
        std::sregex_iterator end;

        while (it != end) {
            std::smatch match = *it;
            if (match[0] == "do()") on = true;
            else if (match[0] == "don't()") on = false;
            else if (on) total += std::stoi(match[1]) * std::stoi(match[2]);
            ++it;
        }
    }

    std::cout << total << "\n";

    return 0;
}
