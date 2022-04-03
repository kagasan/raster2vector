#pragma once
#include <string>
#include <sstream>
#include <vector>

#include "stroke.hpp"

class SVG{
    public:
    Size size;
    std::string data;
    SVG(Size size): size(size) {
        std::stringstream ss;
        ss << "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" << std::endl;
        ss << "<!DOCTYPE svg PUBLIC '-//W3C//DTD SVG 1.1//EN' 'http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd'>" << std::endl;
        ss << "<svg width='100%' height='100%' viewBox='0 0 ";
        ss << size.width << " " << size.height;
        ss << "' version='1.1' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink' ";
        ss << " xml:space='preserve' xmlns:serif='http://www.serif.com/'";
        ss << " style='fill-rule:evenodd;clip-rule:evenodd;stroke-linejoin:round;stroke-miterlimit:2;'>" << std::endl;
        data = ss.str();
    }
    void bind(std::vector<Stroke>strokes) {
        std::stringstream ss;
        for (auto stroke: strokes) {
            ss << stroke << std::endl;
        }
        data += ss.str();
    }
    
    friend std::ostream& operator<<(std::ostream&, const SVG&);
};

std::ostream& operator<<(std::ostream& stream, const SVG& svg){
    stream << svg.data << std::endl;
    stream << "</svg>";
    return stream;
}
