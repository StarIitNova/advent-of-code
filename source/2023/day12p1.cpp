#include "core.h"

size_t getCnts(std::string config, std::vector<int> nums) {
    if (config == "")
        return nums.empty() ? 1 : 0;
    if (nums.empty())
        return config.find_first_of('#') != std::string::npos ? 0 : 1;

    size_t res = 0;

    if (".?"s.find_first_of(config[0]) != std::string::npos) {
        res += getCnts(config.substr(1), nums);
    }

    if ("#?"s.find_first_of(config[0]) != std::string::npos) {
        if (nums[0] <= config.size() && config.substr(0, nums[0]).find_first_of('.') == std::string::npos && (nums[0] == config.size() || config[nums[0]] != '#')) {
            int first = nums[0];
            nums.erase(nums.begin());
            if (first >= config.size())
                return res + getCnts("", nums);
            return res + getCnts(config.substr(first + 1), nums);
        }
    }

    return res;
}

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");

    size_t total = 0;
    for (const auto &line : inputs) {
        auto lineinfo = AOC::split(line);
        std::string cfg = lineinfo[0], numstr = lineinfo[1];
        std::vector<int> nums = AOC::map<int, std::string>(_aoc_strtoi, AOC::split(numstr, ","));
        total += getCnts(cfg, nums);
    }

    std::cout << total << "\n";
}