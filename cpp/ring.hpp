#pragma once
#include <vector>
#include <cmath>
#include "point.hpp"

class Ring{
    public:
    std::vector<std::vector<Point> >points;
    Ring (int max_r = 0) {
        points = std::vector<std::vector<Point> >(max_r + 1, std::vector<Point>());
        for (int y = - max_r; y <= max_r; y++) {
            for (int x = - max_r; x <= max_r; x++) {
                int r = std::floor(std::hypot(x, y));
                if (r > max_r)continue;
                points[r].push_back(Point(x, y));
            }
        }
    }
};
