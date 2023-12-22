#include <string>
#include <vector>
#include "util.h"

std::string scanPartNumber(int& pX, const std::string& line)
{
    int xLeft = pX;
    int xRight = pX;

    while (std::isdigit(line[xLeft - 1]))
    {
        --xLeft;
    }

    while (std::isdigit(line[xRight + 1]))
    {
        ++xRight;
    }

    std::string partNumber = line.substr(xLeft, xRight - xLeft + 1);

    // Increment the pointer to the end of this number.
    pX = xRight;

    return partNumber;
}

int computeGearRatio(int x, int y, const std::vector<std::string>& lines) {

    int height = lines.size();
    int width = lines[0].size();

    // Squishy borders to prevent indexing into the howling void.
    int topY = std::max(y - 1, 0);
    int bottomY = std::min(y + 1, (height - 1));

    int leftX = std::max(x - 1, 0);
    int rightX = std::min(x + 1, (width - 1));

    int nAdjacent = 0;

    for (int pY = topY; pY <= bottomY; ++pY)
    {

        int nRowDigits = 0;
        int nRowNumbers = 0;

        for (int pX = leftX; pX <= rightX; ++ pX)
        {
            nRowDigits += std::isdigit(lines[pY][pX]) ? 1 : 0;
        }

        // If there are any digits, there is at least one number.
        if (nRowDigits > 0)
            nRowNumbers += 1;

        // If the middle char is a separator, then there are two numbers.
        if (nRowDigits == 2 && !std::isdigit(lines[pY][x]))
            nRowNumbers += 1;

        nAdjacent += nRowNumbers;

    }

    if (nAdjacent != 2)
        return 0;

    int product = 1;
    std::string partNumber;
    for (int pY = topY; pY <= bottomY; ++pY)
    {
        for (int pX = leftX; pX <= rightX; ++pX)
        {
            if(std::isdigit(lines[pY][pX]))
            {
                // Scan part number and reposition pX.
                partNumber = scanPartNumber(pX, lines[pY]);
                product *= std::stoi(partNumber);
            }
        }
    }

    return product;
}

int main () {
    std::vector<std::string> lines;
    readFile("input/3.txt", lines);

    int sum = 0;
    for (int y = 0; y < lines.size(); ++y)
        for (int x = 0; x < lines[0].size(); ++x)
            if (lines[y][x] == '*')
                sum += computeGearRatio(x, y, lines);

    std::cout << "Total sum: " << sum << "\n";
}