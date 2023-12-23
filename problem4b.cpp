#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include "util.h"


class CardCounter {
public:
    CardCounter () {};

    void parse(std::string line) {
        std::vector<std::string> buffer;
        std::vector<std::string> cardInfo;
        std::vector<std::string> winningNosAsString;
        std::vector<std::string> myNosAsString;
        std::vector<std::string> allNosAsString;
        int cardNo;

        buffer = parseByDelimiter(line, ':');
        cardInfo = parseByDelimiter(buffer[0], ' ');
        allNosAsString = parseByDelimiter(buffer[1], '|');
        winningNosAsString = parseByDelimiter(allNosAsString[0], ' ');
        myNosAsString = parseByDelimiter(allNosAsString[1], ' ');

        cardNo = std::stoi(cardInfo[1]);
        std::cout << cardNo << "\n";

        std::vector<int> winningNos;
        std::vector<int> myNos;

        std::transform(winningNosAsString.begin(), winningNosAsString.end(), 
            std::back_inserter(winningNos), [](std::string s) { return std::stoi(s); });

        std::transform(myNosAsString.begin(), myNosAsString.end(), 
            std::back_inserter(myNos), [](std::string s) { return std::stoi(s); });

        std::sort(winningNos.begin(), winningNos.end());
        std::sort(myNos.begin(), myNos.end());

        std::vector<int> intersection;

        std::set_intersection(
            winningNos.begin(), winningNos.end(),
            myNos.begin(), myNos.end(),
            std::back_inserter(intersection));

        int nMatches = intersection.size();

        for (int i = 1; i <= nMatches; ++i)
        {
            int idx = (cardNo + 1) + i;
            nCopies_[idx] += nCopies_[cardNo]; 
        }
    }

    int total() {
        int sum = 0;
        for (int n : nCopies_)
            sum += n;
        return sum;
    }

private:
    std::vector<int> nCopies_;
};

int main() {

    std::vector<std::string> lines;
    readFile("input/4.txt", lines);

    CardCounter counter;

    for (std::string line : lines) 
        counter.parse(line);

    // std::cout << "Total sum: " << counter.total() << "\n";

    return 0;
} 