#include "core.h"

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");

    size_t totalLen = 0, trueLen = 0;
    for (const auto &line : inputs) {
        std::string nLine = "\"";
        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] == '\\')
                nLine += "\\\\";
            else if (line[i] == '"')
                nLine += "\\\"";
            else
                nLine += line[i];
        }
        nLine += "\"";

        totalLen += nLine.size();
        trueLen += line.size();
    }

    std::cout << totalLen - trueLen << "\n";
}