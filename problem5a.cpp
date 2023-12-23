#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
#include "util.h"

std::vector<long> parseSeeds (std::string line) {
    std::vector<std::string> info;

    info = parseByDelimiter(line, ' ');

    std::vector<long> seeds;
    for (int i = 1; i < info.size(); ++i)
        seeds.push_back(std::stol(info[i]));

    return seeds;
}

long seed2location(long seed) {
    return 0;
}

int main() {
    std::vector<std::string> lines;
    readFile("input/5.txt", lines);

    std::vector<std::unordered_map<int, int>> maps;
    std::vector<long> seeds = parseSeeds(lines[0]);

    std::unordered_map<int, int> map;

    for (int i = 2; i < lines.size(); ++i) {
        map[0] = 0;

        // Ignore "X-to-Y map:" lines...
        if (!std::isdigit(lines[i][0]))
            continue;

        // Get "key" as lower range of source, and "value" as offset to dest.
        std::vector<std::string> info = parseByDelimiter(lines[i], ' ');

        long destination = std::stol(info[0]);
        long source = std::stol(info[1]);
        long range = std::stol(info[2]);

        long offset = destination - source;

        // Determine start offset.
        map[source] = offset;

        // Set the offset to 0 above the specified range.
        map[source + range] = 0;
        
        if (lines[i].empty())
        {
            maps.push_back(map);
            map.clear();
        }

    }

    // Push back last map (TODO: better way to do this?).
    maps.push_back(map);

    std::vector<long> locations;
    for (long seed : seeds)
        locations.push_back(seed2location(seed));

    long min = *std::min_element(locations.begin(), locations.end());

    std::cout << "Min value: " << min << "\n";
    return 0;
}