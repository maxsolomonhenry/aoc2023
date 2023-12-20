#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "util.h"


struct Point {
    int x = 0;
    int y = 0;
};

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

class Schematic {
public:
    Schematic(std::vector<std::string> data) : data_(data) {}

    const char read(Point p) const {
        return data_[p.y][p.x];
    }

private:
    std::vector<std::string> data_;
};

class Grid {
public:
    Grid(int width, int height) : width_(width), height_(height) {
        position_ = {0, 0};
        hasReset_ = false;
    }

    void advance() {
        ++position_.x;

        if (position_.x >= width_)
        {
            position_.x = 0;
            ++position_.y;
        }

        if (position_.y >= height_)
        {
            position_.y = 0;
            hasReset_ = true;
        }
    }

    const bool hasReset() const {
        return hasReset_;
    }

    const Point& position() const {
        return position_;
    }

private:
    int width_;
    int height_;

    Point position_;

    bool hasReset_;
};

int main() {

    std::vector<std::string> lines;
    readFile("input/3.txt", lines);

    int nWidth = lines[0].size();
    int nHeight = lines.size();

    Grid grid(nWidth, nHeight);
    Schematic schematic(lines);

    // Look for numbers, extract.
    while (!grid.hasReset())
    {
        const Point& p = grid.position();

        std::cout << p << ": " << schematic.read(p) << "\n";
        grid.advance();
    }
    
    // See if symbol around said numbers. 

    return 0;
}