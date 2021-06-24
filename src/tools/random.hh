#pragma once

#include <cstdlib>

namespace randm {

inline int random_int() {
    return std::rand();
}

inline int random_int(int min, int max) {
    return min + std::rand() % (max - min);
}

inline float random_float() {
    return std::rand() / (RAND_MAX + 1.0);
}

inline float random_float(float min, float max) {
    return min + random_float() * (max - min);
}

inline bool random_bool() {
    return (random_int() % 2) == 0;
}

inline glm::vec3 random_vec3(float min, float max) {
    return glm::vec3(random_float(min, max), random_float(min, max), random_float(min, max));
}

inline void shuffle(int* p, int n) {
    for (int i = n - 1; i > 0; --i)
        std::swap(p[i], p[random_int(0, i)]);
}

}
