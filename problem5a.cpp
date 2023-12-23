#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include "util.h"

std::vector<long> parseSeeds (std::string line) {

    auto info = parseByDelimiter(line, ' ');

    std::vector<long> seeds;
    for (int i = 1; i < info.size(); ++i)
        seeds.push_back(std::stol(info[i]));

    return seeds;
}

long findClosestLowerKey(const std::map<long, long>& map, long query) {
    
    long key = -1;
    for (const auto& pair : map)
    {
        if (pair.first > query)
            return key;

        key = pair.first;
    }

    return key;
}

long seed2location(long seed, std::vector<std::map<long, long>> maps) {

    long query = seed;
    for (auto& map : maps)
    {
        long key = findClosestLowerKey(map, query);
        long offset = map[key];
        query += offset;
    }

    return query;
}

int main() {
    std::vector<std::string> lines;
    readFile("input/5.txt", lines);

    std::vector<std::map<long, long>> maps;
    std::vector<long> seeds = parseSeeds(lines[0]);

    std::map<long, long> map;
    map[0] = 0;

    for (int i = 2; i < lines.size(); ++i) 
    {
        if (lines[i].empty())
        {
            maps.push_back(map);
            map.clear();
            map[0] = 0;
        }

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
        if (map.find(source + range) == map.end())
            map[source + range] = 0;

    }

    // Push back last map.
    maps.push_back(map);

    std::vector<long> locations;
    for (long seed : seeds)
        locations.push_back(seed2location(seed, maps));

    long min = *std::min_element(locations.begin(), locations.end());

    std::cout << "Min value: " << min << "\n";
    return 0;
}