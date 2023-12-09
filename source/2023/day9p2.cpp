#include "core.h"

const auto numtobool = [](size_t v) -> bool { return v == 0; };
size_t expand(std::vector<size_t> nums) {
    if (AOC::all(AOC::map<bool, size_t>(numtobool, nums)))
        return 0;

    std::vector<size_t> dts{};
    for (size_t i = 0; i < nums.size() - 1; i++)
        dts.push_back(nums[i + 1] - nums[i]);
    size_t diff = expand(dts);
    return nums.front() - diff;
}

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");
    size_t total = 0;

    for (const auto &line : inputs) {
        std::vector<size_t> numbers = AOC::map<size_t, std::string>(_aoc_strtoull, AOC::split(line));
        total += expand(numbers);
    }

    printf("%d\n", total);
}