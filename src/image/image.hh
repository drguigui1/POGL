#pragma once

#include <vector>

class Image {
public:
    Image() = default;
    Image(int w, int h, std::vector<float> p);

    /* Methods */
    float get_pixel_at(float i, float j);

    /* Getters */
    int get_width() const { return width; }
    int get_height() const { return height; }

private:
    int width;
    int height;

    std::vector<float> pixels;
};
