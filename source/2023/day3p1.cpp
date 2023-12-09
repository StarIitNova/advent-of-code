#include "core.h"

bool check(std::vector<std::string> &bin, int x, int y, int col) {
    std::vector<int> toCheck = {
        x + 1 + y * cols, x + 1 + (y + 1) * cols, x + (y + 1) * cols, x - 1 + (y + 1) * cols,
        x - 1 + y * cols, x - 1 + (y - 1) * cols, x + (y - 1) * cols, x + 1 + (y - 1) * cols,
    };

    if (bin[x + 1 + y * cols] == "E")
        if (check(bin, x + 1, y, cols))
            return true;

    for (const auto &pos : toCheck)
        if (pos < bin.size())
            if (bin[pos] != "." && !isdigit(bin[pos][0]) && bin[pos] != "E")
                return true;

    return false;
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

            if (isdigit(bin[x + y * lineLen][0]))
                if (check(bin, x, y, lineLen))
                    total += std::stoi(bin[x + y * lineLen]);
        }
    }

    std::cout << total << "\n";
}