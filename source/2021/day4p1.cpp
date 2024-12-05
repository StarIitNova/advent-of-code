#include "newcore.h"

int main() {
    aoc::vector<aoc::string> lines = aoc::vector<aoc::string>::from(aoc::split(aoc::read_file("input.txt"), "\n", false));
    aoc::vector<int> calls = aoc::map(_aoc_strtoi, lines[0].split(","));
    aoc::vector<aoc::vector<int>> boards;

    int i = 1;
    while (i < lines.size()) {
        if (lines[i].size() <3) i++;
        aoc::vector<int> board;
        while (i < lines.size() && lines[i].size() >= 3) {
            aoc::vector<int> vals = aoc::map(_aoc_strtoi, lines[i].split());
            board.insert(board.end(), vals.begin(), vals.end());
            i++;
        }
        if (board.size())
            boards.push_back(board);
    }

    aoc::vector<int> scalls;
    for (const auto &call : calls) {
        scalls.push_back(call);

        for (const auto &board : boards) {
            bool wins = false;
            for (int y = 0; y < 5; y++) {
                bool s = true;
                for (int x = 0; x < 5; x++)
                    if (!scalls.has(board[y * 5 + x])) s = false;
                wins |= s;
            }

            for (int x = 0; x < 5; x++) {
                bool s = true;
                for (int y = 0; y < 5; y++)
                    if (!scalls.has(board[y * 5 + x])) s = false;
                wins |= s;
            }

            for (int xx = 0; xx < 5; xx++) {
                bool sa = false, sb = false;
                if (!scalls.has(board[xx * 5 + xx])) sa = false;
                if (!scalls.has(board[(5 - xx) * 5 + xx])) sb = false;
                wins |= sa | sb;
            }

            if (wins) {
                int c = 0;
                for (int i = 0; i < 25; i++)
                    if (!scalls.has(board[i])) c += board[i];
                std::cout << c * call << "\n";
                return 0;
            }
        }
    }

    return 0;
}

