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
    std::vector<std::string> blocks = AOC::split(AOC::readfile("input"), "\n\n");
    std::string inputStr = blocks[0];
    blocks.erase(blocks.begin());

    auto strtoi = [](std::string v) -> size_t { return std::stoll(v); };

    std::vector<std::string> spl1 = AOC::split(inputStr, ":");
    std::vector<std::string> spl2 = AOC::split(spl1[1]);
    auto inputs = AOC::map<size_t, std::string>(strtoi, spl2);

    std::vector<SeedInfo> seeds;
    for (int i = 0; i < inputs.size(); i += 2)
        seeds.push_back(SeedInfo{inputs[i], inputs[i] + inputs[i + 1]});

    for (const auto &block : blocks) {
        std::vector<SeedInfo> ranges{};
        std::vector<std::string> lines = AOC::split(block, "\n");
        lines.erase(lines.begin());
        for (const auto &line : lines)
            ranges.push_back(SeedInfo(AOC::map<size_t, std::string>(strtoi, AOC::split(line))));

        std::vector<SeedInfo> newVals{};
        while (seeds.size() > 0) {
            SeedInfo sinfo = AOC::pop(seeds);
            size_t sdest = sinfo.dest, ssrc = sinfo.src;

            bool found = false;
            for (const auto &soil : ranges) {
                size_t dest = soil.dest, src = soil.src, len = soil.length;
                size_t highdest = AOC::max(sdest, src);
                size_t highsrc = AOC::min(ssrc, src + len);

                if (highdest < highsrc) {
                    newVals.push_back(SeedInfo{highdest - src + dest, highsrc - src + dest});
                    if (highdest > sdest)
                        seeds.push_back(SeedInfo{sdest, highdest});
                    else if (ssrc > highsrc)
                        seeds.push_back(SeedInfo{highsrc, ssrc});
                    found = true;
                    break;
                }
            }

            if (!found)
                newVals.push_back(SeedInfo{sdest, ssrc});
        }

        seeds = newVals;
    }

    size_t lowest = -1;
    for (const auto &seed : seeds) {
        if (seed.dest < lowest)
            lowest = seed.dest;
    }

    std::cout << lowest << "\n";
}