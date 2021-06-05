#include <cmath>

#include "noise2.hh"

ImprovedNoise::ImprovedNoise() {
    p = new int[512];
    for (int i = 0; i < 256 ; i++) {
        p[256 + i] = permutation[i];
        p[i] = permutation[i];
    }
}

ImprovedNoise::~ImprovedNoise() {
    delete[] p;
}

static float lerp(float t, float a, float b) {
    return a + t * (b - a);
}

static float grad(int hash, float x, float y, float z) {
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float ImprovedNoise::compute(float x, float y, float z, int) const {
    return noise(x, y, z);
}

float ImprovedNoise::noise(float x, float y, float z) const {
    auto floor = [](float value, int mask) { return (int) std::floor(value) & mask; };
    int x0 = floor(x, this->mask);
    int y0 = floor(y, this->mask);
    int z0 = floor(z, this->mask);

    auto relative_pos = [](float x) { return x - std::floor(x); };
    x = relative_pos(x);
    y = relative_pos(y);
    z = relative_pos(z);

    auto fade = [](float t) { return t * t * t * (t * (t * 6 - 15) + 10); };
    float u = fade(x);
    float v = fade(y);
    float w = fade(z);

    int p00 = p[p[x0    ] + y0     ] + z0;
    int p01 = p[p[x0    ] + y0 + 1 ] + z0;
    int p10 = p[p[x0 + 1] + y0     ] + z0;
    int p11 = p[p[x0 + 1] + y0 + 1 ] + z0;

    float a, b;

    a = grad(p[p00],     x,     y,     z);
    b = grad(p[p10],     x - 1, y,     z);
    float l1 = lerp(u, a, b);

    a = grad(p[p01],     x,     y - 1, z);
    b = grad(p[p11],     x - 1, y - 1, z);
    float l2 = lerp(u, a, b);

    a = grad(p[p00 + 1], x,     y,     z - 1);
    b = grad(p[p10 + 1], x - 1, y,     z - 1);
    float l3 = lerp(u, a, b);

    a = grad(p[p01 + 1], x,     y - 1, z - 1);
    b = grad(p[p11 + 1], x - 1, y - 1, z - 1);
    float l4 = lerp(u, a, b);

    return lerp(w, lerp(v, l1, l2), lerp(v, l3, l4));
}
