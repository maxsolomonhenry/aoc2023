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


bool boundingBoxHasSymbol (std::string partNumber, int width, int height, int x, int y, std::vector<std::string> lines) {
    // Get start position of word.

    int xStart;
    int yStart;

    int xUpperLeft;
    int yUpperLeft;

    int xLowerRight;
    int yLowerRight;

    int nDigits = partNumber.size();

    if (x != 0)
    {
        xStart = x - nDigits;
        yStart = y;
    } else {
        xStart = width - nDigits;
        yStart = y - 1;
    }

    // Determine squishy bounding box.
    xUpperLeft = std::max(xStart - 1, 0);
    yUpperLeft = std::max(yStart - 1, 0);

    xLowerRight = std::min(xStart + nDigits, (width - 1));
    yLowerRight = std::min(yStart + 1, (height - 1));

    // Check for symbols.
    for (int i = yUpperLeft; i <= yLowerRight; ++i)
    {
        for (int j = xUpperLeft; j <= xLowerRight; ++j)
        {
            if (isSymbol(lines[i][j]))
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

    std::string partNumber;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            char& c = lines[y][x];
            if (!std::isdigit(c))
            {
                if (!partNumber.empty())
                {
                    
                    if (boundingBoxHasSymbol (partNumber, width, height, x, y, lines))
                    {
                        sum += std::stoi(partNumber);
                    }

                    partNumber.clear();
                }
                continue;
            }
            partNumber.push_back(c);
        }
    }

    std::cout << "Total sum: " << sum << "\n";

    return 0;
}