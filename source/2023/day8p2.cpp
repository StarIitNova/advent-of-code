#include "core.h"

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");
    std::string steps = inputs[0];
    inputs.erase(inputs.begin(), inputs.begin() + 1);

    std::map<std::string, std::vector<std::string>> nw{};

    for (const auto &line : inputs) {
        auto linfo = AOC::split(line, " = ");
        auto pos = linfo[0], match = linfo[1];
        nw[pos] = AOC::split(match.substr(1, match.size() - 2), ", ");
    }

    std::vector<std::string> positions{};
    for (const auto &[key, _] : nw)
        if (key.back() == 'A')
            positions.push_back(key);

    std::vector<std::vector<size_t>> cycles{};

    for (auto &current : positions) {
        std::vector<size_t> cycle{};

        std::string currSteps = steps;
        size_t stepCount = 0;
        std::string firstZ = "";

        while (true) {
            while (stepCount == 0 || current.back() != 'Z') {
                stepCount++;
                current = nw[current][currSteps[0] == 'L' ? 0 : 1];
                currSteps = currSteps.substr(1) + currSteps.substr(0, 1);
            }

            cycle.push_back(stepCount);

            if (firstZ.empty()) {
                firstZ = current;
                stepCount = 0;
            } else {
                break;
            }
        }

        cycles.push_back(cycle);
    }

    std::vector<size_t> nums = AOC::map<size_t, std::vector<size_t>>([](std::vector<size_t> cycle) -> size_t { return cycle[0]; }, cycles);
    size_t lcm = AOC::pop(nums);

    for (const auto &num : nums) {
        int gcd = std::gcd((int)lcm, (int)num);
        lcm *= (int)num / gcd;
    }

    printf("%d\n", lcm);
}