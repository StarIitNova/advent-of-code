// I need to redo this script, it worked once but I can't seem to get it to work again

#include "core.h"

std::map<std::string, size_t> cache{};

std::string keyFromState(std::string config, std::vector<size_t> nums) {
    std::string key = config + ":";
    for (const auto &num : nums)
        key += std::to_string(num) + ",";
    return key;
}

size_t getCnts(std::string config, std::vector<size_t> nums) {
    if (config == "")
        return nums.empty() ? 1 : 0;
    if (nums.empty())
        return config.find_first_of('#') != std::string::npos ? 0 : 1;

    std::string key = keyFromState(config, nums);
    if (cache.count(key))
        return cache[key];

    size_t res = 0;

    if (".?"s.find_first_of(config[0]) != std::string::npos) {
        res += getCnts(config.substr(1), nums);
    }

    if ("#?"s.find_first_of(config[0]) != std::string::npos) {
        if (nums[0] <= config.size() && config.substr(0, nums[0]).find_first_of('.') == std::string::npos && (nums[0] == config.size() || config[nums[0]] != '#')) {
            size_t first = nums[0];
            nums.erase(nums.begin());
            if (first >= config.size())
                res += getCnts("", nums);
            else
                res += getCnts(config.substr(first + 1), nums);
        }
    }

    cache[key] = res;
    return res;
}

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");

    size_t total = 0;
    for (const auto &line : inputs) {
        auto lineinfo = AOC::split(line);
        std::string cfg = lineinfo[0], numstr = lineinfo[1];
        std::vector<size_t> nums = AOC::map<size_t, std::string>(_aoc_strtoull, AOC::split(numstr, ","));

        cfg = AOC::rep(cfg, 5, "?");
        size_t cnt = nums.size();
        for (size_t _ = 0; _ < 5; _++) {
            for (size_t i = 0; i < cnt; i++) {
                nums.push_back(nums[i]);
            }
        }

        total += getCnts(cfg, nums);
    }

    std::cout << total << "\n";
}