#pragma once
#include <iostream>
class Size{
    public:
    int width, height;
    Size(int width = 0, int height = 0):width(width),height(height){}
    friend std::ostream& operator<<(std::ostream&, const Size&);
};

std::ostream& operator<<(std::ostream& stream, const Size& size){
    stream << size.width << "," << size.height;
    return stream;
}
