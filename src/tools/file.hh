#pragma once

#include <iostream>
#include <sstream>

namespace file {

inline std::ifstream open_read_file(const char* path) {
    std::ifstream file(path);
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

}
