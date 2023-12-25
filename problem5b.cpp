#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include "util.h"

std::vector<std::pair<long, long>> parseSeedInfo (std::string line) {

    auto info = parseByDelimiter(line, ' ');

    std::vector<std::pair<long, long>> seedInfo;

    for (int i = 1; i < info.size(); i += 2)
    {
        std::pair<long, long> seed(
            std::stol(info[i]), 
            std::stol(info[i + 1])
        );

        seedInfo.push_back(seed);
    }

    return seedInfo;
}

bool inRange(long seed, const std::vector<std::pair<long, long>>& seedInfo)
{
    for (auto pair : seedInfo)
    {
        if ((seed >= pair.first) && (seed < pair.first + pair.second))
            return true;
    }
    return false;
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

long location2seed(long location, std::vector<std::map<long, long>> maps) {

    long query = location;
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

    auto seedInfo = parseSeedInfo(lines[0]);

    // Reverse it.
    std::vector<std::map<long, long>> backwardsMaps;
    for (auto it = maps.rbegin(); it != maps.rend(); ++it)
    {
        std::map<long, long> reversed;
        for (auto pair : *it)
        {
            long key = pair.first + pair.second;
            long value = -pair.second;
            reversed[key] = value;
        }

        backwardsMaps.push_back(reversed);
    }

    long i = 0;
    int seed;
    while (true)
    {
        seed = location2seed(i++, backwardsMaps);
        std::cout << seed << "\n";

        if (inRange(seed, seedInfo))
            break;
    }

    std::cout << "Lowest seed: " << seed << "\n";

    return 0;
}