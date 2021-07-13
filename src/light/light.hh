#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "shader.hh"

class Light {
public:
    Light() = default;
    Light(const glm::vec3& c);

    /* Methods */
    virtual void to_shader(Shader& shader, const int& i, const glm::vec3 offset = glm::vec3(0.0f)) const = 0; // DO NOT USE IT - TO REMOVE
    virtual void to_shader(shared_shader shader, const int& i, const glm::vec3 offset = glm::vec3(0.0f)) const = 0;

protected:
    /* Attributes */
    glm::vec3 light_color;

};

class PointLight : public Light {
public:
    PointLight() = default;
    PointLight(const glm::vec3& l_color,
               const glm::vec3& l_pos,
               float l_kc,
               float l_kl,
               float l_kq);

    /* Methods */
    virtual void to_shader(Shader& shader, const int& i, const glm::vec3 offset = glm::vec3(0.0f)) const override;
    virtual void to_shader(shared_shader shader, const int& i, const glm::vec3 offset = glm::vec3(0.0f)) const override;

private:
    /* Attributes */
    glm::vec3 light_pos;
    float light_kc;
    float light_kl;
    float light_kq;
};

class DirectionalLight : public Light {
public:
    DirectionalLight() = default;
    DirectionalLight(const glm::vec3& l_color, const glm::vec3& l_dir);

    /* Methods */
    virtual void to_shader(Shader& shader, const int& i, const glm::vec3 offset = glm::vec3(0.0f)) const override;
    virtual void to_shader(shared_shader shader, const int& i, const glm::vec3 offset = glm::vec3(0.0f)) const override;

private:
    /* Attributes */
    glm::vec3 light_dir;
};

using shared_light = std::shared_ptr<Light>;
