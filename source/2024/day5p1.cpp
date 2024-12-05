#include "newcore.h"

int main() {
    aoc::vector<aoc::string> lines = aoc::vector<aoc::string>::from(aoc::split(aoc::read_file("input.txt"), "\n", false));
    aoc::vector<int> rules;

    int total = 0;
    bool pages = false;
    for (const auto &line : lines) {
        if (line.size() == 0) {
            pages = true;
            continue;
        }

        if (!pages) {
            aoc::vector<int> vs = aoc::map(_aoc_strtoi, line.split("|"));
            rules.push_back(vs[0]);
            rules.push_back(vs[1]);
            continue;
        }

        aoc::vector<int> porder = aoc::map(_aoc_strtoi, line.split(","));
        bool ok = true;
        for (int i = 0; i < porder.size(); i++) {
            for (int j = 0; j < porder.size(); j++) {
                if (i == j) continue;

                for (int x = 0; x < rules.size(); x += 2) {
                    if (j < i && rules[x] == porder[i] && rules[x + 1] == porder[j]) ok = false;
                    if (i < j && rules[x] == porder[j] && rules[x + 1] == porder[i]) ok = false;
                }
            }
        }

        if (ok) total += porder[(int)(((float)porder.size() / 2.0f - 0.5f))];
    }



    std::cout << total << "\n";

    return 0;
}

