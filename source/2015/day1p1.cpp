#include "core.h"

int main() {
    std::string input = AOC::readfile("input.txt");

    int floor = 0;
    for (size_t i = 0; i < input.size(); i++) {
        if (input[i] == '(')
            floor++;
        else
            floor--;
    }

    std::cout << floor << "\n";
}