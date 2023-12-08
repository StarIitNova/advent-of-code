#include "core.h"

int main() {
    std::string input = AOC::readfile("input.txt");

    int x = 0, y = 0, x2 = 0, y2 = 0;
    std::map<std::string, int> houses{{"0,0", 1}};
    for (size_t i = 0; i < input.size(); i++) {
        if (i % 2 == 1) {
            if (input[i] == '>')
                x++;
            else if (input[i] == '<')
                x--;
            else if (input[i] == '^')
                y++;
            else
                y--;
        } else {
            if (input[i] == '>')
                x2++;
            else if (input[i] == '<')
                x2--;
            else if (input[i] == '^')
                y2++;
            else
                y2--;
        }

        std::string v = std::to_string(x) + "," + std::to_string(y);
        std::string v2 = std::to_string(x2) + "," + std::to_string(y2);
        if (!houses.count(v))
            houses[v] = 0;
        houses[v]++;

        if (!houses.count(v2))
            houses[v2] = 0;
        houses[v2]++;
    }

    size_t total = 0;
    for (const auto &[house, count] : houses)
        total++;
    printf("%d\n", total);
}