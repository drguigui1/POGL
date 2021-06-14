#pragma once

#include <glm/glm.hpp>

class PointLight {
public:
    PointLight() = default;
    PointLight(glm::vec3 l_color,
               glm::vec3 l_pos,
               float l_kc,
               float l_kl,
               float l_kq);
    glm::vec3 light_color;
    glm::vec3 light_pos;
    float light_kc;
    float light_kl;
    float light_kq;
};

class DirectionalLight {
public:
    DirectionalLight() = default;
    DirectionalLight(glm::vec3 l_color, glm::vec3 l_dir);
    glm::vec3 light_color;
    glm::vec3 light_dir;
};