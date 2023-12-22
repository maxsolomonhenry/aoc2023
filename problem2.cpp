#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "util.h"

int computePower(const std::vector<std::string>& handfuls) {

    int numCubes;

    std::map<std::string, int> minCubesMap = {
        {"red", 0}, {"green", 0}, {"blue", 0}
    };

    for (const std::string& handful : handfuls)
    {
        std::vector<std::string> cubes = parseByDelimiter(handful, ',');
        for (const std::string& cube: cubes)
        {
            std::vector<std::string> cubeInfo = parseByDelimiter(cube, ' ');
            numCubes = std::stoi(cubeInfo[0]);

            std::string& color = cubeInfo[1];

            if (numCubes > minCubesMap[color])
                minCubesMap[color] = numCubes;
        }
    }

    int power = 1;
    for (auto& pair: minCubesMap)
        power *= pair.second;

    return power;
}

int main() {

    std::vector<std::string> lines;
    readFile("input/2.txt", lines);

    int sum = 0;
    
    for (std::string line : lines)
    {
        std::vector<std::string> info = parseByDelimiter(line, ':');
        std::vector<std::string> handfuls = parseByDelimiter(info[1], ';');
        sum += computePower(handfuls);
    }

    std::printf("Total sum: %d\n", sum);

    return 0;
}