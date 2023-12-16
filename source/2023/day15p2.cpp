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

    std::vector<std::vector<std::string>> boxes{};
    for (size_t i = 0; i < 256; i++)
        boxes.push_back({});

    std::map<std::string, size_t> focalLengths{};

    for (const auto &instruction : inputs) {
        if (instruction.find('-') != std::string::npos) {
            std::string label = instruction.substr(0, instruction.size() - 1);
            size_t index = hash(label);
            if (AOC::in(boxes[index], label))
                boxes[index].erase(boxes[index].begin() + AOC::inPos(boxes[index], label));
        } else {
            auto info = AOC::split(instruction, "=");
            std::string label = info[0];
            size_t len = std::stoll(info[1]);

            size_t index = hash(label);
            if (!AOC::in(boxes[index], label))
                boxes[index].push_back(label);

            focalLengths[label] = len;
        }
    }

    size_t total = 0;
    for (size_t i = 0; i < boxes.size(); i++)
        for (size_t l = 0; l < boxes[i].size(); l++)
            total += (i + 1) * (l + 1) * focalLengths[boxes[i][l]];

    std::cout << total << "\n";
}