#include "core.h"

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");

    size_t totalLen = 0, trueLen = 0;
    for (const auto &line : inputs) {
        totalLen += line.size();

        std::string nLine = line.substr(1, line.size() - 2);
        for (size_t i = 0; i < nLine.size(); i++) {
            if (nLine[i] == '\\') {
                if (nLine[i + 1] == 'x')
                    i += 2;
                i++;
            }

            trueLen++;
        }
    }

    std::cout << totalLen - trueLen << "\n";
}