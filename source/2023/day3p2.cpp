#include "core.h"

size_t getGearRatio(std::vector<std::string> &bin, int x, int y, int cols) {
    std::vector<int> toCheck = {
        x + 1 + y * cols, x + 1 + (y + 1) * cols, x + (y + 1) * cols, x - 1 + (y + 1) * cols,
        x - 1 + y * cols, x - 1 + (y - 1) * cols, x + (y - 1) * cols, x + 1 + (y - 1) * cols,
    };

    int num1 = 0;
    int num2 = 0;
    size_t aPos = 0;

    for (const auto &pos : toCheck) {
        if (pos < bin.size()) {
            if (bin[pos] == "E" || isdigit(bin[pos][0])) {
                int cpos = pos;
                while (bin[cpos] == "E")
                    cpos--;
                if (num1 == 0) {
                    num1 = std::stoi(bin[cpos]);
                    aPos = cpos;
                } else if (cpos != aPos)
                    num2 = std::stoi(bin[cpos]);
            }
        }
    }

    return num1 * num2;
}

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");
    std::vector<std::string> bin{};

    size_t lineLen = 0, lineCount = 0;
    while (const auto &input : inputs) {
        lineCount++;
        lineLen = input.size();
        for (size_t i = 0; i < input.size(); i++) {
            if (isdigit(input[i])) {
                size_t start = i;
                while (isdigit(input[i]))
                    i++;
                bin.push_back(input.substr(start, i - start));
                for (size_t x = 0; x < i - start - 1; x++)
                    bin.push_back("E");
                i--;
            } else
                bin.push_back(std::string(1, input[i]));
        }
    }

    size_t total = 0;
    for (size_t y = 0; y < lineCount; y++) {
        for (size_t x = 0; x < lineLen; x++) {
            if (bin[x + y * lineLen].empty())
                continue;

            if (bin[x + y * lineLen] == "*")
                total += getGearRatio(bin, x, y, lineLen);
        }
    }

    std::cout << total << "\n";
}