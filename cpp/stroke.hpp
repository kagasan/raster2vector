#pragma once
#include <deque>
#include <vector>
#include <set>
#include "point.hpp"
#include "color.hpp"
#include "size.hpp"

class Stroke{
    public:
    std::deque<Point>path;
    int r;
    Color color;
    Size size;
    std::set<Point>point_set;
    long long score;
    
    Stroke(int r, Color color, Size size, std::deque<Point> points = std::deque<Point>(0), long long score = 0)
    :r(r), color(color), size(size), score(score) {
        for (auto p: points) push_back(p);
    }

    std::vector<Point>push_front(Point point, bool dryrun = false) {
        if (dryrun) {
            if (path.size() == 0)return update_circle(point, true);
            return update_segment(point, path[0], true);
        } else {
            path.push_front(point);
            if (path.size() == 1)return update_circle(point, false);
            return update_segment(path[0], path[1], false);
        }        
    }
    std::vector<Point> push_back(Point point, bool dryrun = false) {
        if (dryrun) {
            if (path.size() == 0)return update_circle(point, true);
            return update_segment(path[path.size()-1], point, true);
        } else {
            path.push_back(point);
            if (path.size() == 1)return update_circle(point, false);
            return update_segment(path[path.size()-2], path[path.size()-1], false);
        }
    }

    friend std::ostream& operator<<(std::ostream&, const Stroke&);

    Stroke light_stroke() {
        return Stroke(r, color, size, path);
    }

    Point get_front() {
        if (path.size() == 0)return Point(0, 0);
        return path[0];
    }
    Point get_back() {
        if (path.size() == 0)return Point(0, 0);
        return path[path.size() - 1];
    }

    private:
    std::vector<Point>update_circle(Point center, bool dryrun) {
        std::vector<Point>res;
        int y_begin = std::max(0, center.y - r);
        int y_last = std::min(size.height - 1, center.y + r);
        int x_begin = std::max(0, center.x - r);
        int x_last = std::min(size.width - 1, center.x + r);
        for (int y = y_begin; y <= y_last; y++) {
            for (int x = x_begin; x <= x_last; x++) {
                Point p(x, y);
                int y_diff = y - center.y;
                int x_diff = x - center.x;
                if (y_diff * y_diff + x_diff * x_diff <= r * r && point_set.find(p) == point_set.end()) {
                    if (! dryrun) point_set.insert(p);
                    res.push_back(p);
                }
            }
        }
        return res;
    }

    std::vector<Point> update_segment(Point p1, Point p2, bool dryrun) {
        std::vector<Point>res;
        int y_begin = std::max(0, std::min(p1.y, p2.y) - r);
        int y_last = std::min(size.height - 1, std::max(p1.y, p2.y) + r);
        int x_begin = std::max(0, std::min(p1.x, p2.x) - r);
        int x_last = std::min(size.width - 1, std::max(p1.x, p2.x) + r);
        for (int y = y_begin; y <= y_last; y++) {
            for (int x = x_begin; x <= x_last; x++) {
                Point p(x, y);
                if (p.is_near_to_line_segment(p1, p2, r) && point_set.find(p) == point_set.end()) {
                    if (! dryrun) point_set.insert(p);
                    res.push_back(p);
                }
            }
        }
        return res;
    }

};

std::ostream& operator<<(std::ostream& stream, const Stroke& stroke){
    if (stroke.path.size () > 1) {
        stream << "<path ";    
        stream << "style='fill:none;stroke:" << stroke.color;
        stream << ";stroke-width:" << 2 * stroke.r;
        stream << ";opacity:0.5;stroke-linecap:round;' ";
        stream << "d='";
        for (unsigned int i = 0; i < stroke.path.size(); i++) {
            if (i == 0) stream << "M ";
            else stream << " L ";
            stream << stroke.path[i];
        }
        stream << "'";
        stream << "/>";
    } else if (stroke.path.size() == 1) {
        stream << "<circle ";
        stream << "cx='" << stroke.path[0].x << "' ";
        stream << "cy='" << stroke.path[0].y << "' ";
        stream << "r='" << stroke.r << "' ";
        stream << "style='fill: " << stroke.color << "; fill-opacity: 0.5;'";
        stream << "/>";
    }
    return stream;
}
