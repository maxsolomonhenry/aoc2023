#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include "util.h"

int computePoints(std::string line) {
    std::vector<std::string> buffer;
    std::vector<std::string> winningNumbers;
    std::vector<std::string> myNumbers;

    buffer = parseByDelimiter(line, ':');
    buffer = parseByDelimiter(buffer[1], '|');

    winningNumbers = parseByDelimiter(buffer[0], ' ');
    myNumbers = parseByDelimiter(buffer[1], ' ');

    std::vector<int> winningIntegers;
    std::vector<int> myIntegers;

    std::transform(winningNumbers.begin(), winningNumbers.end(), 
        std::back_inserter(winningIntegers), [](std::string s) { return std::stoi(s); });

    std::transform(myNumbers.begin(), myNumbers.end(), 
        std::back_inserter(myIntegers), [](std::string s) { return std::stoi(s); });

    std::sort(winningIntegers.begin(), winningIntegers.end());
    std::sort(myIntegers.begin(), myIntegers.end());

    std::vector<int> intersection;

    std::set_intersection(
        winningIntegers.begin(), winningIntegers.end(),
        myIntegers.begin(), myIntegers.end(),
        std::back_inserter(intersection));

    int points = 0;
    if (!intersection.empty())
        points = std::pow(2, (intersection.size() - 1));
    
    return points;
}

int main() {

    std::vector<std::string> lines;
    readFile("input/4.txt", lines);

    int sum = 0;
    for (std::string line : lines) 
    {
        sum += computePoints(line);
    }

    std::cout << "Total sum: " << sum << "\n";

    return 0;
} 