#include "core.h"

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");

    int total = 0;
    for (auto &input : inputs) {
        std::string val =
            input.substr(input.find_first_of("0123456789"), 1) + input.substr(input.find_last_of("0123456789"), 1);
        total += std::stoi(val);
    }

    std::cout << total << std::endl;
    return 0;
}