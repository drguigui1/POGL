#pragma once

namespace value {

inline float clamp(float a, float b, float value) {
    return std::max(a, std::min(b, value));
}

}
