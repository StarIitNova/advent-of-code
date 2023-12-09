#include "core.h"

int main() {
    std::string input = AOC::readfile("input.txt");

    size_t val = 0;
    while (true) {
        val++;
        std::string v = input + std::to_string(val);
        std::string md5 = AOC::MD5(v);

        if (md5.substr(0, 5) == "00000")
            break;
    }

    std::cout << val << "\n";
}