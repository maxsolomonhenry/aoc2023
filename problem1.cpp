#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "util.h"

int main() {
    std::vector<std::string> lines;
    readFile("input/1.txt", lines);

    int sum = 0;

    for (const std::string& line : lines)
    {
        int firstDigit = -1;
        int lastDigit = -1;

        for (auto it = line.begin(); it != line.end(); it++)
        {
            if (std::isdigit(*it))
            {
                firstDigit = ctoi(*it);
                break;
            }
        }

        for (auto it = line.rbegin(); it != line.rend(); it++)
        {
            if (std::isdigit(*it))
            {
                lastDigit = ctoi(*it);
                break;
            }
        }

        assert((firstDigit >= 0) && (lastDigit >= 0));

        sum += 10 * firstDigit + lastDigit;
    }

    std::cout << "Total sum: " << sum << "\n";

    return 0;
}