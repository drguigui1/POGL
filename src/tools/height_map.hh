#pragma once

#include <vector>
#include <iostream>

#include "noise2.hh"
#include "save.hh"
#include "random.hh"

inline std::vector<float> generate_height_map(int width, int height) {
    ImprovedNoise noise;
    std::vector<float> height_map = std::vector<float>();

    float coef = randm::random_float(50, 200);
    float shift_x = randm::random_float(0, 1);
    float shift_y = randm::random_float(0, 1);

    for (float i = 0; i < width; ++i) {
        for (float j = 0; j < height; ++j) {
            float value = noise.compute(i / coef + shift_x, j / coef + shift_y, 0);
            height_map.push_back(value);
        }
    }

    return height_map;
}
