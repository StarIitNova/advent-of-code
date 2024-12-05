#include "newcore.h"

int main() {
    aoc::vector<aoc::string> lines = aoc::vector<aoc::string>::from(aoc::split(aoc::read_file("input.txt"), "\n"));

    auto proc = [](aoc::vector<aoc::string> vec, bool iso2 = false) -> aoc::string {
        int idx = 0;
        while (vec.size() > 1) {
            aoc::vector<aoc::string> nvec, rot = aoc::rotate(vec);
            int ones = std::count(rot[idx].begin(), rot[idx].end(), '1'), zeros = std::count(rot[idx].begin(), rot[idx].end(), '0');
            for (int i = 0; i < vec.size(); i++)
                if ((vec[i][idx] == '1' && ((iso2 && ones >= zeros) | (!iso2 && ones < zeros))) | (vec[i][idx] == '0' && ((iso2 && zeros > ones) | (!iso2 && zeros <= ones))))
                    nvec.push_back(vec[i]);
            vec = nvec;
            idx++;
        }

        return vec[0];
    };

    aoc::string o2s = proc(lines, true), co2s = proc(lines);
    std::cout << std::strtoull(o2s.c_str(), nullptr, 2) * std::strtoull(co2s.c_str(), nullptr, 2) << "\n";

    return 0;
}

