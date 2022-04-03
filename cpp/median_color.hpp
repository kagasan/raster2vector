#pragma once
#include "color.hpp"
#include "median.hpp"

class MedianColor{
    public:
    Median r_med, g_med, b_med;
    void push(int r, int g, int b) {
        r_med.push(r);
        g_med.push(g);
        b_med.push(b);
    }
    Color get() {
        return Color(r_med.get(), g_med.get(), b_med.get());
    }
};
