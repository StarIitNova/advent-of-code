#include "core.h"

int main() {
    std::vector<std::string> inputs = AOC::split(AOC::readfile("input.txt"), "\n");
    std::map<std::string, unsigned short> circuit{};

    std::vector<size_t> used{};

    static const auto doublet = [&](std::vector<std::string> gets, size_t idx) -> std::vector<unsigned short> {
        unsigned short v0 = 0, v1 = 0;
        if (gets[0].find_first_not_of("0123456789") != std::string::npos && !circuit.count(gets[0]))
            return {0, 0, 0};
        if (gets[1].find_first_not_of("0123456789") != std::string::npos && !circuit.count(gets[1]))
            return {0, 0, 0};

        if (circuit.count(gets[0]))
            v0 = circuit[gets[0]];
        else
            v0 = std::stoi(gets[0]);
        if (circuit.count(gets[1]))
            v1 = circuit[gets[1]];
        else
            v1 = std::stoi(gets[1]);
        used.push_back(idx);
        return {v0, v1, 1};
    };

    unsigned short oldA = 1;
    while (true) {
        used.clear();
        size_t changes = 0;

        static const auto updateCirc = [&](std::string idx, unsigned short val) {
            if (!circuit.count(idx) || circuit[idx] != val) {
                changes++;
                circuit[idx] = val;
            }
        };

        for (size_t i = 0; i < inputs.size(); i++) {
            std::string line = inputs[i];
            std::vector<std::string> info = AOC::split(line, " -> ");

            if (info[0].find("AND") != std::string::npos) {
                std::vector<std::string> x = AOC::split(info[0], " AND ");
                std::vector<unsigned short> vals = doublet(x, i);
                if (vals[2] == 1)
                    updateCirc(info[1], vals[0] & vals[1]);
            } else if (info[0].find("OR") != std::string::npos) {
                std::vector<std::string> x = AOC::split(info[0], " OR ");
                std::vector<unsigned short> vals = doublet(x, i);
                if (vals[2] == 1)
                    updateCirc(info[1], vals[0] | vals[1]);
            } else if (info[0].find("LSHIFT") != std::string::npos) {
                std::vector<std::string> x = AOC::split(info[0], " LSHIFT ");
                std::vector<unsigned short> vals = doublet(x, i);
                if (vals[2] == 1)
                    updateCirc(info[1], vals[0] << vals[1]);
            } else if (info[0].find("RSHIFT") != std::string::npos) {
                std::vector<std::string> x = AOC::split(info[0], " RSHIFT ");
                std::vector<unsigned short> vals = doublet(x, i);
                if (vals[2] == 1)
                    updateCirc(info[1], vals[0] >> vals[1]);
            } else if (info[0].find("NOT") != std::string::npos) {
                std::string id = AOC::split(info[0], " ")[1];
                if (circuit.count(id)) {
                    updateCirc(info[1], ~circuit[id]);
                    used.push_back(i);
                }
            } else {
                if (info[0].find_first_not_of("0123456789") != std::string::npos)
                    updateCirc(info[1], circuit[info[0]]);
                else
                    updateCirc(info[1], std::stoi(info[0]));
                used.push_back(i);
            }
        }

        if (changes == 0)
            break;
    }

    std::cout << circuit["a"] << "\n";
}