#include <iostream>
#include <string>
#include <vector>

// part 1
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

// part 2
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
    std::vector<std::string> bin{};

    std::string input;

    size_t lineLen = 0, lineCount = 0;
    while (std::getline(std::cin, input)) {
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

            // part 2
            if (bin[x + y * lineLen] == "*")
                total += getGearRatio(bin, x, y, lineLen);

            // part 1
            // if (isdigit(bin[x + y * lineLen][0])) {
            //     // part 1
            //     if (check(bin, x, y, lineLen)) {
            //         total += std::stoi(bin[x + y * lineLen]);
            //     }

            //     // test code
            //     // std::cout << (check(bin, x, y, lineLen) ? "T" : "F");
            // } // else {
            //   // test code
            //   // std::cout << bin[x + y * lineLen];
            // // }
        }
        // test code
        // std::cout << "\n";
    }

    std::cout << total << "\n";
}