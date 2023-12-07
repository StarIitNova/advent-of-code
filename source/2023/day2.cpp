#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::string input;

    int maxRed = 12, maxGreen = 13, maxBlue = 14;
    int sum = 0;
    while (std::getline(std::cin, input)) {
        size_t f = input.find_first_of(':') + 2;
        size_t start = input.find_first_of("0123456789");
        int gameID = std::stoi(input.substr(start, f - 2 - start));
        // bool gameFailed = false; // for part 1

        int highRed = 0, highGreen = 0, highBlue = 0; // part 2
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

            // part 2
            if (red > highRed)
                highRed = red;
            if (green > highGreen)
                highGreen = green;
            if (blue > highBlue)
                highBlue = blue;

            // following is for part 1
            // if (red > maxRed || green > maxGreen || blue > maxBlue) {
            //     gameFailed = true;
            //     break;
            // }

            f = input.find_first_of(';', f + 1);
            if (f == std::string::npos)
                break;
            f++;
        }

        // part 2
        sum += highRed * highGreen * highBlue;

        // following is for part 1
        // if (!gameFailed) {
        //     sum += gameID;
        // }
    }

    std::cout << sum << "\n";
}