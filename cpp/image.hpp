#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <vector>
#include <string>
#include <tuple>

#include "point.hpp"
#include "color.hpp"
#include "size.hpp"
#include "stroke.hpp"

class Image{
    public:
    std::vector<Color>data;
    Size size;

    Image(Size image_size = Size(0, 0))
    :size(image_size) {
        data = std::vector<Color>(size.width * size.height);
    }
    Image(std::string file_name) {
        read(file_name);
    }

    void read(std::string file_name) {
        int w, h, bpp;
        unsigned char* pixels = stbi_load(file_name.c_str(), &w, &h, &bpp, 0);
        size = Size(w, h);
        data = std::vector<Color>(size.width * size.height);
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                unsigned int index = y * size.width * bpp + x * bpp;
                data[size.width * y + x] = Color(pixels[index], pixels[index + 1], pixels[index + 2]);
            }
        }
        stbi_image_free(pixels);
    }

    void write_png(std::string file_name) {
        int bpp = 4;
        unsigned char* pixels = new unsigned char[size.width * size.height * bpp];
        for (int p_idx = 0, d_idx = 0; d_idx <= size.width * size.height; d_idx++, p_idx += 4) {
            pixels[p_idx] = data[d_idx].r;
            pixels[p_idx + 1] = data[d_idx].g;
            pixels[p_idx + 2] = data[d_idx].b;
            pixels[p_idx + 3] = 255;
        }
        stbi_write_png(file_name.c_str(), size.width, size.height, bpp, pixels, 0);
        stbi_image_free(pixels);
    }

    bool has(Point p) {
        return p.x >= 0 && p.y >= 0 && p.x < size.width && p.y < size.height;
    }

    void paint(Stroke stroke) {
        for (auto point: stroke.point_set) {
            data[point.x + size.width * point.y] += stroke.color;
        }
    }

    Color & operator [](Point point) { 
        return data[point.x + size.width * point.y];
    }

};
