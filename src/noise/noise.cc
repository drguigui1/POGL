#include "noise.hh"

#include "random.hh"

Noise::Noise(float s, NoiseType t)
    : scale(s), type(t)
{
    this->init_noise_arrays();
}

void Noise::init_noise_arrays() {
    glm::vec3 tmp(0.0);

    for (int i = 0; i < count; ++i) {
        tmp.x = randm::random_float(0, 10);
        tmp.y = randm::random_float(0, 6);
        tmp.z = randm::random_float(0, 2);

        random_vect[i] = tmp;
    }

    for (int i = 0; i < count * 3; ++i)
        permutation[i] = i / 3;

    randm::shuffle(permutation, count * 3);
}

float Noise::compute(float x, float y, float z, int octaves) const {
    switch (type) {
    case NOISE:
        return 0.5 + noise(x * scale, y * scale, z * scale) * 0.5;
    case WOOD:
        return sin(z * scale + this->wood(x, y, z) * 10);
    default:
        return 0.5 + sin(z * scale + this->turb(x, y, z, octaves) * 10) * 0.5;
    }
}

static double smooth_step(float x) {
    if (x <= 0) return 0;
    if (x >= 1) return 1;
    return x * x * (3 - 2 * x);
}

static double f(float i, float x) {
    return i * x + (1 - i) * (1 - x);
}

static float interpolate(const glm::vec3 c[2][2][2], float x, float y, float z) {
    float u = x - std::floor(x);
    float v = y - std::floor(y);
    float w = z - std::floor(z);

    float uu = smooth_step(u);
    float vv = smooth_step(v);
    float ww = smooth_step(w);

    float res = 0;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2 ; ++k) {
                float dot = 0;
                dot += (u - i) * c[i][j][k].x;
                dot += (v - j) * c[i][j][k].y;
                dot += (w - k) * c[i][j][k].z;

                res += f(i, uu) * f(j, vv) * f(k, w) * dot;
            }
        }
    }
    return res;
}

float Noise::noise(float x, float y, float z) const {
    int x_floor = std::floor(x);
    int y_floor = std::floor(y);
    int z_floor = std::floor(z);

    glm::vec3 c[2][2][2] = { glm::vec3(0.0) };
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                c[i][j][k] = random_vect[
                    permutation[(x_floor + i) & mask] ^
                    permutation[((y_floor + j) & mask) * 2] ^
                    permutation[((z_floor + j) & mask) * 3]
                ];
            }
        }
    }

    return interpolate(c, x, y, z);
}

float Noise::turb(float x, float y, float z, int octaves) const {
    float res = 0;
    float factor = 1;
    float freq = 1;
    for (int i = 0; i < octaves; ++i) {
        res += this->noise(x * freq, y * freq, z * freq) * factor;
        freq *= 2;
        factor *= 0.5f;
    }
    return res;
}

float Noise::wood(float x, float y, float z) const {
    return std::fabs(this->noise(x, y, z)) * 10;
}
