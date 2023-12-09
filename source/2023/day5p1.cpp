#include "core.h"

struct SeedInfo {
    size_t dest = 0;
    size_t src = 0;
    size_t length = 0;

    SeedInfo(size_t _dest, size_t _src) : dest(_dest), src(_src) {}
    SeedInfo(std::vector<size_t> mapped) {
        dest = mapped[0];
        src = mapped[1];
        length = mapped[2];
    }
};

int main() {
    std::vector<std::string> blocks = AOC::split(AOC::readfile("input.txt"), "\n\n");
    std::string inputStr = blocks[0];
    blocks.erase(blocks.begin());

    std::vector<size_t> seeds = AOC::map<size_t, std::string>(_aoc_strtoull, AOC::split(AOC::split(inputStr, ":")[1]));

    for (const auto &block : blocks) {
        std::vector<SeedInfo> ranges{};
        std::vector<std::string> lines = AOC::split(block, "\n");
        lines.erase(lines.begin());
        for (const auto &line : lines)
            ranges.push_back(SeedInfo(AOC::map<size_t, std::string>(_aoc_strtoull, AOC::split(line))));

        std::vector<size_t> newVals{};
        for (const auto &seed : seeds) {
            bool escape = false;
            for (const auto &soil : ranges) {
                size_t dest = soil.dest, src = soil.src, len = soil.length;

                if (src <= seed && seed < src + len) {
                    newVals.push_back(seed - src + dest);
                    escape = true;
                    break;
                }
            }
            if (!escape)
                newVals.push_back(seed);
        }
        seeds = newVals;
    }

    printf("%d\n", AOC::min(seeds));
}