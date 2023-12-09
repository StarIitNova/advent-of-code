#include "core.h"

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");

    int maxRed = 12, maxGreen = 13, maxBlue = 14;
    int sum = 0;
    for (const auto &input : inputs) {
        size_t f = input.find_first_of(':') + 2;
        size_t start = input.find_first_of("0123456789");
        int gameID = std::stoi(input.substr(start, f - 2 - start));
        bool gameFailed = false;
        while (f != std::string::npos) {
            std::vector<std::string> cont;
            std::string x;
            std::istringstream ss(input.substr(f, input.find_first_of(';', f) - f));
            while (std::getline(ss, x, ','))
                cont.push_back(x.substr(0, x.find_first_of(';')));

            int red = 0, green = 0, blue = 0;
            for (const auto str : cont) {
                if (str.find_first_of("0123456789") != std::string::npos) {
                    std::string val = str.substr(str.find_first_of("0123456789"), str.find_first_of(' ', 1));
                    if (str.find("red") != std::string::npos)
                        red += std::stoi(val);
                    else if (str.find("green") != std::string::npos)
                        green += std::stoi(val);
                    else
                        blue += std::stoi(val);
                }
            }

            if (red > maxRed || green > maxGreen || blue > maxBlue) {
                gameFailed = true;
                break;
            }

            f = input.find_first_of(';', f + 1);
            if (f == std::string::npos)
                break;
            f++;
        }

        if (!gameFailed) {
            sum += gameID;
        }
    }

    std::cout << sum << "\n";
}