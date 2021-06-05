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

inline void min(float& res, float values...) {
    va_list args;
    va_start(args, values);

    for (int i = 0; i < values; ++i) {
        float val = va_arg(args, double);

        res = std::min(res, val);
    }
    va_end(args);
}

inline void max(float& res, float values...) {
    va_list args;
    va_start(args, values);

    for (int i = 0; i < values; ++i) {
        float val = va_arg(args, double);

        res = std::max(res, val);
    }
    va_end(args);
}

}
