#include "image.hh"

Image::Image(int w, int h, std::vector<float> p)
    : width(w), height(h), pixels(p)
{}

float Image::get_pixel_at(float i, float j) {
    return pixels[i * height + j];
}
