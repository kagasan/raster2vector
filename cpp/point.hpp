#pragma once
#include <iostream>

class Point{
    public:
    int x, y;
    
    Point(int x = 0, int y = 0):x(x), y(y){}
    
    Point operator + (const Point p) {
        return Point(x + p.x, y + p.y);
    }

    friend std::ostream& operator<<(std::ostream&, const Point&);

    bool is_near_to_line_segment(Point p1, Point p2, long long r) {
        // 線分p1p2との距離がr以下ならtrue
        long long a = p2.x - p1.x;
        long long b = p2.y - p1.y;
        long long a2 = a * a;
        long long b2 = b * b;
        long long r2 = a2 + b2;
        long long tt = - ( a * ( p1.x - x ) + b * ( p1.y - y ) );
        if( tt < 0 ) {
            return ((p1.x - x) * (p1.x - x) + (p1.y - y) * (p1.y - y)) <= r * r;
        }
        if( tt > r2 ) {
            return ((p2.x - x) * (p2.x - x) + (p2.y - y) * (p2.y - y)) <= r * r;
        }
        long long f1 = a * (p1.y - y) - b * (p1.x - x);
        return f1 * f1 <= r * r * r2;
    }

    bool operator < (const Point &p) const {
        if (y != p.y)return y < p.y;
        return x < p.x;
    }
};

std::ostream& operator<<(std::ostream& stream, const Point& point){
    stream << point.x << "," << point.y;
    return stream;
}