#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <tuple>
#include "util.h"


int computeNumMatches(std::string line) {
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

    int nMatches = intersection.size();

    return nMatches;
}

int main() {

    std::vector<std::string> lines;
    readFile("input/4.txt", lines);

    int nLines = lines.size();
    std::vector<int> nCopies(nLines, 1);

    for (int i = 0; i < nLines; ++i) 
    {
        int nMatches = computeNumMatches(lines[i]);

        for (int j = 1; j <= nMatches; ++j)
        {
            int idx = i + j;
            nCopies[idx] += nCopies[i];
        }
    }

    int sum = 0;
    for (int n : nCopies)
        sum += n;

    std::cout << "Total sum: " << sum << "\n";

    return 0;
} 