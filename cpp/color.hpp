#pragma once
#include <iostream>
#include <cmath>

class Color{
    public:
    int r, g, b;
    
    Color(int r = 255, int g = 255, int b = 255):r(r),g(g),b(b){}

    Color operator + (const Color color){
        return Color(
            (r + color.r) / 2,
            (g + color.g) / 2,
            (b + color.b) / 2
        );
    }

    void operator += (const Color color){
        r = (r + color.r) / 2;
        g = (g + color.g) / 2;
        b = (b + color.b) / 2;
    }

    long long operator - (const Color color) {
        int r_diff = r - color.r;
        int g_diff = g - color.g;
        int b_diff = b - color.b;
        return std::abs(r_diff) + std::abs(g_diff) + std::abs(b_diff);
    }

    friend std::ostream& operator<<(std::ostream&, const Color&);
};

std::ostream& operator<<(std::ostream& stream, const Color& color){
    stream << "rgb(" << color.r << ", " << color.g << ", " << color.b << ")";
    return stream;
}