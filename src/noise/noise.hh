#pragma once

#include <glm/glm.hpp>

enum NoiseType {
    NOISE,
    TURBULENCE,
    WOOD
};

class Noise {
public:
    Noise(float s=1, NoiseType t=NOISE);

    /* Methods */
    virtual float compute(float x, float y, float z, int octaves=7) const;

protected:
    static const int size = 256;
    static const int mask = 255;

private:
    void init_noise_arrays();
    float noise(float x, float y, float z) const;
    float turb(float x, float y, float z, int octaves) const;
    float wood(float x, float y, float z) const;

    /* Attributes */
    float scale;
    NoiseType type;

    glm::vec3 random_vect[size];
    int permutation[size * 3];
};
