#pragma once

#include <queue>
#include <algorithm>

class Median{
    public:
    std::priority_queue<int>min_q;
    std::priority_queue<int, std::vector<int>, std::greater<int> >max_q;
    int total_count;
    Median(int default_min = -1000, int default_max = 1000){
        min_q.push(default_min);
        max_q.push(default_max);
        total_count = 0;
    }
    void push(int x){
        total_count++;
        min_q.push(x);
        if (total_count % 2 == 0) {
            max_q.push(min_q.top());
            min_q.pop();
        }
        int min_top = min_q.top();
        min_q.pop();
        int max_top = max_q.top();
        max_q.pop();
        min_q.push(std::min(min_top, max_top));
        max_q.push(std::max(min_top, max_top));
    }
    int get(int min_limit = 0, int max_limit = 255){
        int y = 0;
        if (total_count % 2) {
            y = min_q.top();
        } else {
            y = (min_q.top() + max_q.top()) / 2;
        }
        return std::max(min_limit, std::min(max_limit, y));
    }
};
