#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "util.h"


bool isSymbol(const char& c) {

    if (std::isdigit(c))
        return false;
    
    if (c == '.')
        return false;

    if (c == '\0')
        return false;

    return true;

}

bool hasAdjacentSymbol(std::string value, int x, int y, std::vector<std::string> lines) {

    int pX;
    int pY;
    int right;

    if (x == 0)
    {
        // If it is first item on next line.
        pX = lines[0].size() - (value.size() + 1);
        pY = y - 2;
        right = value.size();
    } else if (x == value.size()){
        // Up against the leftmost edge.
        pX = x - value.size();
        pY = y - 1;
        right = value.size();
    } else {
        pX = x - (value.size() + 1);
        pY = y - 1;
        right = value.size() + 1;
    }

    // Check top row.
    if (pY >= 0)
    {
        for (int i = 0; i <= right; ++i)
        {
            if (isSymbol(lines[pY][pX + i]))
                return true;
        }
    }

    // Check middle row.
    if (isSymbol(lines[pY + 1][pX]))
        return true;

    if (isSymbol(lines[pY + 1][pX + right]))
        return true;
    
    // Check bottom row.
    if (pY <= lines.size())
    {
        for (int i = 0; i <= right; ++i)
        {
            if (isSymbol(lines[pY + 2][pX + i]))
                return true;
        }
    }

    return false;
}

int main() {

    std::vector<std::string> lines;

    readFile("input/3.txt", lines);

    int height = lines.size();
    int width = lines[0].size();
    int sum = 0;

    std::string value;
    for (int y = 0; y <= height; ++y)
    {
        for (int x = 0; x <= width; ++x)
        {
            char& c = lines[y][x];
            if (!std::isdigit(c))
            {
                if (!value.empty())
                {
                    if (hasAdjacentSymbol(value, x, y, lines))
                    {
                        sum += std::stoi(value);
                    }

                    value.clear();
                }
                continue;
            }
            value.push_back(c);
        }
    }

    std::cout << "Total sum: " << sum << "\n";

    return 0;
}