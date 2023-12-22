#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

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

bool readFile(const std::string& fpath, std::vector<std::string>& lines)
{
    std::ifstream in{fpath};

    if (!in) {
        std::cerr << "Cannot open file " << fpath << std::endl;
        return false;
    }


    std::string str;
    while (std::getline(in, str)) {
        lines.push_back(str);
    }

    return true;
}

int ctoi(const char& c)
{
    return c - '0';
}

int sign(int x)
{
    return (x > 0) - (x < 0);
}