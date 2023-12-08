#include "core.h"

int main() {
    std::string input = AOC::readfile("input.txt");

    int x = 0, y = 0;
    std::map<std::string, int> houses{{"0,0", 1}};
    for (size_t i = 0; i < input.size(); i++) {
        if (input[i] == '>')
            x++;
        else if (input[i] == '<')
            x--;
        else if (input[i] == '^')
            y++;
        else
            y--;

        std::string v = std::to_string(x) + "," + std::to_string(y);
        if (!houses.count(v))
            houses[v] = 0;
        houses[v]++;
    }

    size_t total = 0;
    for (const auto &[house, count] : houses)
        total++;
    printf("%d\n", total);
}