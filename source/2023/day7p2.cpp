#include "core.h"

struct Hand {
    std::string deck;
    size_t bid = 0;
    unsigned short worth;
};

// change J to 11 for part 1
std::map<char, int> cardWorth{{'T', 10}, {'J', 1}, {'Q', 12}, {'K', 13}, {'A', 14}};

unsigned short getCharWorth(char c) {
    if (cardWorth.count(c))
        return cardWorth[c];
    return (unsigned short)(c - '0');
}

unsigned short getWorth(std::string hand) {
    std::map<char, int> counts;
    for (size_t i = 0; i < hand.size(); i++) {
        if (!counts.count(hand[i]))
            counts[hand[i]] = 0;
        counts[hand[i]]++;
    }

    if (!counts.count('J'))
        counts['J'] = 0;

    bool hasThree = false;
    unsigned short twoGroups = 0;
    for (const auto &[card, count] : counts) {
        if (count == 5)
            return 7;
        else if (count == 4) {
            if (counts['J'] == 1)
                return 7;
            return 6;
        } else if (count == 3) {
            if (counts['J'] == 2)
                return 7;
            else if (counts['J'] == 1)
                return 6;
            hasThree = true;
        } else if (count == 2) {
            if (card != 'J' && counts['J'] == 3)
                return 7;
            else if (card != 'J' && counts['J'] == 2)
                return 6;
            else if (card != 'J' && counts['J'] == 1) {
                hasThree = true;
                continue;
            }
            twoGroups++;
        }
    }

    return (hasThree ? 3 : 0) + twoGroups + 1;
}

int main() {
    auto input = AOC::split(AOC::readfile("input.txt"), "\n");

    std::vector<Hand> hands{};

    for (const auto &hand : input) {
        auto handInfo = AOC::split(hand);
        Hand nhand{handInfo[0], (size_t)std::stoll(handInfo[1])};
        nhand.worth = getWorth(handInfo[0]);
        hands.push_back(nhand);
    }

    auto sortFn = [](Hand a, Hand b) -> bool {
        if (a.worth != b.worth)
            return a.worth <= b.worth;

        for (size_t i = 0; i < a.deck.size(); i++)
            if (a.deck[i] != b.deck[i])
                return getCharWorth(a.deck[i]) <= getCharWorth(b.deck[i]);

        return true;
    };

    std::sort(hands.begin(), hands.end(), sortFn);

    size_t finalEarn = 0;
    for (size_t i = 0; i < hands.size(); i++) {
        finalEarn += hands[i].bid * (i + 1);
    }

    std::cout << finalEarn << "\n";
}