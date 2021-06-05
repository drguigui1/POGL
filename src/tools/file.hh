#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include "image.hh"

namespace file {

inline std::ifstream open_read_file(const char* path) {
    std::ifstream file(path);
    if (!file.is_open())
        std::cout << "Error: cannot open file " << path << std::endl;
    return file;
}

inline std::ofstream open_write_file(const char* path) {
    std::ofstream file(path);
    if (!file.is_open())
        std::cout << "Error: cannot open file " << path << std::endl;
    return file;
}

inline std::string get_file_content(const char* path) {
    std::ifstream file = open_read_file(path);

    std::stringstream stream;
    stream << file.rdbuf();

    file.close();
    return stream.str();
}

inline Image ppm_to_image(const char* path) {
    std::ifstream file = file::open_read_file(path);

    // Parse header
    std::string line;
    getline(file, line); // P3
    getline(file, line); // width, height

    size_t dist;
    int width = std::stoi(line, &dist);
    int height = std::stoi(line.substr(dist));

    getline(file, line); // 255

    std::vector<float> height_map = std::vector<float>();
    for (std::string line; getline(file, line);)
        height_map.push_back(std::stof(line));

    file.close();
    return Image(width, height, height_map);
}

}
