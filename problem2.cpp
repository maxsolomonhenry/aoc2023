#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "util.h"


std::vector<std::string> parseByDelimiter(const std::string& line, const char& d) {

    std::istringstream iss(line);
    
    std::vector<std::string> output;
    std::string element;

    while (std::getline(iss, element, d))
    {
        if (element.empty())
            continue;

        output.push_back(element);
    }

    return output;
}

int parseGameNo(std::string& game) {
    game.erase(0, game.find(' '));
    return std::stoi(game.substr(0, game.find(':')));
}

bool isValidGame(const std::vector<std::string>& handfuls, std::map<std::string, int>& limits) {

    int numCubes;

    for (std::string handful : handfuls)
    {
        std::vector<std::string> cubes = parseByDelimiter(handful, ',');
        for (std::string cube: cubes)
        {
            std::vector<std::string> cubeInfo = parseByDelimiter(cube, ' ');
            numCubes = std::stoi(cubeInfo[0]);
            if (numCubes > limits[cubeInfo[1]])
                return false;
        }
    }

    return true;
}

int main() {

    std::vector<std::string> lines;
    readFile("input/2.txt", lines);

    int gameNo;
    int sum = 0;

    std::map<std::string, int> limits = {
        {"red", 12}, {"green", 13}, {"blue", 14}
    };

    for (std::string line : lines)
    {
        std::vector<std::string> info = parseByDelimiter(line, ':');

        gameNo = parseGameNo(info[0]); 

        std::vector<std::string> handfuls = parseByDelimiter(info[1], ';');

        if (isValidGame(handfuls, limits))
            sum += gameNo;

    }

    std::printf("Total sum: %d\n", sum);

    return 0;
}