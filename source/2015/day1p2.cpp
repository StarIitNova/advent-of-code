#include "core.h"

int main() {
    std::string input = AOC::readfile("input.txt");

    int i = 0, floor = 0;
    for (i = 0; i < input.size(); i++) {
        if (input[i] == '(')
            floor++;
        else
            floor--;
        if (floor == -1)
            break;
    }

    std::cout << i + 1 << "\n";
}