#pragma once

#include <cstdarg>
#include <vector>
#include <iostream>

namespace variadic {

inline void push_all(std::vector<float>& vec, float nb...) {
    va_list args;
    va_start(args, nb);
    for (int i = 0; i < nb; ++i) {
        float val = va_arg(args, double);
        vec.push_back(val);
    }
    va_end(args);
}

}
