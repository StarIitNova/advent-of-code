#include "core.h"

size_t hash(std::string str) {
    size_t val = 0;

    for (size_t i = 0; i < str.size(); i++) {
        val += (int)str[i];
        val *= 17;
        val %= 256;
    }

    return val;
}

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::trim(AOC::readfile("input.txt")), ",");

    std::cout << AOC::sum(AOC::map<size_t, std::string>(hash, inputs)) << "\n";
}