#pragma once

#include "value.hh"
#include "file.hh"

namespace save {

inline void save_to_ppm_grayscale(const char* filename, const std::vector<float> map, int width, int height) {
    std::ofstream file = file::open_write_file(filename);

    file << "P3" << std::endl;
    file << width << ' ' << height << std::endl;
    file << "255" << std::endl;

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            int value = value::clamp(0, 255, map[i * height + j] * 255.0);
            file << value << ' ' << value << ' ' << value << std::endl;
        }
    }

    std::cout << "Save grayscale ppm image at " << filename << std::endl;
    file.close();
}

inline void save_vector(const char* filename, const std::vector<float> map, int width, int height) {
    std::ofstream file = file::open_write_file(filename);

    // Image size
    file << width << ' ' << height << std::endl;

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            float value = map[i * height + j];
            file << value << std::endl;
        }
    }

    std::cout << "Save vector with float at " << filename << std::endl;
    file.close();
}

}
