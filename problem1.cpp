#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "util.h"


std::string parseNextDigitWord(const std::string::const_iterator& i, const std::string::const_iterator& end) {
    std::string query;

    auto length = std::distance(i, end);

    if (length <= 2)
        return "";

    query = std::string(i, i + 3);
    if (query == "one" || query == "two" || query == "six")
        return query;

    if (length <= 3)
        return "";

    query = std::string(i, i + 4);
    if (query == "four" || query == "five" || query == "nine")
        return query;

    if (length <= 4)
        return "";

    query = std::string(i, i + 5);
    if (query == "three" || query == "seven" || query == "eight")
        return query;

    return "";
}

int wordtoi(const std::string& word) {
    if (word == "one")
        return 1;
    else if (word == "two")
        return 2;
    else if (word == "three")
        return 3;
    else if (word == "four")
        return 4;
    else if (word == "five")
        return 5;
    else if (word == "six")
        return 6;
    else if (word == "seven")
        return 7;
    else if (word == "eight")
        return 8;
    else if (word == "nine")
        return 9;
    else
        return -1;
}

std::vector<int> parseDigits(const std::string& line) {
    std::vector<int> digits;

    for (auto c = line.begin(); c != line.end(); ++c)
    {
        if (isdigit(*c))
        {
            digits.push_back(ctoi(*c));
            continue;
        }

        std::string word = parseNextDigitWord(c, line.end());
        if (word.empty())
            continue;

        digits.push_back(wordtoi(word));
    }

    return digits;
}

int main() {

    int calibrationNo;

    std::vector<std::string> lines;
    readFile("input/1.txt", lines);

    int sum = 0;
    for (const std::string& line : lines)
    {
        std::vector<int> digits = parseDigits(line);
        calibrationNo = 10 * digits.front() + digits.back();
        sum += calibrationNo;
        std::printf("%s: %d\n", line.c_str(), calibrationNo);
    }

    std::cout << "Total sum: " << sum << "\n";

    return 0;
}