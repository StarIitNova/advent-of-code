#include "core.h"

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");
    std::string steps = inputs[0];
    inputs.erase(inputs.begin(), inputs.begin() + 1);

    size_t totalSteps = 0;
    std::string current = "AAA";
    std::map<std::string, std::vector<std::string>> nw{};

    for (const auto &line : inputs) {
        auto linfo = AOC::split(line, " = ");
        auto pos = linfo[0], match = linfo[1];
        nw[pos] = AOC::split(match.substr(1, match.size() - 2), ", ");
    }

    while (current != "ZZZ") {
        totalSteps++;
        current = nw[current][steps[0] == 'L' ? 0 : 1];
        steps = steps.substr(1) + steps.substr(0, 1);
    }

    printf("%d\n", totalSteps);
}